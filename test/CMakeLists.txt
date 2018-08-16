option(KW_Valgrind "Execute test suite with Valgrind" OFF)
option(KW_Coverage "Build test suite with coverage information" OFF)

ADD_DEFINITIONS(-DBOOST_ALL_DYN_LINK)

add_library(catch_main OBJECT
    "src/unit.cpp"
)
target_compile_features(catch_main PUBLIC cxx_std_11)
target_include_directories(catch_main PRIVATE "thirdparty/catch")


if(KW_Coverage)
    message(STATUS "Building test suite with coverage information")
    if(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        message(FATAL_ERROR "KW_Coverage requires GCC.")
    endif()

    # enable profiling
    set(CMAKE_CXX_FLAGS "--coverage -g -O0 -fprofile-arcs -ftest-coverage")

    # from https://github.com/RWTH-HPC/CMake-codecov/blob/master/cmake/FindGcov.cmake
    get_filename_component(COMPILER_PATH "${CMAKE_CXX_COMPILER}" PATH)
    string(REGEX MATCH "^[0-9]+" GCC_VERSION "${CMAKE_CXX_COMPILER_VERSION}")
    find_program(GCOV_BIN NAMES gcov-${GCC_VERSION} gcov HINTS ${COMPILER_PATH})

    # collect all source files from the chosen include dir
    file(GLOB_RECURSE SOURCE_FILES ${CHUHLICH_KW_INCLUDE_BUILD_DIR}*.h ${CHUHLICH_KW_SRC_BUILD_DIR}*.cpp)

    # add target to collect coverage information and generate HTML file
    # (filter script from https://stackoverflow.com/a/43726240/266378)
    add_custom_target(lcov_html
        COMMAND lcov --directory .. --capture --output-file json.info --gcov-tool ${GCOV_BIN} --rc lcov_branch_coverage=1
        COMMAND lcov -e json.info ${SOURCE_FILES} --output-file json.info.filtered --rc lcov_branch_coverage=1
#        COMMAND ${CMAKE_SOURCE_DIR}/test/thirdparty/imapdl/filterbr.py json.info.filtered > json.info.filtered.noexcept
        COMMAND genhtml --title "KW - Knitwork" --legend --demangle-cpp --output-directory html --show-details --branch-coverage json.info.filtered
        COMMENT "Generating HTML report test/html/index.html"
    )
endif()


file(GLOB files "src/unit-*.cpp")
foreach(file ${files})
    get_filename_component(file_basename ${file} NAME_WE)
    string(REGEX REPLACE "unit-([^$]+)" "test-\\1" testcase ${file_basename})

    add_executable(${testcase} $<TARGET_OBJECTS:catch_main> ${file})
    set_target_properties(${testcase} PROPERTIES
        COMPILE_DEFINITIONS "$<$<CXX_COMPILER_ID:MSVC>:_SCL_SECURE_NO_WARNINGS>"
        COMPILE_OPTIONS "$<$<CXX_COMPILER_ID:MSVC>:/EHsc;$<$<CONFIG:Release>:/Od>>"
    )

    target_compile_definitions(${testcase} PRIVATE CATCH_CONFIG_FAST_COMPILE)
    target_compile_features(${testcase} PRIVATE cxx_std_11)
    target_include_directories(${testcase} PRIVATE "thirdparty/catch")
    target_include_directories(${testcase} PRIVATE ${CHUHLICH_KW_INCLUDE_BUILD_DIR})
    target_include_directories(${testcase} PRIVATE ${Boost_INCLUDE_DIRS})

    target_link_libraries(${testcase} ${CHUHLICH_KW_TARGET_NAME} boost_filesystem boost_system boost_log_setup boost_log)

    set(Boost_NO_BOOST_CMAKE ON) #  Don't do a find_package in config mode before searching for a regular boost install.
#    find_package(Boost COMPONENTS log_setup log program_options REQUIRED)
    add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})

    if(NOT MSVC)
        set_target_properties(${testcase} PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated -Wno-float-equal")
    endif()

    add_test(NAME "${testcase}_default"
      COMMAND ${testcase} ${CATCH_TEST_FILTER}
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    set_tests_properties("${testcase}_default" PROPERTIES LABELS "default")

    add_test(NAME "${testcase}_all"
      COMMAND ${testcase} ${CATCH_TEST_FILTER} "*"
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    set_tests_properties("${testcase}_all" PROPERTIES LABELS "all")

    if(KW_Valgrind)
        add_test(NAME "${testcase}_valgrind"
          COMMAND ${memcheck_command} ${CMAKE_CURRENT_BINARY_DIR}/${testcase} ${CATCH_TEST_FILTER}
          WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        )
        set_tests_properties("${testcase}_valgrind" PROPERTIES LABELS "valgrind")
    endif()

endforeach()
