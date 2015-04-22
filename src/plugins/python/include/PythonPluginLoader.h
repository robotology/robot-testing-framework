// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_PYTHONPLUGINLOADER_H
#define _RTF_PYTHONPLUGINLOADER_H

#include <PluginLoader.h>
#include <TestCase.h>
#include <string>

namespace RTF {
    namespace plugin {
        class PythonPluginLoader;
    }
}

/**
 * @brief The PythonPluginLoader loads a Python test case plug-in and
 * gives the direct access to the TestCase.
 */
class RTF::plugin::PythonPluginLoader : public RTF::plugin::PluginLoader {

public:

    /**
     * PythonPluginLoader constructor
     */
    PythonPluginLoader();

    /**
     *  PythonPluginLoader destructor
     */
    virtual ~PythonPluginLoader();

    /**
     * @brief open Loads a test case plugin
     * @param filename the pyhton plugin filename
     * @return A pointer to the test case loaded from the
     * plugin or a null pointer in case of failure.
     */
    RTF::TestCase* open(const std::string filename);

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

#endif // _RTF_PYTHONPLUGINLOADER_H
