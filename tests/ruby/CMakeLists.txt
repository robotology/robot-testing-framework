#  Robot Testing Framework
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#


# adding ruby tests
if(ENABLE_RUBY_PLUGIN)

    # RubtPlugin depends on RubyTestCase.rb
    ADD_RTF_CPPTEST(NAME RubyPlugin
                    SRCS RubyPlugin.cpp
                    PARAM "${TEST_TARGET_PATH}/RubyTestCase.rb"
                    ENV "bar")

    # LuaTestCase
    ADD_RTF_RUBYTEST(RubyTestCase.rb)

endif()

