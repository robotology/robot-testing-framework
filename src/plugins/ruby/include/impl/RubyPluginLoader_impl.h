// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_RUBYPLUGINLOADER_IMPL_H
#define _RTF_RUBYPLUGINLOADER_IMPL_H

#include <string>
#include <TestCase.h>
#include <ruby.h>

namespace RTF {
    namespace plugin {
        class RubyPluginLoaderImpl;
    }
}

/**
 * @brief The RubyPluginLoaderImpl loads a ruby test case plug-in and
 * gives the direct access to the TestCase.
 */
class RTF::plugin::RubyPluginLoaderImpl : public RTF::TestCase{

public:

    /**
     * RubyPluginLoaderImpl constructor
     */
    RubyPluginLoaderImpl();

    /**
     *  RubyPluginLoaderImpl destructor
     */
    virtual ~RubyPluginLoaderImpl();

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
    std::string extractFileName(const std::string& path);

    static RubyPluginLoaderImpl* getImpFromRuby();
    static std::string getRubyErrorMessage();
    static std::string getRubyBackTrace();

    static VALUE wrapSetup(VALUE args);
    static VALUE protectedSetup(VALUE testcase, ID id, VALUE param,
                               RubyPluginLoaderImpl* impl);
    static VALUE wrapRun(VALUE args);
    static VALUE protectedRun(VALUE testcase, ID id,
                               RubyPluginLoaderImpl* impl);
    static VALUE wrapTearDown(VALUE args);
    static VALUE protectedTearDown(VALUE testcase, ID id,
                               RubyPluginLoaderImpl* impl);    

    static VALUE setName(VALUE self, VALUE obj);
    static VALUE assertError(VALUE self, VALUE obj);
    static VALUE assertFail(VALUE self, VALUE obj);
    static VALUE testReport(VALUE self, VALUE obj);
    static VALUE testCheck(VALUE self, VALUE cond, VALUE message);

private:
    std::string filename;
    std::string error;    
    VALUE testcase;
    VALUE rtfModule;
};

#endif // _RTF_RUBYPLUGINLOADER_IMPL_H

