#  Robot Testing Framework
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


# Build RTF library
add_subdirectory(rtf)


# Build testrunner
if (BUILD_TESTRUNNER)
    add_subdirectory(testrunner)
endif(BUILD_TESTRUNNER)

