// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <Asserter.h> // used to format the string message
#include <SuitRunner.h>
#include <ErrorLogger.h>
#include <PlatformDir.h>
#include <iostream>
#include <tinyxml.h>

using namespace std;
using namespace RTF;

SuitRunner::SuitRunner(bool verbose)
    : PluginRunner(verbose),
      verbose(verbose) {
}

SuitRunner::~SuitRunner() {
    reset();
}

void SuitRunner::reset() {
    // first reset the PluginRunner
    PluginRunner::reset();

    // delete all the suits which was created
    for(int i=0; i<suits.size(); i++)
        delete suits[i];
    suits.clear();
}

bool SuitRunner::loadSuit(std::string filename) {
    if(verbose)
        cout<<"Loading "<<filename<<endl;

    ErrorLogger& logger = ErrorLogger::Instance();

    // loading xml file
    TiXmlDocument doc(filename.c_str());

    // it seems TinyXML throw an exception when
    // trying to open a directory instead of a file!
    bool bOK;
    try {
        bOK = doc.LoadFile();
    }
    catch(...) {
        string error = Asserter::format("Caught an exception while trying to open suit '%s'. (Is it a XML file?)",
                                        filename.c_str());
        logger.addError(error);
        return false;
    }

    if(!bOK) {
        string error = Asserter::format("Syntax error while loading '%s' at line %d. (%s)",
                                        filename.c_str(), doc.ErrorRow(), doc.ErrorDesc());
        logger.addError(error);
        return false;
    }

    //retrieving root element
    TiXmlElement *root = doc.RootElement();
    if(!root) {
        string error = Asserter::format("Syntax error while loading '%s'. (No root element)",
                                        filename.c_str());
        logger.addError(error);
        return false;
    }

    if(!compare(root->Value(), "suit")) {
        if(verbose)
            cout<<filename<<" is not a test suit file!"<<endl;
        return false;
    }

    std::string name = (root->Attribute("name")) ? root->Attribute("name") : "unknown";
    TestSuit* suit = new TestSuit(name);

    // retrieving test cases
    for(TiXmlElement* test = root->FirstChildElement(); test;
        test = test->NextSiblingElement())
    {
        if(compare(test->Value(), "test")) {            
            // load the plugin and add it to the suit
            PluginRunner::Plugin* plugin = openPlugin(test->GetText());
            if(plugin) {
                // set the test case param
                if(test->Attribute("param"))
                    plugin->test.getContent().setParam(test->Attribute("param"));
                // keep track of the created plugins
                plugins.push_back(plugin);
                // add the test to the suit
                suit->addTest(&plugin->test.getContent());
            }
        }
    }

    // add the test suit to the TestRunner
    addTest(suit);
    // keep tracks of the created suits
    suits.push_back(suit);
    return true;
}

bool SuitRunner::loadMultipleSuits(std::string path,
                                         bool recursive) {
    if(!recursive)
        return loadSuitsFromPath(path);

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

    loadSuitsFromPath(path);

    while((entry = readdir(dir))) {
        if((entry->d_type == DT_DIR) &&
                (string(entry->d_name) != string(".")) &&
                (string(entry->d_name) != string("..")))
        {
            string name = path + string(entry->d_name);
            loadMultipleSuits(name, recursive);
        }
    }
    closedir(dir);    
    return true;
}

bool SuitRunner::loadSuitsFromPath(std::string path) {
    if(verbose)
        cout<<"Loading suits from "<<path<<endl;

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
            // check for xml file
            string ext = name.substr(name.size()-4,4);
            if(compare(ext.c_str(), ".xml"))
                loadSuit(path+name);
        }
    }
    closedir(dir);
    return true;
}
