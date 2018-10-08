add_definitions(-D__LIBNAME="kw")
ADD_DEFINITIONS(-DBOOST_ALL_DYN_LINK)

# We need profiling info if tests are activated
if(BUILD_TESTING AND KW_BuildTests)
    set(CMAKE_CXX_FLAGS "--coverage -g -O0 -fprofile-arcs -ftest-coverage")
endif()


# @author  Barthélémy von Haller
set(LIB_HEADERS
  "${CMAKE_CURRENT_BINARY_DIR}/../include/kw/kwVersion.h" # Generated header
  ../include/kw/kwBase.h
  ../include/kw/kwDataContainer.h
  ../include/kw/kwDataSourceFactory.h
  ../include/kw/kwDataSource.h
  ../include/kw/kwDebug.h
  ../include/kw/kwLibHandle.h
  ../include/kw/kwLibraryInfo.h
  ../include/kw/kwLibraryManager.h
  ../include/kw/kwLogger.h
  ../include/kw/kwMessage.h
  ../include/kw/kwMessageHandlerFactory.h
  ../include/kw/kwMessageHandler.h
  ../include/kw/kwTestHandler.h
  ../include/kw/kwObjectFactory.h
  ../include/kw/kwObject.h
  ../include/kw/kwReleaseInfo.h
  ../include/kw/kwShm.h
  ../include/kw/kwSocketClient.h
  ../include/kw/kwSystem.h
  ../include/kw/kwTechnicalException.h
  ../include/kw/kwTimer.h
  ../include/kw/kwValColor.h
  ../include/kw/kwValCoord.h
  ../include/kw/kwValFixedPoint.h
  ../include/kw/kwValInteger.h
  ../include/kw/kwValUnsignedInteger.h
  ../include/kw/kwValFloat.h
  ../include/kw/kwValString.h
  ../include/kw/kwValue.h
  ../include/kw/kwValJsonObject.h
  ../include/kw/kwValBool.h
  ../include/kw/kwLockedQueue.h
  ../include/kw/kwSysTimerConfiguration.h
)

set(LIB_SOURCES
  kwDataContainer.cpp
  kwDataSource.cpp
  kwDataSourceFactory.cpp
  kwSysTimerConfiguration.cpp
  kwException.cpp
  kwLibHandle.cpp
  kwLibraryInfo.cpp
  kwLibraryManager.cpp
  kwLogger.cpp
  kwMessage.cpp
  kwMessageHandler.cpp
  kwTestHandler.cpp
  kwMessageHandlerFactory.cpp
  kwObject.cpp
  kwObjectFactory.cpp
  kwShm.cpp
  kwSocketClient.cpp
  kwSystem.cpp
  kwTimer.cpp
  kwValColor.cpp
  kwValCoord.cpp
  kwValFixedPoint.cpp
  kwValInteger.cpp
  kwValUnsignedInteger.cpp
  kwValFloat.cpp
  kwValString.cpp
  kwValBool.cpp
  kwValJsonObject.cpp
  kwValue.cpp
)

set(APP_HEADERS
)

set(APP_SOURCES
  main.cpp
)

# Define two variables in order not to repeat ourselves.
set(LIBRARY_NAME kw)

# Define the library
add_library(${LIBRARY_NAME} SHARED ${LIB_SOURCES})
set_target_properties(${LIBRARY_NAME} PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated -Wno-float-equal")

# Set the build version. It will be used in the name of the lib, with corresponding
# symlinks created. SOVERSION could also be specified for api version. 
set_target_properties(${LIBRARY_NAME} PROPERTIES
  VERSION ${VERSION}  # ${VERSION} was defined in the main CMakeLists.
  FRAMEWORK FALSE
  PUBLIC_HEADER "${LIB_HEADERS}" # specify the public headers
)

include_directories("${CMAKE_SOURCE_DIR}/include/kw"
  "${CMAKE_SOURCE_DIR}/ext/json/include"
  )

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

# This is a make target, so you can do a "make projArunner"
set(APPLICATION_NAME kwRunner)
add_executable(${APPLICATION_NAME} ${APP_SOURCES})

# Links the target exe (projArunner) against the library (libprojA) and other required libraries
target_link_libraries(${APPLICATION_NAME} ${LIBRARY_NAME} dl Threads::Threads rt boost_filesystem boost_system boost_log_setup boost_log)
#

# Says how and where to install software
# Targets:
#   * <prefix>/lib/<libraries>
#   * header location after install: <prefix>/include/<project>/*.h
#   * headers can be included by C++ code `#<project>/Bar.hpp>`
install(TARGETS ${LIBRARY_NAME} ${APPLICATION_NAME}
  EXPORT ${PROJECT_NAME}Targets            # for downstream dependencies
  ARCHIVE DESTINATION lib COMPONENT libs   # static lib
  RUNTIME DESTINATION bin COMPONENT libs   # binaries
  LIBRARY DESTINATION lib COMPONENT libs   # shared lib
  FRAMEWORK DESTINATION bin COMPONENT libs # for mac
  PUBLIC_HEADER DESTINATION include/${PROJECT_NAME} COMPONENT devel   # headers for mac (note the different component -> different package)
  INCLUDES DESTINATION include             # headers
)
