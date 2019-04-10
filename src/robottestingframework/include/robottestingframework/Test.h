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


#ifndef ROBOTTESTINGFRAMEWORK_TEST_H
#define ROBOTTESTINGFRAMEWORK_TEST_H

#include <string>

namespace robottestingframework {

class TestResult;

/**
 * @brief The simplest form of a test unit
 */
class Test
{
public:
    /**
     * Test constructor
     * @param name The test name
     * @param description An optional string which describes
     * the test
     */
    Test(std::string name,
         std::string description = "") :
            strName(name),
            strDescription(description)
    {
    }

    /**
     *  Test destructor
     */
    virtual ~Test()
    {
    }

    /**
     * @brief getName Getting test name.
     * @return The name of the test.
     */
    const std::string getName() const
    {
        return strName;
    }

    /**
     * @brief getDescription Getting test description
     * @return The description of the test
     */
    const std::string getDescription() const
    {
        return strDescription;
    }

    /**
     * @brief setDescription Sets an optional string which
     * describes the test.
     * @param description The description string
     */
    void setDescription(const std::string description)
    {
        strDescription = description;
    }

    /**
     * the main caller of a test.
     * @param result an instance of a TestResult
     * to collect the result of the test
     */
    virtual void run(TestResult& result) = 0;

    /**
     * @brief interrupt interrupts the current test run
     */
    virtual void interrupt()
    {
    }

    /**
     * @brief succeeded
     * @return true or false representing whether the test
     * was successful or not.
     */
    virtual bool succeeded() const = 0;

protected:
    /**
     * @brief setName setting the test name
     * @param name the test name
     */
    void setName(std::string name)
    {
        strName = name;
    }

private:
    std::string strName;
    std::string strDescription;
};

} // namespace robottestingframework

#endif // ROBOTTESTINGFRAMEWORK_TEST_H
