/*
 * Robot Testing Framework
 *
 * Copyright (C) 2015-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#include <robottestingframework/Asserter.h> // used to format the string message

#include <ErrorLogger.h>
#include <PlatformDir.h>
#include <PluginFactory.h>
#include <PluginRunner.h>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace robottestingframework;
using namespace robottestingframework::plugin;

PluginRunner::PluginRunner(bool verbose) :
        verbose(verbose)
{
}

PluginRunner::~PluginRunner()
{
    reset();
}

void PluginRunner::reset()
{
    // first reset the TestRunner
    TestRunner::reset();

    // delete all the plugin loader which was created
    for (unsigned int i = 0; i < dllLoaders.size(); i++)
        delete dllLoaders[i];
    dllLoaders.clear();
}


bool PluginRunner::loadPlugin(std::string filename,
                              const unsigned int repetition,
                              const std::string param,
                              const string environment)
{
    PluginLoader* loader = PluginFactory::createByName(filename);
    if (loader == nullptr) {
        ErrorLogger::Instance().addError("cannot create any known plug-in loader for " + filename);
        return false;
    }

    TestCase* test = loader->open(filename);
    if (test == nullptr) {
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
                                       bool recursive)
{
    if (!recursive)
        return loadPluginsFromPath(path);

    // load from subfolders
    if ((path.rfind(PATH_SEPERATOR) == string::npos) || (path.rfind(PATH_SEPERATOR) != path.size() - 1))
        path = path + string(PATH_SEPERATOR);

    DIR* dir;
    struct dirent* entry;
    if ((dir = opendir(path.c_str())) == nullptr) {
        ErrorLogger::Instance().addError("cannot access " + path);
        return false;
    }

    loadPluginsFromPath(path);

    while ((entry = readdir(dir))) {
        if ((entry->d_type == DT_DIR) && (string(entry->d_name) != string(".")) && (string(entry->d_name) != string(".."))) {
            string name = path + string(entry->d_name);
            loadMultiplePlugins(name, recursive);
        }
    }
    closedir(dir);
    return true;
}

bool PluginRunner::loadPluginsFromPath(std::string path)
{
    if (verbose)
        cout << "Loading plug-ins from " << path << endl;

    if ((path.rfind(PATH_SEPERATOR) == string::npos) || (path.rfind(PATH_SEPERATOR) != path.size() - 1))
        path = path + string(PATH_SEPERATOR);

    DIR* dir;
    struct dirent* entry;
    if ((dir = opendir(path.c_str())) == nullptr) {
        ErrorLogger::Instance().addError("cannot access " + path);
        return false;
    }

    while ((entry = readdir(dir))) {
        string name = entry->d_name;
        if (name.size() > 4) {
            // check for windows .dll
            string ext = name.substr(name.size() - 4, 4);
            if (PluginFactory::compare(ext.c_str(), ".dll"))
                loadPlugin(path + name, 0);
                // check for .lua plugin files
#ifdef ENABLE_LUA_PLUGIN
            if (PluginFactory::compare(ext.c_str(), ".lua"))
                loadPlugin(path + name, 0);
#endif
        }
        if (name.size() > 3) {
            // check for unix .so
            string ext = name.substr(name.size() - 3, 3);
            if (PluginFactory::compare(ext.c_str(), ".so"))
                loadPlugin(path + name, 0);
        }
#ifdef ENABLE_PYTHON_PLUGIN
        // check for .py
        if (name.size() > 2) {
            string ext = name.substr(name.size() - 3, 3);
            if (PluginFactory::compare(ext.c_str(), ".py"))
                loadPlugin(path + name, 0);
        }
#endif
#ifdef ENABLE_RUBY_PLUGIN
        // check for .rb
        if (name.size() > 2) {
            string ext = name.substr(name.size() - 3, 3);
            if (PluginFactory::compare(ext.c_str(), ".rb"))
                loadPlugin(path + name, 0);
        }
#endif
    }
    closedir(dir);
    return true;
}
