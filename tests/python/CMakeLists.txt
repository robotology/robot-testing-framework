#  Robot Testing Framework
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


# adding lua tests
if(ENABLE_PYTHON_PLUGIN)

    # LuaPlugin depends on LuaTestCase.lua
    ADD_RTF_CPPTEST(NAME PythonPlugin
                    SRCS PythonPlugin.cpp
                    PARAM "${TEST_TARGET_PATH}/PythonTestCase.py"
                    ENV "bar")

    # LuaTestCase
    ADD_RTF_PYTHONTEST(PythonTestCase.py)

endif()

