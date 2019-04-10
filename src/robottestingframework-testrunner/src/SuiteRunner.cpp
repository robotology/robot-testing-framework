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
#include <robottestingframework/dll/DllFixturePluginLoader.h>

#include <ErrorLogger.h>
#include <PlatformDir.h>
#include <PluginFactory.h>
#include <SuiteRunner.h>
#include <tinyxml.h>

using namespace std;
using namespace robottestingframework;
using namespace robottestingframework::plugin;

SuiteRunner::SuiteRunner(bool verbose) :
        PluginRunner(verbose),
        verbose(verbose)
{
}

SuiteRunner::~SuiteRunner()
{
    reset();
}

void SuiteRunner::reset()
{
    // first reset the PluginRunner
    PluginRunner::reset();

    // delete all the suites which was created
    for (auto& suite : suites) {
        delete suite;
    }
    suites.clear();

    // delete all the fixture plugin loader which was created
    for (auto& fixtureLoader : fixtureLoaders) {
        delete fixtureLoader;
    }
    fixtureLoaders.clear();
}

bool SuiteRunner::loadSuite(std::string filename)
{
    if (verbose) {
        cout << "Loading " << filename << endl;
    }

    ErrorLogger& logger = ErrorLogger::Instance();

    // loading xml file
    TiXmlDocument doc(filename.c_str());

    // it seems TinyXML throw an exception when
    // trying to open a directory instead of a file!
    bool bOK;
    try {
        bOK = doc.LoadFile();
    } catch (...) {
        string error = Asserter::format("Caught an exception while trying to open suite '%s'. (Is it a XML file?)",
                                        filename.c_str());
        logger.addError(error);
        return false;
    }

    if (!bOK) {
        string error = Asserter::format("Syntax error while loading '%s' at line %d. (%s)",
                                        filename.c_str(),
                                        doc.ErrorRow(),
                                        doc.ErrorDesc());
        logger.addError(error);
        return false;
    }

    //retrieving root element
    TiXmlElement* root = doc.RootElement();
    if (root == nullptr) {
        string error = Asserter::format("Syntax error while loading '%s'. (No root element)",
                                        filename.c_str());
        logger.addError(error);
        return false;
    }

    bool rootTagIsSuite = PluginFactory::compare(root->Value(), "suite");

    if (!rootTagIsSuite) {
        if (verbose) {
            cout << filename << " is not a test suite file!" << endl;
        }
        return false;
    }

    std::string environment;
    std::string name = (root->Attribute("name")) != nullptr ? root->Attribute("name") : "unknown";
    TestSuite* suite = new TestSuite(name);

    // retrieving test cases
    for (TiXmlElement* test = root->FirstChildElement(); test != nullptr;
         test = test->NextSiblingElement()) {
        if (PluginFactory::compare(test->Value(), "description")) {
            if (test->GetText() != nullptr) {
                suite->setDescription(test->GetText());
            }
        } else if (PluginFactory::compare(test->Value(), "environment")) {
            if (test->GetText() != nullptr) {
                environment = test->GetText();
            }
        } else if (PluginFactory::compare(test->Value(), "fixture") && test->GetText() != nullptr) {
            // load the fixture manager plugin
            auto* loader = new DllFixturePluginLoader();
            std::string pluginName = test->GetText();

            FixtureManager* fixture = loader->open(pluginName);
            if (fixture != nullptr) {
                // set the fixture manager param
                if (test->Attribute("param") != nullptr) {
                    fixture->setParam(test->Attribute("param"));
                }
                // set the fixture manager for the current suite
                suite->addFixtureManager(fixture);
                // keep track of the created plugin loaders
                fixtureLoaders.push_back(loader);
            } else {
                logger.addError(loader->getLastError());
                delete loader;
                // stop going on if the fixture manager cannot be loaded
                delete suite;
                return false;
            }
        } else if (PluginFactory::compare(test->Value(), "test") && test->GetText() != nullptr) {

            PluginLoader* loader;
            std::string pluginName = test->GetText();
            if (test->Attribute("type") != nullptr) {
                loader = PluginFactory::createByType(test->Attribute("type"));
            } else {
                loader = PluginFactory::createByName(test->GetText());
            }

            if (loader == nullptr) {
                ErrorLogger::Instance().addError("cannot create any known plug-in loader for " + pluginName);
                continue;
            }
            TestCase* testcase = loader->open(pluginName);

            if (testcase != nullptr) {
                // set the test case environment
                testcase->setEnvironment(environment);
                // set the test case param
                if (test->Attribute("param") != nullptr) {
                    testcase->setParam(test->Attribute("param"));
                }
                // set the test case repetition
                if (test->Attribute("repetition") != nullptr) {
                    char* endptr;
                    auto rep = (unsigned int)strtol(test->Attribute("repetition"), &endptr, 10);
                    if (endptr == nullptr) {
                        testcase->setRepetition(rep);
                    } else {
                        string error = Asserter::format("Invalid repetition attribute while loading '%s' at line %d. (%s)",
                                                        filename.c_str(),
                                                        doc.ErrorRow(),
                                                        doc.ErrorDesc());
                        logger.addError(error);
                        continue;
                    }
                }
                // add the test to the suite
                suite->addTest(testcase);
                // keep track of the created plugin loaders
                dllLoaders.push_back(loader);
            } else {
                logger.addError(loader->getLastError());
                delete loader;
            }
        }
    }

    // add the test suite to the TestRunner
    addTest(suite);
    // keep tracks of the created suites
    suites.push_back(suite);
    return true;
}

bool SuiteRunner::loadMultipleSuites(std::string path,
                                     bool recursive)
{
    if (!recursive) {
        return loadSuitesFromPath(path);
    }

    // load from subfolders
    if ((path.rfind(PATH_SEPERATOR) == string::npos) || (path.rfind(PATH_SEPERATOR) != path.size() - 1)) {
        path = path + string(PATH_SEPERATOR);
    }

    DIR* dir;
    struct dirent* entry;
    if ((dir = opendir(path.c_str())) == nullptr) {
        ErrorLogger::Instance().addError("cannot access " + path);
        return false;
    }

    loadSuitesFromPath(path);

    while ((entry = readdir(dir)) != nullptr) {
        if ((entry->d_type == DT_DIR) && (string(entry->d_name) != string(".")) && (string(entry->d_name) != string(".."))) {
            string name = path + string(entry->d_name);
            loadMultipleSuites(name, recursive);
        }
    }
    closedir(dir);
    return true;
}

bool SuiteRunner::loadSuitesFromPath(std::string path)
{
    if (verbose) {
        cout << "Loading suites from " << path << endl;
    }

    if ((path.rfind(PATH_SEPERATOR) == string::npos) || (path.rfind(PATH_SEPERATOR) != path.size() - 1)) {
        path = path + string(PATH_SEPERATOR);
    }

    DIR* dir;
    struct dirent* entry;
    if ((dir = opendir(path.c_str())) == nullptr) {
        ErrorLogger::Instance().addError("cannot access " + path);
        return false;
    }

    while ((entry = readdir(dir)) != nullptr) {
        string name = entry->d_name;
        if (name.size() > 4) {
            // check for xml file
            string ext = name.substr(name.size() - 4, 4);
            if (PluginFactory::compare(ext.c_str(), ".xml")) {
                loadSuite(path + name);
            }
        }
    }
    closedir(dir);
    return true;
}
