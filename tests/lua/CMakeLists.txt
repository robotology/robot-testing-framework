#  Robot Testing Framework
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


# adding lua tests
if (ENABLE_LUA_PLUGIN)
    configure_file(LuaTestCase.lua ${TEST_TARGET_PATH}/LuaTestCase.lua COPYONLY)
endif()

