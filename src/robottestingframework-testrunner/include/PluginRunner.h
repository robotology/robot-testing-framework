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


#ifndef ROBOTTESTINGFRAMEWORK_PLUGINRUNNER_H
#define ROBOTTESTINGFRAMEWORK_PLUGINRUNNER_H

#include <robottestingframework/PluginLoader.h>
#include <robottestingframework/TestCase.h>
#include <robottestingframework/TestRunner.h>

#include <string>
#include <vector>

/**
 * class PluginRunner
 */
class PluginRunner : public robottestingframework::TestRunner
{

public:
    /**
     * PluginRunner constructor
     */
    PluginRunner(bool verbose = false);

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
    bool loadPlugin(std::string filename,
                    const unsigned int repetition,
                    const std::string param = "",
                    const std::string environment = "");

    /**
     * @brief loadSinglePlugin loads all plugins from the
     * given path
     * @param path the path to the plugin files
     * @param recursive loads from subfolders if true
     * @return true or false upon success or failure
     */
    bool loadMultiplePlugins(std::string path, bool recursive = false);

    /**
     * Clear the test list
     */
    void reset();

protected:
    std::vector<robottestingframework::plugin::PluginLoader*> dllLoaders;

private:
    bool loadPluginsFromPath(std::string path);

private:
    bool verbose;
};

#endif // ROBOTTESTINGFRAMEWORK_PLUGINRUNNER_H
