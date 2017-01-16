#  RTF
#  Copyright: (C) 2015 Ali Paikan
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#

if (ENABLE_PLUGIN)        

    # SingleTestCase
    ADD_RTF_CPPTEST(SingleTestCase SingleTestCase.cpp)

    # SingleTestCase
    ADD_RTF_CPPTEST(MultiTestCases MultiTestCases.cpp)

    # SingleTestSuite
    ADD_RTF_CPPTEST(SingleTestSuite SingleTestSuite.cpp)   

    # SingleTestSuite
    ADD_RTF_CPPTEST(FixtureManager FixtureManager.cpp)

endif()

