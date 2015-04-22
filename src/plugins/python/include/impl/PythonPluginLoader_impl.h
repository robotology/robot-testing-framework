// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_PYTHONPLUGINLOADER_IMPL_H
#define _RTF_PYTHONPLUGINLOADER_IMPL_H

#include <Python.h>
#include <string>
#include <TestCase.h>

namespace RTF {
    namespace plugin {
        class PythonPluginLoaderImpl;
    }
}

/**
 * @brief The PythonPluginLoaderImpl loads a Pthyon test case plug-in and
 * gives the direct access to the TestCase.
 */
class RTF::plugin::PythonPluginLoaderImpl : public RTF::TestCase{

public:

    /**
     * PythonPluginLoaderImpl constructor
     */
    PythonPluginLoaderImpl();

    /**
     *  PythonPluginLoaderImpl destructor
     */
    virtual ~PythonPluginLoaderImpl();

    /**
     * @brief open Loads a test case plugin
     * @param filename the plugin filename
     * @return A pointer to the test case loaded from the
     * plugin or a null pointer in case of failure.
     */
    RTF::TestCase* open(const std::string filename);

    /**
     * @brief close Unloads the plugin and deletes any
     * allocated memory.
     */
    void close();

    /**
     * @brief getLastError gets the last error if any.
     * @return returns the last error string.
     */
    const std::string getLastError();

    /**
     * @brief getFileName returns the loaded script file name
     * @return the script file name
     */
    const std::string getFileName();

    /**
     * @brief setTestName set the test case name
     * @param name the test case name
     */
    void setTestName(const std::string name);

    virtual bool setup(int argc, char**argv);

    virtual void tearDown();

    virtual void run();


private:
    PyObject *pyName;
    PyObject *pyModule;
    PyObject *pyDict;

private:    
    std::string filename;
    std::string error;    
};

#endif // _RTF_PYTHONPLUGINLOADER_IMPL_H
