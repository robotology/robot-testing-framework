#  Robot Testing Framework
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


# build plugin manager
if (ENABLE_PLUGIN OR BUILD_TESTRUNNER)
    add_subdirectory(dll)
endif()

