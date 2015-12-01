// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <rtf/Asserter.h> // used to format the string message
#include <SuitRunner.h>
#include <ErrorLogger.h>
#include <PlatformDir.h>
#include <tinyxml.h>
#include <PluginFactory.h>
#include <rtf/dll/DllFixturePluginLoader.h>

using namespace std;
using namespace RTF;
using namespace RTF::plugin;

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

    // delete all the fixture plugin loader which was created
    for(int i=0; i<fixtureLoaders.size(); i++)
        delete fixtureLoaders[i];
    fixtureLoaders.clear();
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

    if(!PluginFactory::compare(root->Value(), "suit")) {
        if(verbose)
            cout<<filename<<" is not a test suit file!"<<endl;
        return false;
    }

    std::string environment;
    std::string name = (root->Attribute("name")) ? root->Attribute("name") : "unknown";
    TestSuit* suit = new TestSuit(name);

    // retrieving test cases
    for(TiXmlElement* test = root->FirstChildElement(); test;
        test = test->NextSiblingElement())
    {
        if(PluginFactory::compare(test->Value(), "description")) {
            if(test->GetText() != NULL)
                suit->setDescription(test->GetText());
        }
        else if(PluginFactory::compare(test->Value(), "environment")) {
            if(test->GetText() != NULL)
                environment = test->GetText();
        }
        else if(PluginFactory::compare(test->Value(), "fixture") &&
                test->GetText() != NULL) {
                // load the fixture manager plugin
                DllFixturePluginLoader* loader = new DllFixturePluginLoader();
                std::string pluginName = test->GetText();

#ifdef _WIN32
                pluginName =  pluginName + ".dll";
#elif __APPLE__
                pluginName =  pluginName + ".dylib";
#else
                pluginName =  pluginName + ".so";
#endif
                FixtureManager* fixture = loader->open(pluginName);
                if(fixture != NULL) {
                    // set the fixture manager param
                    if(test->Attribute("param"))
                        fixture->setParam(test->Attribute("param"));
                    // set the fixture manager for the current suit
                    suit->setFixtureManager(fixture);
                    // keep track of the created plugin loaders
                    fixtureLoaders.push_back(loader);
                }
                else {
                    logger.addError(loader->getLastError());
                    delete loader;
                    // stop going on if the fixture manager cannot be loaded
                    delete suit;
                    return false;
                }
        }
        else if(PluginFactory::compare(test->Value(), "test") &&
                test->GetText() != NULL) {

            PluginLoader* loader;
            std::string pluginName = test->GetText();
            if(test->Attribute("type")) {
                loader = PluginFactory::createByType(test->Attribute("type"));
                if(PluginFactory::compare(test->Attribute("type"), "dll")) {
#ifdef _WIN32
                   pluginName =  pluginName + ".dll";
#elif __APPLE__
                    pluginName =  pluginName + ".dylib";
#else
                    pluginName =  pluginName + ".so";
#endif
                }
            }
            else
                loader = PluginFactory::createByName(test->GetText());

            if(loader == NULL) {
                ErrorLogger::Instance().addError("cannot create any known plug-in loader for " +
                                                 pluginName);
                continue;
            }
            TestCase* testcase = loader->open(pluginName);

            if(testcase != NULL) {
                // set the test case environment
                testcase->setEnvironment(environment);
                // set the test case param
                if(test->Attribute("param"))
                    testcase->setParam(test->Attribute("param"));
                // set the test case repetition
                if(test->Attribute("repetition")) {
                    char *endptr;
                    unsigned int rep = (unsigned int) strtol(test->Attribute("repetition"), &endptr, 10);
                    if (endptr == 0 && rep >= 0) {
                        testcase->setRepetition(rep);
                    }
                    else {
                        string error = Asserter::format("Invalid repetition attribute while loading '%s' at line %d. (%s)",
                                                        filename.c_str(), doc.ErrorRow(), doc.ErrorDesc());
                        logger.addError(error);
                        continue;
                    }
                }
                // add the test to the suit
                suit->addTest(testcase);
                // keep track of the created plugin loaders
                dllLoaders.push_back(loader);
            }
            else {
                logger.addError(loader->getLastError());
                delete loader;
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
            if(PluginFactory::compare(ext.c_str(), ".xml"))
                loadSuit(path+name);
        }
    }
    closedir(dir);
    return true;
}
