# @author  Barthélémy von Haller
set(LIB_HEADERS
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/Version.h" # Generated header
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglBase.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglDataContainer.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglDataSourceFactory.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglDataSource.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglDebug.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglLibHandle.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglLibraryInfo.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglLibraryManager.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglLogChannel.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglLogDeviceFile.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglLogDevice.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglLogDeviceStdErr.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglLogDeviceStdOut.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglLogger.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglMessage.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglMessageHandlerFactory.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglMessageHandler.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglObjectFactory.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglObject.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglReleaseInfo.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglShm.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglSocketClient.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglSystem.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglTechnicalException.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglTimer.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglValColor.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglValCoord.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglValFixedPoint.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglValInteger.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglValString.h"
  "${CMAKE_CURRENT_BINARY_DIR}/../include/mgl/mglValue.h"
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
