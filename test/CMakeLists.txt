

add_library(catch_main OBJECT
    "src/unit.cpp"
)
target_compile_features(catch_main PUBLIC cxx_std_11)
target_include_directories(catch_main PRIVATE "thirdparty/catch")



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
    target_include_directories(${testcase} PRIVATE "thirdparty/fifo_map")
    target_include_directories(${testcase} PRIVATE ${NLOHMANN_JSON_INCLUDE_BUILD_DIR})
    target_link_libraries(${testcase} ${NLOHMANN_JSON_TARGET_NAME})

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

    if(JSON_Valgrind)
        add_test(NAME "${testcase}_valgrind"
          COMMAND ${memcheck_command} ${CMAKE_CURRENT_BINARY_DIR}/${testcase} ${CATCH_TEST_FILTER}
          WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        )
        set_tests_properties("${testcase}_valgrind" PROPERTIES LABELS "valgrind")
    endif()

endforeach()
