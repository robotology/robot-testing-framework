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


#ifndef ROBOTTESTINGFRAMEWORK_SuiteRunner_H
#define ROBOTTESTINGFRAMEWORK_SuiteRunner_H

#include <robottestingframework/TestSuite.h>
#include <robottestingframework/dll/DllFixturePluginLoader.h>

#include <PluginRunner.h>
#include <string>
#include <vector>

/**
 * class SuiteRunner
 */
class SuiteRunner : public PluginRunner
{

public:
    /**
     * SuiteRunner constructor
     */
    SuiteRunner(bool verbose = false);

    /**
     *  SuiteRunner destructor
     */
    virtual ~SuiteRunner();

    /**
     * @brief loadSuite loads a single test suite (xml file)
     * @param filename the xml file name
     * @return true or false upon success or failure
     */
    bool loadSuite(std::string filename);

    /**
     * @brief loadMultipleSuites loads all test suites from the
     * given path
     * @param path the path to the test suites xml files
     * @param recursive loads from subfolders if true
     * @return true or false upon success or failure
     */
    bool loadMultipleSuites(std::string path, bool recursive = false);

    /**
     * Clear the test list
     */
    void reset();

private:
    bool loadSuitesFromPath(std::string path);

private:
    bool verbose;
    std::vector<robottestingframework::TestSuite*> suites;
    std::vector<robottestingframework::plugin::DllFixturePluginLoader*> fixtureLoaders;
};

#endif // ROBOTTESTINGFRAMEWORK_SuiteRunner_H
