#  Robot Testing Framework
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


# build tests
include(RTFTestHelpers)

if (BUILD_TESTING)
    # enable RTF testing
    ENABLE_RTF_TESTS()

    # adding api c++ tests
    add_subdirectory(api)

    if (BUILD_TESTRUNNER)
        # adding basic tests
        add_subdirectory(basic)

        # adding basic tests
        add_subdirectory(fixture)

        # adding lua tests
        add_subdirectory(lua)

        # adding python tests
        add_subdirectory(python)

        # adding python tests
        add_subdirectory(ruby)
    endif()
endif()
