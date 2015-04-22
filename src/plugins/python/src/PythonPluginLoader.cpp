// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#include <PythonPluginLoader_impl.h>
#include <PythonPluginLoader.h>
#include <Plugin.h>
#include <Asserter.h>
#include <TestAssert.h>

#ifdef _WIN32
    #include <stdlib.h>
#else
    #include <libgen.h>
#endif
using namespace std;
using namespace RTF;
using namespace RTF::plugin;


/**
 * @brief PythonPluginLoaderImpl
 */

PythonPluginLoaderImpl::PythonPluginLoaderImpl()
    : TestCase(""), pyName(NULL) {

}

PythonPluginLoaderImpl::~PythonPluginLoaderImpl() {
    close();
}

void PythonPluginLoaderImpl::close() {
    // Clean up
    if(pyModule) {
         Py_DECREF(pyModule);
         pyModule = NULL;
    }
    if(pyName) {
        Py_DECREF(pyName);
        pyName = NULL;
    }

    // Finish the Python Interpreter
    Py_Finalize();
}

TestCase* PythonPluginLoaderImpl::open(const std::string filename) {
    close();
    this->filename = filename;

    // Initialize the Python Interpreter
    Py_Initialize();

    // extending python system path
#ifdef _WIN32
    string dname = ".";
    string bname = filename;
#else
    char* dir = strdup(filename.c_str());
    char* name = strdup(filename.c_str());
    string dname = dirname(dir);
    string bname = basename(name);
#endif
    PyRun_SimpleString("import sys");
    string sys_path = "sys.path.append(\"" + dname + "\")";
    PyRun_SimpleString(sys_path.c_str());

    // catch errors
    PyObject *ptype, *pvalue, *ptraceback;
    PyErr_Fetch(&ptype, &pvalue, &ptraceback);
    PyErr_Clear();

    // remove the file extention if exist
    int lastindex = bname.find_last_of(".");
    string rawname = bname.substr(0, lastindex);

    // Build the name object
    printf("rawname: %s\n", rawname.c_str());
    pyName = PyString_FromString(rawname.c_str());
    printf("loading %s ...\n", filename.c_str());
    if(pyName == NULL) {
        error = Asserter::format("Cannot load %s because %s",
                                 filename.c_str(), PyString_AsString(pvalue));
        close();
        return NULL;
    }

    // Load the module object
    pyModule = PyImport_Import(pyName);
    if(pyModule == NULL) {
        //error = Asserter::format("Cannot load %s because %s",
        //                         filename.c_str(), PyString_AsString(pvalue));
        PyErr_Print();
        close();
        return NULL;
    }
/*
    // pyDict is a borrowed reference
    pyDict = PyModule_GetDict(pyModule);
    if(pyDict == NULL) {
        error = Asserter::format("Cannot load %s because %s",
                                 filename.c_str(), PyString_AsString(pvalue));
        close();
        return NULL;
    }
*/

    Py_XDECREF(ptype);
    Py_XDECREF(pvalue);
    Py_XDECREF(ptraceback);
    return this;
}

void PythonPluginLoaderImpl::setTestName(const std::string name) {
    Test::setName(name);
}

const std::string PythonPluginLoaderImpl::getLastError() {

    return error;
}

const std::string PythonPluginLoaderImpl::getFileName() {
    return filename;
}

bool PythonPluginLoaderImpl::setup(int argc, char**argv) {

    return true;
}

// TODO: in the Lua test plugin, the teardown will not be called
//       after any exception. This is not coherent with the c++
//       implementaion of test cases.
void PythonPluginLoaderImpl::tearDown() {

}

void PythonPluginLoaderImpl::run() {

}


/*
int PythonPluginLoaderImpl::setName(lua_State* L) {
    return 0;
}

int PythonPluginLoaderImpl::assertError(lua_State* L) {
    return 0;
}

int PythonPluginLoaderImpl::assertFail(lua_State* L) {
    return 0;
}

int PythonPluginLoaderImpl::testReport(lua_State* L) {
    return 0;
}

int PythonPluginLoaderImpl::testFail(lua_State* L) {
    return 0;
}
*/

/**
 * @brief PythonPluginLoader
 */
PythonPluginLoader::PythonPluginLoader()
    : implementaion(NULL) { }

PythonPluginLoader::~PythonPluginLoader() {
    close();
}

void PythonPluginLoader::close() {
    if(implementaion)
        delete ((PythonPluginLoaderImpl*)implementaion);
    implementaion = NULL;
}

TestCase* PythonPluginLoader::open(const std::string filename) {
    close();
    implementaion = new PythonPluginLoaderImpl();
    return ((PythonPluginLoaderImpl*)implementaion)->open(filename);
}

const std::string PythonPluginLoader::getLastError() {
    if(implementaion)
        return ((PythonPluginLoaderImpl*)implementaion)->getLastError();
    return string("");
}

