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

#ifndef __ICUB_TEST_01122009__
#define __ICUB_TEST_01122009__

#include <string>

#include <yarp/os/Searchable.h>

#include "Logger.h"

#include <yarp/os/ResourceFinder.h>

#include <yarp/sig/Vector.h>

/*
* Some helpr functions
*/
bool isApproxEqual(const double *left, const double *right, const double *l_thresholds, const double *h_thresholds, int lenght);
bool isApproxEqual(const double *left, const double *right, const double *thresholds, int lenght);
bool isApproxEqual(const yarp::sig::Vector &left, const yarp::sig::Vector &right, const yarp::sig::Vector &thresholds);  
bool isApproxEqual(double left, double right, double l_th, double h_th);

class UnitTest
{
public:
    UnitTest(yarp::os::Property& config);

    virtual ~UnitTest()
    {}
    
    virtual bool init(yarp::os::Property &configuration){ return true; }
    virtual bool run()=0;
    virtual bool release(){return true; }

    bool getSuccess()
    {
        return m_bSuccess;
    }

    bool isCritical()
    {
        return m_bIsCritical;
    }

    bool configure();

    std::string getName()
    { return m_Name; }

    std::string getDescription()
    { return m_Description; }

protected:
    bool m_bSuccess;
    bool m_bIsCritical;

    std::string m_Name;
    std::string m_Description;
    std::string m_partCode;

    yarp::os::Property configuration;
};

#endif
