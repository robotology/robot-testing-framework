// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <rtf/python/impl/PythonPluginLoader_impl.h>
#include <rtf/python/PythonPluginLoader.h>
#include <rtf/dll/Plugin.h>
#include <rtf/Asserter.h>
#include <rtf/TestAssert.h>

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


PyMethodDef PythonPluginLoaderImpl::testPythonMethods[] = {
     {"setName", PythonPluginLoaderImpl::setName, METH_VARARGS, "Setting the test name."},
     {"assertError", PythonPluginLoaderImpl::assertError, METH_VARARGS, "Error assertion."},
     {"assertFail", PythonPluginLoaderImpl::assertFail, METH_VARARGS, "Failure assertion."},
     {"testReport", PythonPluginLoaderImpl::testReport, METH_VARARGS, "report a test message."},
     {"testCheck", PythonPluginLoaderImpl::testCheck, METH_VARARGS, "report failure message with condition."},
     {NULL, NULL, 0, NULL}
};


PythonPluginLoaderImpl::PythonPluginLoaderImpl()
    : TestCase(""){
    pyName = pyModule =  pyModuleRTF = pyCapsuleRTF = NULL;
}

PythonPluginLoaderImpl::~PythonPluginLoaderImpl() {
    close();
}

void PythonPluginLoaderImpl::close() {
    // Clean up
    if(pyCapsuleRTF) {
        Py_DECREF(pyCapsuleRTF);
        pyName = NULL;
    }
    if(pyModuleRTF) {
        Py_DECREF(pyModuleRTF);
        pyName = NULL;
    }
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

    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    _splitpath_s(filename.c_str(),
                 drive, _MAX_DRIVE,
                 dir, _MAX_DIR,
                 fname, _MAX_FNAME,
                 ext, _MAX_EXT);
    string dname = string(drive) + string(dir);
    for(size_t i=0; i<dname.size(); i++)
        dname[i] = (dname[i] == '\\') ? '/' : dname[i];
    string bname = fname;
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
    size_t lastindex = bname.find_last_of(".");
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


    // store the current instance of PythonPluginLoaderImpl
    // register the extended methods and import the 'rtf'
    PyObject* pyCapsuleRTF = PyCapsule_New(this, "PythonPluginLoaderImpl", NULL);
    //(void) Py_InitModule("rtf", testPythonMethods);
    Py_InitModule4("rtf", testPythonMethods, (char *)NULL,
                   pyCapsuleRTF, PYTHON_API_VERSION);
    PyObject *pyModuleRTF = PyImport_Import(PyString_FromString("rtf"));
    PyModule_AddObject(pyModuleRTF, "PythonPluginLoaderImpl", pyCapsuleRTF);
    PyModule_AddObject(pyModule, "RTF", pyModuleRTF);

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

    setTestName(bname);
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
        strError = "Syntax Error!";
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
    PyObject* func = PyObject_GetAttrString(pyInstance, "setup");
    if(func == NULL)
        return true;


    PyObject* arglist = PyTuple_New(argc);
    if(arglist == NULL) {
        error = Asserter::format("Cannot create arguments because %s",
                                  getPythonErrorString().c_str());
        RTF_ASSERT_ERROR(error);
    }
    for (int i=0; i<argc; i++) {
        PyObject *str = PyString_FromString(argv[i]);
        if (str == NULL) {
            Py_DECREF(arglist);
            error = Asserter::format("Cannot create arguments because %s",
                                      getPythonErrorString().c_str());
            RTF_ASSERT_ERROR(error);
        }
        PyTuple_SetItem(arglist, i, str);
    }

    PyObject* pyValue = PyObject_CallObject(func, arglist);
    if(pyValue == NULL) {
        error = Asserter::format("Cannot call the setup() method because %s",
                                  getPythonErrorString().c_str());
        Py_DECREF(arglist);
        RTF_ASSERT_ERROR(error);
    }

    // TODO: ensure the return value type
    bool ret = (PyObject_IsTrue(pyValue) == 1);
    Py_DECREF(arglist);
    Py_DECREF(pyValue);
    return ret;
}

void PythonPluginLoaderImpl::tearDown() {
    PyObject* func = PyObject_GetAttrString(pyInstance, "tearDown");
    if(func == NULL)
        return;

    char method[] = "tearDown";
    PyObject* pyValue = PyObject_CallMethod(pyInstance, method, NULL);
    if(pyValue == NULL) {
        error = Asserter::format("Cannot call the tearDown() method because %s",
                                  getPythonErrorString().c_str());
        RTF_ASSERT_ERROR(error);
    }

    Py_DECREF(pyValue);
}

