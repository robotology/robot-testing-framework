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


#ifndef ROBOTTESTINGFRAMEWORK_RUBYPLUGINLOADER_IMPL_H
#define ROBOTTESTINGFRAMEWORK_RUBYPLUGINLOADER_IMPL_H

#include <robottestingframework/TestCase.h>

#include <ruby.h>
#include <string>

namespace robottestingframework {
namespace plugin {

/**
 * @brief The RubyPluginLoaderImpl loads a ruby test case plug-in and
 * gives the direct access to the TestCase.
 */
class RubyPluginLoaderImpl : public robottestingframework::TestCase
{

public:
    /**
     * RubyPluginLoaderImpl constructor
     */
    RubyPluginLoaderImpl();

    /**
     *  RubyPluginLoaderImpl destructor
     */
    ~RubyPluginLoaderImpl() override;

    /**
     * @brief open Loads a test case plugin
     * @param filename the plugin filename
     * @return A pointer to the test case loaded from the
     * plugin or a null pointer in case of failure.
     */
    TestCase* open(const std::string filename);

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

    bool setup(int argc, char** argv) override;

    void tearDown() override;

    void run() override;


private:
    std::string extractFileName(const std::string& path);

    static RubyPluginLoaderImpl* getImpFromRuby();
    static std::string getRubyErrorMessage();
    static std::string getRubyBackTrace();

    static VALUE wrapSetup(VALUE args);
    static VALUE protectedSetup(VALUE testcase, ID id, VALUE param, RubyPluginLoaderImpl* impl);
    static VALUE wrapRun(VALUE args);
    static VALUE protectedRun(VALUE testcase, ID id, RubyPluginLoaderImpl* impl);
    static VALUE wrapTearDown(VALUE args);
    static VALUE protectedTearDown(VALUE testcase, ID id, RubyPluginLoaderImpl* impl);

    static VALUE setName(VALUE self, VALUE obj);
    static VALUE assertError(VALUE self, VALUE obj);
    static VALUE assertFail(VALUE self, VALUE obj);
    static VALUE testReport(VALUE self, VALUE obj);
    static VALUE testCheck(VALUE self, VALUE cond, VALUE message);

private:
    std::string filename;
    std::string error;
    VALUE testcase;
    VALUE RobotTestingFrameworkModule;
};

} // namespace plugin
} // namespace robottestingframework

#endif // ROBOTTESTINGFRAMEWORK_RUBYPLUGINLOADER_IMPL_H
