#  Robot Testing Framework
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


# adding lua tests
if(ENABLE_LUA_PLUGIN)

    # LuaPlugin depends on LuaTestCase.lua
    ADD_RTF_CPPTEST(NAME LuaPlugin
                    SRCS LuaPlugin.cpp
                    PARAM "${TEST_TARGET_PATH}/LuaTestCase.lua"
                    ENV "bar")

    # LuaTestCase
    ADD_RTF_LUATEST(LuaTestCase.lua)

endif()