void PythonPluginLoaderImpl::run() {
    char method[] = "run";
    PyObject* pyValue = PyObject_CallMethod(pyInstance, method, NULL);
    if(pyValue == NULL) {
        error = Asserter::format("Cannot call the run() method because %s",
                                  getPythonErrorString().c_str());
        RTF_ASSERT_ERROR(error);
    }

    Py_DECREF(pyValue);
}


PyObject* PythonPluginLoaderImpl::setName(PyObject* self,
                                          PyObject* args) {
    const char* name;
    PythonPluginLoaderImpl* impl =
            (PythonPluginLoaderImpl*) PyCapsule_GetPointer(self, "PythonPluginLoaderImpl");
    RTF_ASSERT_ERROR_IF_FALSE(impl != NULL, "The setName cannot find the instance of PythonPluginLoaderImpl");
    if (!PyArg_ParseTuple(args, "s", &name)) {
        RTF_ASSERT_ERROR(Asserter::format("setName() is called with the wrong paramters."));
    }
    impl->setTestName(name);
    Py_RETURN_NONE;
}



PyObject* PythonPluginLoaderImpl::assertError(PyObject* self,
                                              PyObject* args) {
    const char* message;
    PythonPluginLoaderImpl* impl =
            (PythonPluginLoaderImpl*) PyCapsule_GetPointer(self, "PythonPluginLoaderImpl");
    RTF_ASSERT_ERROR_IF_FALSE(impl != NULL, "The setName cannot find the instance of PythonPluginLoaderImpl");

    if (!PyArg_ParseTuple(args, "s", &message)) {
        RTF_ASSERT_ERROR(Asserter::format("assertError() is called with the wrong paramters."));
    }
    //impl->close();
    RTF::Asserter::error(RTF::TestMessage("asserts error with exception",
                                          message, impl->getFileName(), 0));
    Py_RETURN_NONE;
}


PyObject* PythonPluginLoaderImpl::assertFail(PyObject* self,
                                              PyObject* args) {
    const char* message;
    PythonPluginLoaderImpl* impl =
            (PythonPluginLoaderImpl*) PyCapsule_GetPointer(self, "PythonPluginLoaderImpl");
    RTF_ASSERT_ERROR_IF_FALSE(impl != NULL, "The setName cannot find the instance of PythonPluginLoaderImpl");

    if (!PyArg_ParseTuple(args, "s", &message)) {
        RTF_ASSERT_ERROR(Asserter::format("assertError() is called with the wrong paramters."));
    }
    RTF::Asserter::fail(RTF::TestMessage("asserts failure with exception",
                                          message, impl->getFileName(), 0));
    Py_RETURN_NONE;
}


PyObject* PythonPluginLoaderImpl::testReport(PyObject* self,
                                              PyObject* args) {
    const char* message;
    PythonPluginLoaderImpl* impl =
            (PythonPluginLoaderImpl*) PyCapsule_GetPointer(self, "PythonPluginLoaderImpl");
    RTF_ASSERT_ERROR_IF_FALSE(impl != NULL, "The setName cannot find the instance of PythonPluginLoaderImpl");

    if (!PyArg_ParseTuple(args, "s", &message)) {
        RTF_ASSERT_ERROR(Asserter::format("assertError() is called with the wrong paramters."));
    }
    RTF::Asserter::report(RTF::TestMessage("reports",
                                           message, impl->getFileName(), 0), (TestCase*)impl);
    Py_RETURN_NONE;
}

PyObject* PythonPluginLoaderImpl::testCheck(PyObject* self,
                                            PyObject* args) {
    const char* message;
    PyObject* cond;
    PythonPluginLoaderImpl* impl =
            (PythonPluginLoaderImpl*) PyCapsule_GetPointer(self, "PythonPluginLoaderImpl");
    RTF_ASSERT_ERROR_IF_FALSE(impl != NULL, "The setName cannot find the instance of PythonPluginLoaderImpl");

    if (!PyArg_ParseTuple(args, "Os", &cond, &message)) {
        RTF_ASSERT_ERROR(Asserter::format("assertError() is called with the wrong paramters."));
    }
    //const char* str_cond = PyString_AsString(cond);
    //char str_cond[] = "False";
    RTF::Asserter::testCheck(PyObject_IsTrue(cond), RTF::TestMessage("checks",
                                           message, impl->getFileName(), 0), (TestCase*)impl);
    Py_RETURN_NONE;
}


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

