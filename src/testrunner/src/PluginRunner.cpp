// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <algorithm>
#include <rtf/Asserter.h> // used to format the string message
#include <PluginRunner.h>
#include <ErrorLogger.h>
#include <PlatformDir.h>
#include <PluginFactory.h>
#include <iostream>

using namespace std;
using namespace RTF;
using namespace RTF::plugin;

PluginRunner::PluginRunner(bool verbose)
    :verbose(verbose) {
}

PluginRunner::~PluginRunner() {
    reset();
}

void PluginRunner::reset() {
    // first reset the TestRunner
    TestRunner::reset();

    // delete all the plugin loader which was created
    for(int i=0; i<dllLoaders.size(); i++)
        delete dllLoaders[i];
    dllLoaders.clear();
}


bool PluginRunner::loadPlugin(std::string filename,
                              const unsigned int repetition,
                              const std::string param,
                              const string environment) {
    PluginLoader* loader = PluginFactory::createByName(filename);
    if(loader == NULL) {
        ErrorLogger::Instance().addError("cannot create any known plug-in loader for " + filename);
        return false;
    }

    TestCase* test = loader->open(filename);
    if(test == NULL) {
        ErrorLogger::Instance().addError(loader->getLastError());
        return false;
    }

    // set the test case param and environment
    test->setParam(param);
    test->setEnvironment(environment);
    test->setRepetition(repetition);

    // add the test case to the TestRunner
    addTest(test);

    // keep track of what have been created
    dllLoaders.push_back(loader);

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
        if(name.size() > 4) {
            // check for windows .dll
            string ext = name.substr(name.size()-4,4);
            if(PluginFactory::compare(ext.c_str(), ".dll"))
                loadPlugin(path+name, 0);
            // check for .lua plugin files
#ifdef ENABLE_LUA_PLUGIN
            if(PluginFactory::compare(ext.c_str(), ".lua"))
                loadPlugin(path+name, 0);
#endif
        }
        if(name.size() > 3) {
            // check for unix .so
            string ext = name.substr(name.size()-3,3);
            if(PluginFactory::compare(ext.c_str(), ".so"))
                loadPlugin(path+name, 0);
        }
        if(name.size() > 6) {
            // check for mac .dylib
            string ext = name.substr(name.size()-6,6);
            if(PluginFactory::compare(ext.c_str(), ".dylib"))
                loadPlugin(path+name, 0);
        }
#ifdef ENABLE_PYTHON_PLUGIN
        // check for .py
        if(name.size() > 2) {
            string ext = name.substr(name.size()-3,3);
             if(PluginFactory::compare(ext.c_str(), ".py"))
                 loadPlugin(path+name, 0);
        }
#endif
#ifdef ENABLE_RUBY_PLUGIN
        // check for .rb
        if(name.size() > 2) {
            string ext = name.substr(name.size()-3,3);
             if(PluginFactory::compare(ext.c_str(), ".rb"))
                 loadPlugin(path+name,0);
        }
#endif
    }
    closedir(dir);
    return true;
}
