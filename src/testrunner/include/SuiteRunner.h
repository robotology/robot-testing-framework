// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_SuiteRunner_H
#define _RTF_SuiteRunner_H

#include <string>
#include <vector>
#include <rtf/TestSuite.h>
#include <PluginRunner.h>
#include <rtf/dll/DllFixturePluginLoader.h>

/**
 * class SuiteRunner
 */
class SuiteRunner : public PluginRunner {

public:

    /**
     * SuiteRunner constructor
     */
    SuiteRunner(bool verbose=false);

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
    bool loadMultipleSuites(std::string path, bool recursive=false);

    /**
     * Clear the test list
     */
    void reset();

private:
    bool loadSuitesFromPath(std::string path);

private:
    bool verbose;
    std::vector<RTF::TestSuite*> suites;
    std::vector<RTF::plugin::DllFixturePluginLoader*> fixtureLoaders;
};

#endif // _RTF_SuiteRunner_H
