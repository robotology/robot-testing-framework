// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_DLLPLUGINLOADERIMPL_H
#define _RTF_DLLPLUGINLOADERIMPL_H

#include <TestCase.h>
#include <SharedLibrary.h>
#include <SharedLibraryClass.h>

/**
 * class DllPluginLoaderImpl
 */
class DllPluginLoaderImpl {

    class Plugin {
    public:
        shlibpp::SharedLibraryClassFactory<RTF::TestCase> factory;
        shlibpp::SharedLibraryClass<RTF::TestCase> test;
    };

public:

    /**
     * DllPluginLoaderImpl constructor
     */
    DllPluginLoaderImpl();

    /**
     *  DllPluginLoaderImpl destructor
     */
    virtual ~DllPluginLoaderImpl();

    /**
     * @brief open Loads a test case plugin
     * @param filename the plugin filename
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
    const std::string& getLastError();

private:
    std::string error;
    Plugin* plugin;
};

#endif // _RTF_DLLPLUGINLOADERIMPL_H
