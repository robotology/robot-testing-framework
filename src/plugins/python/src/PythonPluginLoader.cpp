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

    // remove the file extention if exist
    int lastindex = bname.find_last_of(".");
    string rawname = bname.substr(0, lastindex);

    // Build the name object    
    pyName = PyString_FromString(rawname.c_str());    
    if(pyName == NULL) {
        error = Asserter::format("Cannot load %s because %s",
                                 filename.c_str(), getPythonErrorString().c_str());
        close();
        return NULL;
    }

    // Load the module object        
    pyModule = PyImport_Import(pyName);
    if(pyModule == NULL) {
        error = Asserter::format("Cannot load %s because %s",
                                 filename.c_str(), getPythonErrorString().c_str());
        close();
        return NULL;
    }

    // pyDict is a borrowed reference
    pyDict = PyModule_GetDict(pyModule);
    if(pyDict == NULL) {
        error = Asserter::format("Cannot load %s because %s",
                                 filename.c_str(), getPythonErrorString().c_str());
        close();
        return NULL;
    }

    // Build the name of a callable class
    pyClass = PyDict_GetItemString(pyDict, "TestCase");
    if(pyClass == NULL) {
        error = Asserter::format("Cannot find any instance of class TestCase");
        close();
        return NULL;
    }

     // Create an instance of the class
     if (!PyCallable_Check(pyClass) ||
             (pyInstance = PyObject_CallObject(pyClass, NULL)) == NULL) {
         error = Asserter::format("TestCase is not defined as a class");
         close();
         return NULL;
     }

    return this;
}

std::string PythonPluginLoaderImpl::getPythonErrorString() {
    std::string strError;
    // Extra paranoia...
    if (!PyErr_Occurred())
      return strError;

    //PyErr_Print();
    PyObject *type , *value, *traceback, *pyString;
    type = value = traceback = pyString = NULL;

    PyErr_Fetch(&type, &value, &traceback);
    PyErr_Clear();
    if (value != NULL &&
            (pyString=PyObject_Str(value))!=NULL &&
            (PyString_Check(pyString))) {
      strError = PyString_AsString(pyString);
    } else
      strError = "<unknown exception value>";
    Py_XDECREF(pyString);

    if (type != NULL &&
            (pyString=PyObject_Str(type))!=NULL &&
            (PyString_Check(pyString)))
      strError += string("; ") + PyString_AsString(pyString);
    else
      strError = " <unknown exception type>";
    Py_XDECREF(pyString);

    if (traceback != NULL && PyTraceBack_Check(traceback)) {
        strError = "traceback";
    }
    Py_XDECREF(type);
    Py_XDECREF(value);
    Py_XDECREF(traceback);
    return strError;
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
    char method[] = "setup";
    PyObject* arglist = PyList_New(argc);
    if(arglist == NULL) {
        error = Asserter::format("Cannot create arguments because %s",
                                  getPythonErrorString().c_str());
        return false;
    }
    for (int i=0; i<argc; i++) {
        PyObject *str = PyString_FromString(argv[i]);
        if (str == NULL) {
            Py_DECREF(arglist);
            error = Asserter::format("Cannot create arguments because %s",
                                      getPythonErrorString().c_str());
            return false;
        }
        PyList_SET_ITEM(arglist, i, str);
    }

    //PyObject_CallFunction()
    PyObject* pyValue = PyObject_CallMethod(pyInstance, method, NULL);
    if(pyValue == NULL) {
        error = Asserter::format("Cannot call the run() method because %s",
                                  getPythonErrorString().c_str());
        return false;
    }

    Py_DECREF(arglist);
    Py_DECREF(pyValue);
    return true;
}

void PythonPluginLoaderImpl::tearDown() {

}

void PythonPluginLoaderImpl::run() {
    char method[] = "run";
    PyObject* pyValue = PyObject_CallMethod(pyInstance, method, NULL);
    if(pyValue == NULL) {
        error = Asserter::format("Cannot call the run() method because %s",
                                  getPythonErrorString().c_str());
    }
    else
        Py_DECREF(pyValue);
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

