// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_DLLFIXTUREPLUGINLOADER_H
#define _RTF_DLLFIXTUREPLUGINLOADER_H

#include <rtf_dll_config.h>
#include <string>
#include <FixtureManager.h>

namespace RTF {
    namespace plugin {
        class DllFixturePluginLoader;
    }
}

/**
 * @brief The DllFixturePluginLoader loads an test case plug-in and
 * gives the direct access to the TestCase.
 */
class SHLIBPP_EXPORT RTF::plugin::DllFixturePluginLoader {

public:

    /**
     * DllFixturePluginLoader constructor
     */
    DllFixturePluginLoader();

    /**
     *  DllFixturePluginLoader destructor
     */
    virtual ~DllFixturePluginLoader();

    /**
     * @brief open Loads a test case plugin
     * @param filename the plugin filename
     * @return A pointer to the test case loaded from the
     * plugin or a null pointer in case of failure.
     */
    RTF::FixtureManager* open(const std::string filename);

    /**
     * @brief close Unloads the plugin and deletes any
     * allocated memory.
     */
    void close();

    /**
     * @brief getLastError gets the last error if any.
     * @return returns the last error string.
     */
    const std::string getLastError();

private:
    void* implementaion;
};

#endif // _RTF_DLLFIXTUREPLUGINLOADER_H
