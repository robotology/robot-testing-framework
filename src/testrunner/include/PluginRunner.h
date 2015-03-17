// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_PLUGINRUNNER_H
#define _RTF_PLUGINRUNNER_H

#include <string>
#include <vector>
#include <TestRunner.h>
#include <TestCase.h>
#include <DllPluginLoader.h>

/**
 * class PluginRunner
 */
class PluginRunner : public RTF::TestRunner {

public:

    /**
     * PluginRunner constructor
     */
    PluginRunner(bool verbose=false);

    /**
     *  PluginRunner destructor
     */
    virtual ~PluginRunner();

    /**
     * @brief loadPlugin loads a single test plugin
     * @param filename the plugin file name
     * @param param the optional test case parameter
     * @return true or false upon success or failure
     */
    bool loadPlugin(std::string filename, const std::string param="");

    /**
     * @brief loadSinglePlugin loads all plugins from the
     * given path
     * @param path the path to the plugin files
     * @param recursive loads from subfolders if true
     * @return true or false upon success or failure
     */
    bool loadMultiplePlugins(std::string path, bool recursive=false);

    /**
     * Clear the test list
     */
    void reset();

protected:
    bool compare(const char *first, const char *second);    
    std::vector<RTF::DllPluginLoader*> dllLoaders;

private:
    bool loadPluginsFromPath(std::string path);    

private:
    bool verbose;    
};

#endif // _RTF_PLUGINRUNNER_H
