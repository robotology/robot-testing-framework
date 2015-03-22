# Install script for directory: /home/apaikan/Install/robotology/robot-testing/src/rtf

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libRTF.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libRTF.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libRTF.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/apaikan/Install/robotology/robot-testing/build/lib/libRTF.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libRTF.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libRTF.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libRTF.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/apaikan/Install/robotology/robot-testing/src/rtf/./include/Exception.h"
    "/home/apaikan/Install/robotology/robot-testing/src/rtf/./include/TestResult.h"
    "/home/apaikan/Install/robotology/robot-testing/src/rtf/./include/Asserter.h"
    "/home/apaikan/Install/robotology/robot-testing/src/rtf/./include/TestListener.h"
    "/home/apaikan/Install/robotology/robot-testing/src/rtf/./include/TestResultCollector.h"
    "/home/apaikan/Install/robotology/robot-testing/src/rtf/./include/ResultEvent.h"
    "/home/apaikan/Install/robotology/robot-testing/src/rtf/./include/TestSuit.h"
    "/home/apaikan/Install/robotology/robot-testing/src/rtf/./include/FixtureManager.h"
    "/home/apaikan/Install/robotology/robot-testing/src/rtf/./include/TestCase.h"
    "/home/apaikan/Install/robotology/robot-testing/src/rtf/./include/Test.h"
    "/home/apaikan/Install/robotology/robot-testing/src/rtf/./include/TextOutputter.h"
    "/home/apaikan/Install/robotology/robot-testing/src/rtf/./include/TestMessage.h"
    "/home/apaikan/Install/robotology/robot-testing/src/rtf/./include/ConsoleListener.h"
    "/home/apaikan/Install/robotology/robot-testing/src/rtf/./include/TestRunner.h"
    "/home/apaikan/Install/robotology/robot-testing/src/rtf/./include/TestAssert.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime")

