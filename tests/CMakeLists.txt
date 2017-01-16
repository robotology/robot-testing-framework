#  Robot Testing Framework
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


# build tests
include(RTFTestHelpers)

if (BUILD_TESTING AND BUILD_TESTRUNNER)
    # enable RTF testing 
    ENABLE_RTF_TESTS()

    # adding c++ tests
    add_subdirectory(basic)

    # adding lua tests
    add_subdirectory(lua)

endif()

