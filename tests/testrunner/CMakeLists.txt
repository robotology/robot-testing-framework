
#  Robot Testing Framework
#  Copyright: (C) 2017 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Silvio Traversaro <silvio@traversaro.it>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


# adding testrunner tests
add_test(NAME TestRunnerLoadSimpleSuite
         COMMAND $<TARGET_FILE:testrunner> -v --no-output --suite ${CMAKE_CURRENT_SOURCE_DIR}/testsuite.xml
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_test(NAME TestRunnerLoadLegacySuit
         COMMAND $<TARGET_FILE:testrunner> -v --no-output --suit ${CMAKE_CURRENT_SOURCE_DIR}/testsuit.xml
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
