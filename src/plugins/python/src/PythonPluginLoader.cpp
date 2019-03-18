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


#include <robottestingframework/Asserter.h>
#include <robottestingframework/TestAssert.h>
#include <robottestingframework/dll/Plugin.h>
#include <robottestingframework/python/PythonPluginLoader.h>
#include <robottestingframework/python/impl/PythonPluginLoader_impl.h>

#ifdef _WIN32
#    include <stdlib.h>
#else
#    include <libgen.h>
#endif

using namespace std;
using namespace robottestingframework;
using namespace robottestingframework::plugin;


/**
 * @brief PythonPluginLoaderImpl
 */


PyMethodDef PythonPluginLoaderImpl::testPythonMethods[] = {
    { "setName", PythonPluginLoaderImpl::setName, METH_VARARGS, "Setting the test name." },
    { "assertError", PythonPluginLoaderImpl::assertError, METH_VARARGS, "Error assertion." },
    { "assertFail", PythonPluginLoaderImpl::assertFail, METH_VARARGS, "Failure assertion." },
    { "testReport", PythonPluginLoaderImpl::testReport, METH_VARARGS, "report a test message." },
    { "testCheck", PythonPluginLoaderImpl::testCheck, METH_VARARGS, "report failure message with condition." },
    { nullptr, nullptr, 0, nullptr }
};


PythonPluginLoaderImpl::PythonPluginLoaderImpl() :
        TestCase("")
{
    pyName = pyModule = pyModuleRobotTestingFramework = pyCapsuleRobotTestingFramework = nullptr;
}

PythonPluginLoaderImpl::~PythonPluginLoaderImpl()
{
    close();
}

void PythonPluginLoaderImpl::close()
{
    // Clean up
    if (pyCapsuleRobotTestingFramework) {
        Py_DECREF(pyCapsuleRobotTestingFramework);
        pyName = nullptr;
    }
    if (pyModuleRobotTestingFramework) {
        Py_DECREF(pyModuleRobotTestingFramework);
        pyName = nullptr;
    }
    if (pyModule) {
        Py_DECREF(pyModule);
        pyModule = nullptr;
    }
    if (pyName) {
        Py_DECREF(pyName);
        pyName = nullptr;
    }

    // Finish the Python Interpreter
    Py_Finalize();
}

TestCase* PythonPluginLoaderImpl::open(const std::string filename)
{
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
                 drive,
                 _MAX_DRIVE,
                 dir,
                 _MAX_DIR,
                 fname,
                 _MAX_FNAME,
                 ext,
                 _MAX_EXT);
    string dname = string(drive) + string(dir);
    for (size_t i = 0; i < dname.size(); i++)
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
    if (pyName == nullptr) {
        error = Asserter::format("Cannot load %s because %s",
                                 filename.c_str(),
                                 getPythonErrorString().c_str());
        close();
        return nullptr;
    }

    // Load the module object
    pyModule = PyImport_Import(pyName);
    if (pyModule == nullptr) {
        error = Asserter::format("Cannot load %s because %s",
                                 filename.c_str(),
                                 getPythonErrorString().c_str());
        close();
        return nullptr;
    }


    // store the current instance of PythonPluginLoaderImpl
    // register the extended methods and import the 'robottestingframework'
    PyObject* pyCapsuleRobotTestingFramework = PyCapsule_New(this, "PythonPluginLoaderImpl", nullptr);
    //(void) Py_InitModule("robottestingframework", testPythonMethods);
    Py_InitModule4("robottestingframework", testPythonMethods, (char*)nullptr, pyCapsuleRobotTestingFramework, PYTHON_API_VERSION);
    PyObject* pyModuleRobotTestingFramework = PyImport_Import(PyString_FromString("robottestingframework"));
    PyModule_AddObject(pyModuleRobotTestingFramework, "PythonPluginLoaderImpl", pyCapsuleRobotTestingFramework);
    PyModule_AddObject(pyModule, "robottestingframework", pyModuleRobotTestingFramework);

    // pyDict is a borrowed reference
    pyDict = PyModule_GetDict(pyModule);
    if (pyDict == nullptr) {
        error = Asserter::format("Cannot load %s because %s",
                                 filename.c_str(),
                                 getPythonErrorString().c_str());
        close();
        return nullptr;
    }

    // Build the name of a callable class
    pyClass = PyDict_GetItemString(pyDict, "TestCase");
    if (pyClass == nullptr) {
        error = Asserter::format("Cannot find any instance of class TestCase");
        close();
        return nullptr;
    }

    // Create an instance of the class
    if (!PyCallable_Check(pyClass) || (pyInstance = PyObject_CallObject(pyClass, nullptr)) == nullptr) {
        error = Asserter::format("TestCase is not defined as a class");
        close();
        return nullptr;
    }

    setTestName(bname);
    return this;
}

