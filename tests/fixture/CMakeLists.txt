#  RTF
#  Copyright: (C) 2015 Ali Paikan
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#

if (ENABLE_PLUGIN)
    get_property(RTF_LIBS GLOBAL PROPERTY RTF_LIBS)

    # Build a ficture plugin
    set(CMAKE_SHARED_MODULE_PREFIX "")
    add_library(myfixture MODULE MyFixManager.cpp MyFixManager.h)
    target_link_libraries(myfixture ${RTF_LIBS})

    # add the FixturePluginLoader test
    if (UNIX)
        set(param "${TEST_TARGET_PATH}/myfixture.so")
    elseif(WIN32)
        set(param "${TEST_TARGET_PATH}/${CMAKE_BUILD_TYPE}/myfixture.dll")
    else()
        set(param "${TEST_TARGET_PATH}/myfixture.dylib")
    endif()

    ADD_RTF_CPPTEST(NAME FixturePluginLoader
                    SRCS FixturePluginLoader.cpp
                PARAM ${param})
endif()
