#  Robot Testing Framework
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


# build yarp specific extensions
if (ENABLE_YARP)
    add_subdirectory(yarp)
    set_property(GLOBAL PROPERTY RTF_HAS_YARP TRUE)
else()
    set_property(GLOBAL PROPERTY RTF_HAS_YARP FALSE)
endif()
