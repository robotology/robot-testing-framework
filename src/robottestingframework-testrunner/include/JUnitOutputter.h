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


#ifndef ROBOTTESTINGFRAMEWORK_JUNITOUTPUTTER_H
#define ROBOTTESTINGFRAMEWORK_JUNITOUTPUTTER_H


#include <robottestingframework/TestMessage.h>
#include <robottestingframework/TestResultCollector.h>

#include <string>

namespace robottestingframework {

/**
 * \brief Class JUnitOutputter saves the results of the test collected by
 * a TestResultCollector in a JUnit XML file.
 */
class JUnitOutputter
{
public:
    /**
     * @brief JUnitOutputter constructor.
     * @param collector an instance of a TestResultCollector which holds
     * the results of the test
     * @param verbose enables the verbose mode. If \c true, the source file and
     * the line number where the messages are issued by the tests will be written to
     * the output file. The verbose mode is disabled by default.
     */
    JUnitOutputter(TestResultCollector& collector,
                   bool verbose = false);

    /**
     * @brief ~JUnitOutputter destructor
     */
    virtual ~JUnitOutputter();

    /**
     * @brief write Write the results of the test in a JUnit XML file.
     * @param filename the name of the text file. If an instance of
     * the TestMesagge is given to the function, it will return the error
     * message in case of failure.
     * @param errorMsg a pointer to a TestMessage to return the error message
     * in case of failure. It can be left unassigned if it is not required.
     * @return true or false uppoun success or failure
     */
    bool write(std::string filename,
               TestMessage* errorMsg = nullptr);

private:
    bool verbose;
    TestResultCollector& collector;
};

} // namespace robottestingframework

#endif // ROBOTTESTINGFRAMEWORK_JUNITOUTPUTTER_H
