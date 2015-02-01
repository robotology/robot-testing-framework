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

/** Some helpr functions
*/

/**
 * Element-wise compare two vectors to determine if they are approximately equal, according to asymmetric thresholds that specify lower and upper bound. 
 * Both thresholds are assumed to be positive.
 * @param left: left operand
 * @param right: right operand
 * @param l_thresholds: a vector of thresholds whose elements are used when checking equality of corresponding elements of the left and right vectors. It specifies the low bound of the interval.
 * @param h_thresholds: a vector of thresholds whose elements are used when checking equality of corresponding elements of the left and right vectors. It specifies the upper bound of the interval.
 * @param lenght: specifies the lengths of all vectors
 * @return: the result of the comparison
 */
bool isApproxEqual(const double *left, const double *right, const double *l_thresholds, const double *h_thresholds, int lenght);

/**
 * Element-wise compare two vectors to determine if they are approximately equal, according to a threshold. The threshold is assumed to be positive. 
 * @param left: left operand
 * @param right: right operand
 * @param thresholds: a vector of thresholds whose elements are used when checking equality of corresponding elements of the left and right vectors
 * @param lenght: specifies the lengths of all vectors
 * @return: the result of comparison
 */
bool isApproxEqual(const double *left, const double *right, const double *thresholds, int lenght);

/**
 * Element-wise compare two vectors to determine if they are approximately equal, according to a threshold. The threshold is assumed to be positive. 
 * @param left: left operand
 * @param right: right operand
 * @param thresholds: a vector of thresholds whose elements are used when checking equality of corresponding elements of the left and right vectors
 * @return: the result of comparison
 */
bool isApproxEqual(const yarp::sig::Vector &left, const yarp::sig::Vector &right, const yarp::sig::Vector &thresholds);  

/**
 * Compare two scalars to determine if they are approximately equal, according to asymmetric thresholds that specify upper and lower bound.
 * @param left: left operand
 * @param right: right operand
 * @param l_th: lower bound of interval for comparison
 * @param h_th: upper bound of interval for comparison
 * @return: the result of comparison
 */
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
