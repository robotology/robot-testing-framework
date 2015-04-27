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


VALUE RubyPluginLoaderImpl::wrapSetup(VALUE args) {
    VALUE *values = (VALUE *) args;
    VALUE setup = values[0];
    ID id_setup = values[1];
    VALUE param = values[2];
    return rb_funcall(setup, id_setup, 1, param);
}

VALUE RubyPluginLoaderImpl::protectedSetup(VALUE testcase, ID id,
                                           VALUE param, RubyPluginLoaderImpl* impl) {
    int state;
    VALUE args[1];
    args[0] = testcase;
    args[1] = id;
    args[2] = param;
    rb_protect(RubyPluginLoaderImpl::wrapSetup, (VALUE)args, &state);
    return state;
}


VALUE RubyPluginLoaderImpl::wrapRun(VALUE args) {
    VALUE *values = (VALUE *) args;
    VALUE run = values[0];
    ID id_run = values[1];
    return rb_funcall(run, id_run, 0);
}

VALUE RubyPluginLoaderImpl::protectedRun(VALUE testcase, ID id,
                           RubyPluginLoaderImpl* impl) {
    int state;
    VALUE args[1];
    args[0] = testcase;
    args[1] = id;
    rb_protect(RubyPluginLoaderImpl::wrapRun, (VALUE)args, &state);
    return state;
}

VALUE RubyPluginLoaderImpl::wrapTearDown(VALUE args) {
    VALUE *values = (VALUE *) args;
    VALUE teardown = values[0];
    ID id_teardown = values[1];
    return rb_funcall(teardown, id_teardown, 0);
}

VALUE RubyPluginLoaderImpl::protectedTearDown(VALUE testcase, ID id,
                           RubyPluginLoaderImpl* impl) {
    int state;
    VALUE args[1];
    args[0] = testcase;
    args[1] = id;
    rb_protect(RubyPluginLoaderImpl::wrapTearDown, (VALUE)args, &state);
    return state;
}

TestCase* RubyPluginLoaderImpl::open(const std::string filename) {
    close();
    this->filename = filename;
    string bname = extractFileName(filename);
    RUBY_INIT_STACK;
    ruby_init();
    ruby_script(bname.c_str());
    ruby_init_loadpath();

    // load the ruby script
    int state = 0;
    rb_protect((VALUE (*)(VALUE))rb_require, (VALUE)filename.c_str(), &state);
    if(state != 0) {
        error = Asserter::format("Cannot load %s due to error %d",
                                 filename.c_str(), state);
        close();
        return NULL;
    }

    // get an instance of Summer
    testcase = rb_class_new_instance(0, 0,rb_const_get(rb_cObject,
                                                             rb_intern("TestCase")));
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

    VALUE param = rb_ary_new();
    for(int i=0; i<argc; i++)
        rb_ary_push(param, rb_str_new_cstr(argv[i]));
    ID id = rb_intern("setup");
    // TODO: check the return value
    //int state = protectedSetup(testcase, id, param, this);
    return true;
}

void RubyPluginLoaderImpl::tearDown() {
    ID id = rb_intern("tearDown");
    int state = protectedRun(testcase, id, this);
}

void RubyPluginLoaderImpl::run() {
    ID id_run = rb_intern("run");
    int state = protectedRun(testcase, id_run, this);
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


