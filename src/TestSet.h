// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/* 
 * Copyright (C) 2010 RobotCub Consortium, European Commission FP6 Project IST-004370
 * Author: Alessandro Scalzo
 * email: alessandro.scalzo@iit.it
 * website: www.robotcub.org
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

#ifndef __ICUB_TEST_SET_01122009__
#define __ICUB_TEST_SET_01122009__

#include <string>
#include <vector>

#include <yarp/os/Searchable.h>

#include "UnitTest.h"

class TestSet
{
public:
    TestSet() 
    {
        m_numTests=0;
        m_numSkipped=0;
    };

    ~TestSet();
    
    void addTest(UnitTest* pTest)
    {
        m_apTest.push_back(pTest);
    }

    bool init(yarp::os::Searchable& configuration);

    void cleanup();

    int run();

    void printReport();

    void log(std::string string){ printf("%s", string.c_str()); }

protected:
    bool m_bSuccess;
    int m_numFailures;
    std::string m_Comment;
    std::string m_User;
    std::string m_Outfile;
    std::vector<UnitTest*> m_apTest;

    int m_numTests;
    int m_numSkipped;
    double m_timeStart;
    double m_timeEnd;
};

#endif
