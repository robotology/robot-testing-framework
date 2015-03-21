// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <Asserter.h> // used to format the string message
#include <Plugin.h>
#include <DllPluginLoader.h>
#include <DllPluginLoader_impl.h>

using namespace std;
using namespace RTF;
using namespace RTF::plugin;
using namespace shlibpp;

/**
 * @brief DllPluginLoader
 */
DllPluginLoader::DllPluginLoader()
    : implementaion(NULL) { }

DllPluginLoader::~DllPluginLoader() {
    close();
}

void DllPluginLoader::close() {
    if(implementaion)
        delete ((DllPluginLoaderImpl*)implementaion);
    implementaion = NULL;
}

TestCase* DllPluginLoader::open(const std::string filename) {
    close();
    implementaion = new DllPluginLoaderImpl();
    return ((DllPluginLoaderImpl*)implementaion)->open(filename);
}

const std::string DllPluginLoader::getLastError() {
    if(implementaion)
        return ((DllPluginLoaderImpl*)implementaion)->getLastError();
    return string("");
}


/**
 * @brief DllPluginLoaderImpl
 */
DllPluginLoaderImpl::DllPluginLoaderImpl()
    : plugin(NULL) { }

DllPluginLoaderImpl::~DllPluginLoaderImpl() {
    close();
}

void DllPluginLoaderImpl::close() {
    if(plugin)
        delete plugin;
    plugin = NULL;
    error.clear();
}

TestCase* DllPluginLoaderImpl::open(std::string filename) {
    // close any previous loaded plugin
    close();

    // create an instance of plugin class and factory
    DllPluginLoaderImpl::Plugin* plugin = new DllPluginLoaderImpl::Plugin;

    // load the test case plugin    
    plugin->factory.open(filename.c_str(), RTF_PLUGIN_FACTORY_NAME);
    if(!plugin->factory.isValid()) {
        if(plugin->factory.getStatus() == VOCAB4('f','a','c','t'))
            error = Asserter::format("cannot load plugin %s; (it is not an RTF plugin!)",
                                            filename.c_str());
        else
            error = Asserter::format("cannot load plugin %s; error (%s) : %s",
                                            filename.c_str(),
                                            Vocab::decode(plugin->factory.getStatus()).c_str(),
                                            plugin->factory.getLastNativeError().c_str());
        delete plugin;
        plugin = NULL;
        return NULL;
    }

    // TODO: check if this is neccessary!!!
    //plugin->factory.addRef();

    // create an instance of the test case from the plugin
    plugin->test.open(plugin->factory);
    if(!plugin->test.isValid()) {
        error = Asserter::format("cannot create an instance of TestCase from %s",
                                        filename.c_str());
        delete plugin;
        plugin = NULL;
        return NULL;
    }

    return &plugin->test.getContent();
}

const std::string& DllPluginLoaderImpl::getLastError() {
    return error;
}
