// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#include <Asserter.h> // used to format the string message
#include <PluginRunner.h>
#include <ErrorLogger.h>
#include <PlatformDir.h>
#include <iostream>

using namespace std;
using namespace RTF;
using namespace shlibpp;

PluginRunner::PluginRunner(bool verbose)
    :verbose(verbose) {
}

PluginRunner::~PluginRunner() {
    reset();
}

void PluginRunner::reset() {
    // first clear the test list of the TestRunner
    TestRunner::reset();

    if(verbose)
        cout<<"Unloading plug-ins"<<endl;
    // delete all the plugins which was created
    for(int i=0; i<plugins.size(); i++)
        delete plugins[i];
    plugins.clear();
}

bool PluginRunner::loadPlugin(std::string filename) {
    if(verbose)
        cout<<"Loading "<<filename<<endl;

    // create an instance of plugin class and factory
    PluginRunner::Plugin* plugin = new PluginRunner::Plugin;

    // load the test case plugin
    plugin->factory.open(filename.c_str());
    if(!plugin->factory.isValid()) {
        string error = Asserter::format("cannot load plugin %s; error (%s) : %s",
                                        filename.c_str(),
                                        Vocab::decode(plugin->factory.getStatus()).c_str(),
                                        plugin->factory.getLastNativeError().c_str());
        ErrorLogger::Instance().addError(error);
        return false;
    }

    // TODO: check if this is neccessary!!!
    //plugin->factory.addRef();

    // create an instance of the test case from the plugin
    plugin->test.open(plugin->factory);
    if(!plugin->test.isValid()) {
        string error = Asserter::format("cannot create an instance of TestCase from %s",
                                        filename.c_str());
        ErrorLogger::Instance().addError(error);
        delete plugin;
        return false;
    }

    // keep track of what have been created
    plugins.push_back(plugin);

    // add the test case to the TestRunner
    addTest(&plugin->test.getContent());
    return true;
}

bool PluginRunner::loadMultiplePlugins(std::string path,
                                         bool recursive) {    
    if(!recursive)
        return loadPluginsFromPath(path);

    // load from subfolders
    if((path.rfind(PATH_SEPERATOR)==string::npos) ||
        (path.rfind(PATH_SEPERATOR)!=path.size()-1))
        path = path + string(PATH_SEPERATOR);

    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(path.c_str())) == NULL) {
        ErrorLogger::Instance().addError("cannot access " + path);
        return false;
    }

    loadPluginsFromPath(path);

    while((entry = readdir(dir))) {
        if((entry->d_type == DT_DIR) &&
                (string(entry->d_name) != string(".")) &&
                (string(entry->d_name) != string("..")))
        {
            string name = path + string(entry->d_name);
            loadMultiplePlugins(name, recursive);
        }
    }
    closedir(dir);
    return true;
}

bool PluginRunner::loadPluginsFromPath(std::string path) {
    if(verbose)
        cout<<"Loading plug-ins from "<<path<<endl;

    if((path.rfind(PATH_SEPERATOR)==string::npos) ||
        (path.rfind(PATH_SEPERATOR)!=path.size()-1))
        path = path + string(PATH_SEPERATOR);

    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(path.c_str())) == NULL) {
        ErrorLogger::Instance().addError("cannot access " + path);
        return false;
    }

    while((entry = readdir(dir))) {
        string name = entry->d_name;
        if(name.size() > 3) {
            // check for windows .dll
            string ext = name.substr(name.size()-3,3);
            if(ext == "dll")
                loadPlugin(path+name);
        }
        if(name.size() > 2) {
            // check for unix .so
            string ext = name.substr(name.size()-2,2);
            if(ext == "so")
                loadPlugin(path+name);
        }
        if(name.size() > 5) {
            // check for mac .dylib
            string ext = name.substr(name.size()-5,5);
            if(ext == "dylib")
                loadPlugin(path+name);
        }
    }
    closedir(dir);
    return true;
}
