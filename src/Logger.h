#ifndef __LOGGER__
#define __LOGGER__

#include <cstdio>
#include <string>

/** Simple wrapper around a logger. Not for users. In the future it can include xml printer */
class Log
{
    int failures;
public:
    Log()
    {
        failures=0;
    }

    void log(const std::string &s)
    {
        printf("%s", s.c_str());
    }

    void addFailure()
    {
        failures++;
    }

    int getFailures()
    {   return failures; }
};

/** Contains public helper functions to be used within UnitTest.*/
namespace Logger {
/** Report general information. No checks are performed. Message is printf style.*/
void report(const char *msg, ...);
/** Check result of a test. If flag is true the test is considered passed. Otherwise
   the test is considerd failed. Add a message in printf style. */
void checkTrue(bool flag, const char *msg, ...);
/** Return total number of failures so far.*/
int failures();
};



#endif



