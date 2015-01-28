# Copyright: 2014 iCub Facility, Istituto Italiano di Tecnologia
# Author: Lorenzo Natale
# CopyPolicy: Released under the terms of the GNU GPL v2.0.


set(folder_source TestSet.cpp UnitTest.cpp main.cpp Logger.cpp)
set(folder_header TestSet.h UnitTest.h Logger.h)

set(folder_tests testCamera/TestCamera.cpp testCamera/TestCamera.h 
    testMotors/TestMotors.cpp testMotors/TestMotors.h
    testFTSensors/TestFTSensors.h testFTSensors/TestFTSensors.cpp
)

source_group("Source Files" FILES ${folder_source})
source_group("Header Files" FILES ${folder_header})
source_group("Tests" FILES ${folder_tests})

include_directories(${YARP_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

### this makes everything go in $ICUB_DIR/lib and $ICUB_DIR/bin
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
message(STATUS "Executables go to ${EXECUTABLE_OUTPUT_PATH}")

add_executable(robot-testing ${folder_source} ${folder_header} ${folder_tests})

target_link_libraries(robot-testing ${YARP_LIBRARIES})
