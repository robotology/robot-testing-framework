#  Robot Testing Framework
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


# build tests
if (BUILD_TESTS)
    set(TESTRUNNER_PATH ${CMAKE_BINARY_DIR}/bin/testrunner)
    # set the output plugin directory to collect all tests
    set(TEST_TARGET_PATH ${CMAKE_BINARY_DIR}/bin/tests)

    # adding c++ tests
    if (ENABLE_PLUGIN)        
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TEST_TARGET_PATH})
        set(CMAKE_SHARED_MODULE_PREFIX "")
        add_subdirectory(basic)
    endif()

    # adding lua tests
    add_subdirectory(lua)

    # running test units
    add_test(NAME tests
         COMMAND ${TESTRUNNER_PATH} -v --tests ${TEST_TARGET_PATH}
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

