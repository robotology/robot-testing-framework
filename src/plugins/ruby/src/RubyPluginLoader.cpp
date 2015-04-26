// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <Plugin.h>
#include <Asserter.h>
#include <TestAssert.h>
#include <RubyPluginLoader.h>
#include <RubyPluginLoader_impl.h>

using namespace std;
using namespace RTF;
using namespace RTF::plugin;


/**
 * @brief RubyPluginLoaderImpl
 */

RubyPluginLoaderImpl::RubyPluginLoaderImpl()
    : TestCase("") {
}

RubyPluginLoaderImpl::~RubyPluginLoaderImpl() {
    close();
}

void RubyPluginLoaderImpl::close() {
    //ruby_finalize();
}

TestCase* RubyPluginLoaderImpl::open(const std::string filename) {
    close();
    this->filename = filename;
    RUBY_INIT_STACK;
    ruby_init();
    ruby_script(filename.c_str());
    ruby_init_loadpath();
    //printf("%d\n", __LINE__);
    //rb_require("sum");
    //rb_eval_string("$summer = Summer.new");
    //rb_eval_string("$result = $summer.sum(10)");
    //result = rb_gv_get("result");
    //printf("Result = %d\n", NUM2INT(result));
    /*
    if(!rb_load_file(filename.c_str()) ) {
        error = Asserter::format("Cannot load %s ", filename.c_str());
        close();
        return NULL;
    }
    */

    /*
    // Get symbol for our module's name
    ID sym_mymodule = rb_intern(filename.c_str());
    // Get the module
    VALUE mymodule = rb_const_get(rb_cObject, sym_mymodule);
    // Get symbol for our class' name
    ID sym_myclass = rb_intern("TestCase");
    printf("id: %d\n", sym_myclass);

    // Get the class
    VALUE myclass = rb_const_get(mymodule, sym_myclass);
    // Create a new object, using the default initializer, having 0 argument
    VALUE argv[0];
    VALUE myobject = rb_class_new_instance(0, argv, myclass2);

    // Use String initializer with 1 argument
    VALUE strargv[1];
    strargv[0] = rb_str_new2("With argument");
    VALUE mystring = rb_class_new_instance(1, strargv, rb_cString);

    // Get the method's symbol
    ID sym_mymethod = rb_intern("my_method");
    // Call the method, giving 3 parameters
    VALUE result = rb_funcall(myobject, sym_mymethod, 3, Qnil, Qtrue, Qfalse);

    // Get the puts method's symbol
    ID sym_puts = rb_intern("puts");
    // Call puts, from Kernel
    rb_funcall(rb_mKernel, sym_puts, 1, rb_str_new2("Hello world!"));
    */
    setTestName(extractFileName(filename));

    return this;
}

void RubyPluginLoaderImpl::setTestName(const std::string name) {
    Test::setName(name);
}

const std::string RubyPluginLoaderImpl::getLastError() {

    return error;
}

const std::string RubyPluginLoaderImpl::getFileName() {
    return filename;
}

bool RubyPluginLoaderImpl::setup(int argc, char**argv) {

    return true;
}

void RubyPluginLoaderImpl::tearDown() {
}

void RubyPluginLoaderImpl::run() {
}
/*
int RubyPluginLoaderImpl::setName(lua_State* L) {
    return 0;
}

int RubyPluginLoaderImpl::assertError(lua_State* L) {
    return 0;
}

int RubyPluginLoaderImpl::assertFail(lua_State* L) {
    return 0;
}

int RubyPluginLoaderImpl::testReport(lua_State* L) {
    return 0;
}

int RubyPluginLoaderImpl::testFail(lua_State* L) {
    return 0;
}
*/

std::string RubyPluginLoaderImpl::extractFileName(const std::string& path) {

#ifdef _WIN32
    size_t i = path.rfind('\\', s.length());
#else
   size_t i = path.rfind('/', path.length());
#endif
   if(i != string::npos)
      return(path.substr(i+1, path.length()-i));
   return(path);
}

/**
 * @brief RubyPluginLoader
 */
RubyPluginLoader::RubyPluginLoader()
    : implementaion(NULL) { }

RubyPluginLoader::~RubyPluginLoader() {
    close();
}

void RubyPluginLoader::close() {
    if(implementaion)
        delete ((RubyPluginLoaderImpl*)implementaion);
    implementaion = NULL;
}

TestCase* RubyPluginLoader::open(const std::string filename) {
    close();
    implementaion = new RubyPluginLoaderImpl();
    return ((RubyPluginLoaderImpl*)implementaion)->open(filename);
}

const std::string RubyPluginLoader::getLastError() {
    if(implementaion)
        return ((RubyPluginLoaderImpl*)implementaion)->getLastError();
    return string("");
}


