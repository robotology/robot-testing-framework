// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_PLUGINLOADER_H
#define _RTF_PLUGINLOADER_H

#include <string>
#include <TestCase.h>

namespace RTF {
    namespace plugin {
        class PluginLoader;
    }
}

/**
 * @brief The PluginLoader loads an test case plug-in and
 * gives the direct access to the TestCase.
 */
class RTF::plugin::PluginLoader {

public:

    /**
     * PluginLoader constructor
     */
    PluginLoader() { }

    /**
     *  PluginLoader destructor
     */
    virtual ~PluginLoader() { }

    /**
     * @brief open Loads a test case plugin
     * @param filename the plugin filename
     * @return A pointer to the test case loaded from the
     * plugin or a null pointer in case of failure.
     */
    virtual RTF::TestCase* open(const std::string filename) = 0;

    /**
     * @brief close Unloads the plugin and deletes any
     * allocated memory.
     */
    virtual void close() = 0;

    /**
     * @brief getLastError gets the last error if any.
     * @return returns the last error string.
     */
    virtual const std::string getLastError() = 0;
};

#endif // _RTF_PLUGINLOADER_H