std::string PythonPluginLoaderImpl::getPythonErrorString()
{
    std::string strError;
    // Extra paranoia...
    if (!PyErr_Occurred())
        return strError;

    //PyErr_Print();
    PyObject *type, *value, *traceback, *pyString;
    type = value = traceback = pyString = nullptr;

    PyErr_Fetch(&type, &value, &traceback);
    PyErr_Clear();
    if (value != nullptr && (pyString = PyObject_Str(value)) != nullptr && (PyString_Check(pyString))) {
        strError = PyString_AsString(pyString);
    } else
        strError = "<unknown exception value>";
    Py_XDECREF(pyString);

    if (type != nullptr && (pyString = PyObject_Str(type)) != nullptr && (PyString_Check(pyString)))
        strError += string("; ") + PyString_AsString(pyString);
    else
        strError = " <unknown exception type>";
    Py_XDECREF(pyString);

    if (traceback != nullptr && PyTraceBack_Check(traceback)) {
        strError = "Syntax Error!";
    }
    Py_XDECREF(type);
    Py_XDECREF(value);
    Py_XDECREF(traceback);
    return strError;
}

void PythonPluginLoaderImpl::setTestName(const std::string name)
{
    Test::setName(name);
}

std::string PythonPluginLoaderImpl::getLastError()
{
    return error;
}

std::string PythonPluginLoaderImpl::getFileName()
{
    return filename;
}

bool PythonPluginLoaderImpl::setup(int argc, char** argv)
{
    PyObject* func = PyObject_GetAttrString(pyInstance, "setup");
    if (func == nullptr)
        return true;


    PyObject* arglist = PyTuple_New(argc);
    if (arglist == nullptr) {
        error = Asserter::format("Cannot create arguments because %s",
                                 getPythonErrorString().c_str());
        ROBOTTESTINGFRAMEWORK_ASSERT_ERROR(error);
    }
    for (int i = 0; i < argc; i++) {
        PyObject* str = PyString_FromString(argv[i]);
        if (str == nullptr) {
            Py_DECREF(arglist);
            error = Asserter::format("Cannot create arguments because %s",
                                     getPythonErrorString().c_str());
            ROBOTTESTINGFRAMEWORK_ASSERT_ERROR(error);
        }
        PyTuple_SetItem(arglist, i, str);
    }

    PyObject* pyValue = PyObject_CallObject(func, arglist);
    if (pyValue == nullptr) {
        error = Asserter::format("Cannot call the setup() method because %s",
                                 getPythonErrorString().c_str());
        Py_DECREF(arglist);
        ROBOTTESTINGFRAMEWORK_ASSERT_ERROR(error);
    }

    // TODO: ensure the return value type
    bool ret = (PyObject_IsTrue(pyValue) == 1);
    Py_DECREF(arglist);
    Py_DECREF(pyValue);
    return ret;
}

void PythonPluginLoaderImpl::tearDown()
{
    PyObject* func = PyObject_GetAttrString(pyInstance, "tearDown");
    if (func == nullptr)
        return;

    char method[] = "tearDown";
    PyObject* pyValue = PyObject_CallMethod(pyInstance, method, nullptr);
    if (pyValue == nullptr) {
        error = Asserter::format("Cannot call the tearDown() method because %s",
                                 getPythonErrorString().c_str());
        ROBOTTESTINGFRAMEWORK_ASSERT_ERROR(error);
    }

    Py_DECREF(pyValue);
}

void PythonPluginLoaderImpl::run()
{
    char method[] = "run";
    PyObject* pyValue = PyObject_CallMethod(pyInstance, method, nullptr);
    if (pyValue == nullptr) {
        error = Asserter::format("Cannot call the run() method because %s",
                                 getPythonErrorString().c_str());
        ROBOTTESTINGFRAMEWORK_ASSERT_ERROR(error);
    }

    Py_DECREF(pyValue);
}


