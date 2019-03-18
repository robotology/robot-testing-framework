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


#include <robottestingframework/ConsoleListener.h>
#include <robottestingframework/TestAssert.h>
#include <robottestingframework/TestCase.h>
#include <robottestingframework/TestResult.h>
#include <robottestingframework/TestResultCollector.h>
#include <robottestingframework/dll/Vocab.h>

using namespace robottestingframework;
using namespace shlibpp;

class MyTest : public TestCase
{
public:
    MyTest() :
            TestCase("VocabTest")
    {
    }

    void run() override
    {
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(Vocab::encode("RTF") == (int)4609106, "checking Vocab::encode()");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(Vocab::decode(Vocab::encode("RRTF")) == "RRTF", "checking Vocab::decode()");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(Vocab::decode(VOCAB('R', 'T')) == "RT", "checking VOCAB");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(Vocab::decode(VOCAB('R', 'T', 'F')) == "RTF", "checking VOCAB");
        ROBOTTESTINGFRAMEWORK_TEST_CHECK(Vocab::decode(VOCAB('R', 'T', 'F', 'R')) == "RTFR", "checking VOCAB");
    }
};


int main(int argc, char** argv)
{
    ConsoleListener listener;
    TestResultCollector collector;
    TestResult result;
    result.addListener(&listener);
    result.addListener(&collector);

    MyTest test;
    test.TestCase::run(result);
    return collector.failedCount();
}
