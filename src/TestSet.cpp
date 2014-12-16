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

#include <yarp/os/Value.h>

#include "TestXMLPrinter.h"
#include "TestSet.h"

#include <stdio.h>

#include "Logger.h"

#include <yarp/os/Time.h>

bool TestSet::init(yarp::os::Searchable& configuration)
{   
    m_bSuccess=false;
    m_numFailures=0;

    if (configuration.check("user"))
    {
        m_User=configuration.find("user").asString();
    }
    if (configuration.check("comment"))
    {
        m_Comment=configuration.find("comment").asString();
    }
    if (configuration.check("outfile"))
    {
        m_Outfile=configuration.find("outfile").asString();
    }

    return true;
}

TestSet::~TestSet()
{
    cleanup();
}

void TestSet::cleanup()
{
   for (unsigned int t=0; t<m_apTest.size(); ++t)
    {
        if (m_apTest[t])
        {
            delete m_apTest[t];
            m_apTest[t]=NULL;
        }
    }
   
   m_apTest.clear();
}

int TestSet::run()
{
    Logger::report("== Running tests ==\n");
    m_bSuccess=true;
    m_numFailures=0;
    m_numTests=0;

    m_timeStart=yarp::os::Time::now();

    for (unsigned int i=0; i<m_apTest.size(); ++i)
    {
        //read test name and description
        if (!m_apTest[i]->configure())
        {
            Logger::report("Failed to configure " + m_apTest[i]->getName() + " \n");
            m_numSkipped++;
        }
        else
        {
            Logger::report("Running test: "+ m_apTest[i]->getName()+ "\n");
            Logger::report("Description: " + m_apTest[i]->getDescription() + "\n");

            if (!m_apTest[i]->run())
                 m_bSuccess=false;
        
            m_numTests++;
        }
    }

    m_timeEnd=yarp::os::Time::now();

    m_numFailures=Logger::failures();

    return m_numFailures;
}

void TestSet::printReport()
{
    printf("===== Final report =====\n");
    printf("Executed %d tests: \n", m_numTests);
    printf("Execution time: %g seconds\n", m_timeEnd-m_timeStart);
    printf("Failed tests: %d\n", m_numFailures);
    printf("Skipped tests: %d\n", m_numSkipped);
    if (m_numFailures!=0)
        printf("THERE WERE FAILED TESTS, please check output carefully\n");
    printf("=========================\n");

#if 0

    XMLPrinter printer(m_Outfile);

    char failuresStr[16];
    sprintf(failuresStr,"%d",m_numFailures);

    printer.xmlOpen("report");
    printer.xml("user",m_User);
    printer.xml("comment",m_Comment);
    printer.xml("success",std::string(m_bSuccess?"YES":"NO"));

    printer.xml("failures-total",std::string(failuresStr));

    for (unsigned int i=0; i<m_apReport.size(); ++i)
    {
        if (m_apReport[i])
            m_apReport[i]->printReport(printer);   
    }

    printer.xmlClose();
#endif
}