PyObject* PythonPluginLoaderImpl::setName(PyObject* self,
                                          PyObject* args)
{
    const char* name;
    auto* impl = (PythonPluginLoaderImpl*)PyCapsule_GetPointer(self, "PythonPluginLoaderImpl");
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(impl != nullptr, "The setName cannot find the instance of PythonPluginLoaderImpl");
    if (!PyArg_ParseTuple(args, "s", &name)) {
        ROBOTTESTINGFRAMEWORK_ASSERT_ERROR(Asserter::format("setName() is called with the wrong paramters."));
    }
    impl->setTestName(name);
    Py_RETURN_NONE;
}


PyObject* PythonPluginLoaderImpl::assertError(PyObject* self,
                                              PyObject* args)
{
    const char* message;
    auto* impl = (PythonPluginLoaderImpl*)PyCapsule_GetPointer(self, "PythonPluginLoaderImpl");
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(impl != nullptr, "The setName cannot find the instance of PythonPluginLoaderImpl");

    if (!PyArg_ParseTuple(args, "s", &message)) {
        ROBOTTESTINGFRAMEWORK_ASSERT_ERROR(Asserter::format("assertError() is called with the wrong paramters."));
    }
    //impl->close();
    Asserter::error(TestMessage("asserts error with exception",
                                message,
                                impl->getFileName(),
                                0));
    Py_RETURN_NONE;
}


PyObject* PythonPluginLoaderImpl::assertFail(PyObject* self,
                                             PyObject* args)
{
    const char* message;
    auto* impl = (PythonPluginLoaderImpl*)PyCapsule_GetPointer(self, "PythonPluginLoaderImpl");
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(impl != nullptr, "The setName cannot find the instance of PythonPluginLoaderImpl");

    if (!PyArg_ParseTuple(args, "s", &message)) {
        ROBOTTESTINGFRAMEWORK_ASSERT_ERROR(Asserter::format("assertError() is called with the wrong paramters."));
    }
    Asserter::fail(TestMessage("asserts failure with exception",
                               message,
                               impl->getFileName(),
                               0));
    Py_RETURN_NONE;
}


PyObject* PythonPluginLoaderImpl::testReport(PyObject* self,
                                             PyObject* args)
{
    const char* message;
    auto* impl = (PythonPluginLoaderImpl*)PyCapsule_GetPointer(self, "PythonPluginLoaderImpl");
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(impl != nullptr, "The setName cannot find the instance of PythonPluginLoaderImpl");

    if (!PyArg_ParseTuple(args, "s", &message)) {
        ROBOTTESTINGFRAMEWORK_ASSERT_ERROR(Asserter::format("assertError() is called with the wrong paramters."));
    }
    Asserter::report(TestMessage("reports",
                                 message,
                                 impl->getFileName(),
                                 0),
                     (TestCase*)impl);
    Py_RETURN_NONE;
}

PyObject* PythonPluginLoaderImpl::testCheck(PyObject* self,
                                            PyObject* args)
{
    const char* message;
    PyObject* cond;
    auto* impl = (PythonPluginLoaderImpl*)PyCapsule_GetPointer(self, "PythonPluginLoaderImpl");
    ROBOTTESTINGFRAMEWORK_ASSERT_ERROR_IF_FALSE(impl != nullptr, "The setName cannot find the instance of PythonPluginLoaderImpl");

    if (!PyArg_ParseTuple(args, "Os", &cond, &message)) {
        ROBOTTESTINGFRAMEWORK_ASSERT_ERROR(Asserter::format("assertError() is called with the wrong paramters."));
    }
    //const char* str_cond = PyString_AsString(cond);
    //char str_cond[] = "False";
    Asserter::testCheck(PyObject_IsTrue(cond), TestMessage("checks", message, impl->getFileName(), 0), (TestCase*)impl);
    Py_RETURN_NONE;
}


/**
 * @brief PythonPluginLoader
 */
PythonPluginLoader::PythonPluginLoader() :
        implementation(nullptr)
{
}

PythonPluginLoader::~PythonPluginLoader()
{
    close();
}

void PythonPluginLoader::close()
{
    if (implementation)
        delete ((PythonPluginLoaderImpl*)implementation);
    implementation = nullptr;
}

TestCase* PythonPluginLoader::open(const std::string filename)
{
    close();
    implementation = new PythonPluginLoaderImpl();
    return ((PythonPluginLoaderImpl*)implementation)->open(filename);
}

std::string PythonPluginLoader::getLastError()
{
    if (implementation)
        return ((PythonPluginLoaderImpl*)implementation)->getLastError();
    return string("");
}
