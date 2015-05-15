// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_DLLPLUGINLOADERIMPL_H
#define _RTF_DLLPLUGINLOADERIMPL_H

#include <rtf/dll/Plugin.h>
#include <rtf/dll/SharedLibrary.h>
#include <rtf/dll/SharedLibraryClass.h>
#include <string>

/**
 * class DllPluginLoaderImpl
 */
template <class T>
class DllPluginLoaderImpl {

    class Plugin {
    public:
        shlibpp::SharedLibraryClassFactory<T> factory;
        shlibpp::SharedLibraryClass<T> test;
    };

public:

    /**
     * DllPluginLoaderImpl constructor
     */
    DllPluginLoaderImpl() : plugin(NULL) { }

    /**
     *  DllPluginLoaderImpl destructor
     */
    virtual ~DllPluginLoaderImpl() {
        close();
    }


    /**
     * @brief open Loads a generic plugin
     * @param filename the plugin filename
     * @return A pointer to the class loaded from the
     * plugin or a null pointer in case of failure.
     */
    T* open(const std::string filename,
                     const std::string factory_name) {
        // close any previous loaded plugin
        close();

        // create an instance of plugin class and factory
        DllPluginLoaderImpl::Plugin* plugin = new DllPluginLoaderImpl::Plugin;

        // load the test case plugin
        plugin->factory.open(filename.c_str(), factory_name.c_str());
        if(!plugin->factory.isValid()) {
            if(plugin->factory.getStatus() == VOCAB4('f','a','c','t')) {
                std::string plug_type = (factory_name==RTF_PLUGIN_FACTORY_NAME) ? "test case" : "fixture manager";
                error = "cannot load plugin " + filename + "; (it is not an RTF " +  plug_type + " plugin!)";
            }
           else {
               error = "cannot load plugin " + filename + "; error (" +
                   shlibpp::Vocab::decode(plugin->factory.getStatus()) + ") : " +
                   plugin->factory.getLastNativeError();
           }
            delete plugin;
            plugin = NULL;
            return NULL;
        }

        // TODO: check if this is neccessary!!!
        //plugin->factory.addRef();

        // create an instance of the test case from the plugin
        plugin->test.open(plugin->factory);
        if(!plugin->test.isValid()) {
            //error = RTF::Asserter::format("cannot create an instance of TestCase from %s",
            //                                filename.c_str());
            delete plugin;
            plugin = NULL;
            return NULL;
        }

        return &plugin->test.getContent();
    }


    /**
     * @brief close Unloads the plugin and deletes any
     * allocated memory.
     */
    void close() {
        if(plugin)
            delete plugin;
        plugin = NULL;
        error.clear();
    }

    /**
     * @brief getLastError gets the last error if any.
     * @return returns the last error string.
     */
    const std::string& getLastError() {
        return error;
    }

private:
    std::string error;
    Plugin* plugin;
};

#endif // _RTF_DLLPLUGINLOADERIMPL_H
