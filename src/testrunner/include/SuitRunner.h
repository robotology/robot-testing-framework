// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_SuitRunner_H
#define _RTF_SuitRunner_H

#include <string>
#include <vector>
#include <TestSuit.h>
#include <PluginRunner.h>

/**
 * class SuitRunner
 */
class SuitRunner : public PluginRunner {

public:

    /**
     * SuitRunner constructor
     */
    SuitRunner(bool verbose=false);

    /**
     *  SuitRunner destructor
     */
    virtual ~SuitRunner();

    /**
     * @brief loadSuit loads a single test suit (xml file)
     * @param filename the xml file name
     * @return true or false upon success or failure
     */
    bool loadSuit(std::string filename);

    /**
     * @brief loadMultipleSuits loads all test suits from the
     * given path
     * @param path the path to the test suits xml files
     * @param recursive loads from subfolders if true
     * @return true or false upon success or failure
     */
    bool loadMultipleSuits(std::string path, bool recursive=false);

    /**
     * Clear the test list
     */
    void reset();

private:
    bool loadSuitsFromPath(std::string path);
    bool compare(const char *first, const char *second);

private:
    bool verbose;    
    std::vector<RTF::TestSuit*> suits;
};

#endif // _RTF_SuitRunner_H
