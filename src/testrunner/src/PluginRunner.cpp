// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <algorithm>
#include <Asserter.h> // used to format the string message
#include <PluginRunner.h>
#include <ErrorLogger.h>
#include <PlatformDir.h>
#include <iostream>

using namespace std;
using namespace RTF;

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
                              const std::string param) {

    DllPluginLoader* loader = new DllPluginLoader();
    TestCase* test = loader->open(filename);
    if(test == NULL) {
        ErrorLogger::Instance().addError(loader->getLastError());
        return false;
    }

    // set the test case param
    test->setParam(param);

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
            if(compare(ext.c_str(), ".dll"))
                loadPlugin(path+name);
        }
        if(name.size() > 3) {
            // check for unix .so
            string ext = name.substr(name.size()-3,3);
            if(compare(ext.c_str(), ".so"))
                loadPlugin(path+name);
        }
        if(name.size() > 6) {
            // check for mac .dylib
            string ext = name.substr(name.size()-6,6);
            if(compare(ext.c_str(), ".dylib"))
                loadPlugin(path+name);
        }
    }
    closedir(dir);
    return true;
}

bool PluginRunner::compare(const char*first,
                           const char* second)
{
    if(!first && !second) return true;
    if(!first || !second) return false;

    string strFirst(first);
    string strSecond(second);
    transform(strFirst.begin(), strFirst.end(), strFirst.begin(),
              (int(*)(int))toupper);
    transform(strSecond.begin(), strSecond.end(), strSecond.begin(),
              (int(*)(int))toupper);

    return (strFirst == strSecond);
}

