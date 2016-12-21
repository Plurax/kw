# @author  Barthélémy von Haller
set(LIB_HEADERS
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/Version.h" # Generated header
)

set(LIB_SOURCES
  mglDataContainer.cpp
  mglDataSource.cpp
  mglDataSourceFactory.cpp
  mglException.cpp
  mglLibHandle.cpp
  mglLibraryInfo.cpp
  mglLibraryManager.cpp
  mglLogChannel.cpp
  mglLogDeviceFile.cpp
  mglLogDeviceStdErr.cpp
  mglLogDeviceStdOut.cpp
  mglLogger.cpp
  mglMessage.cpp
  mglMessageHandler.cpp
  mglMessageHandlerFactory.cpp
  mglObject.cpp
  mglObjectFactory.cpp
  mglShm.cpp
  mglSocketClient.cpp
  mglSystem.cpp
  mglTimer.cpp
  mglValColor.cpp
  mglValCoord.cpp
  mglValFixedPoint.cpp
  mglValInteger.cpp
  mglValString.cpp
  mglValue.cpp
)

set(APP_HEADERS
)

set(APP_SOURCES
  main.cpp
)

# Define two variables in order not to repeat ourselves.
set(LIBRARY_NAME mgl)

# Define the library
add_library(${LIBRARY_NAME} SHARED ${LIB_SOURCES})

# Set the build version. It will be used in the name of the lib, with corresponding
# symlinks created. SOVERSION could also be specified for api version. 
set_target_properties(${LIBRARY_NAME} PROPERTIES
  VERSION ${VERSION}  # ${VERSION} was defined in the main CMakeLists.
  FRAMEWORK FALSE
  PUBLIC_HEADER "${LIB_HEADERS}" # specify the public headers
)

include_directories("${CMAKE_SOURCE_DIR}/include/mgl"
  "${CMAKE_SOURCE_DIR}/ext/json/src"
  )

# This is a make target, so you can do a "make projArunner"
#set(APPLICATION_NAME projArunner)
#add_executable(${APPLICATION_NAME} ${APP_SOURCES})

# Links the target exe (projArunner) against the library (libprojA) and other required libraries
#target_link_libraries(${APPLICATION_NAME} ${LIBRARY_NAME} ${Boost_PROGRAM_OPTIONS_LIBRARY})

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
