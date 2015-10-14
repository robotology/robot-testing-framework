// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_JUNITOUTPUTTER_H
#define _RTF_JUNITOUTPUTTER_H

#include <rtf/rtf_config.h>
#include <string>
#include <rtf/TestMessage.h>
#include <rtf/TestResultCollector.h>

namespace RTF {
    class JUnitOutputter;
}

/**
 * \brief Class JUnitOutputter saves the results of the test collected by
 * a TestResultCollector in a JUnit XML file.
 */
class RTF_API RTF::JUnitOutputter {
public:

    /**
     * @brief JUnitOutputter constructor.
     * @param collector an instance of a TestResultCollector which holds
     * the results of the test
     * @param verbose enables the verbose mode. If \c true, the source file and
     * the line number where the messages are issued by the tests will be written to
     * the output file. The verbose mode is disabled by default.
     */
    JUnitOutputter(RTF::TestResultCollector& collector,
                  bool verbose=false);

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
               RTF::TestMessage* errorMsg=NULL);

private:
    bool verbose;
    RTF::TestResultCollector& collector;
};

#endif // _RTF_JUNITOUTPUTTER_H
