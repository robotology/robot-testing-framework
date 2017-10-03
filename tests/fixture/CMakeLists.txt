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
    target_link_libraries(myfixture RTF RTF_dll)

    # add the FixturePluginLoader test

    ADD_RTF_CPPTEST(NAME FixturePluginLoader
                    SRCS FixturePluginLoader.cpp
                    PARAM "$<TARGET_FILE:myfixture>")
endif()
