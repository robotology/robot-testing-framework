#ifndef __LOGGER__
#define __LOGGER__

#include <string>

/* Simple wrapper around a logger, in the future it can include xml printer */
class Log
{
    int failures;
public:
    Log()
    {
        failures=0;
    }

    void log(std::string s)
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

namespace Logger {
void report(std::string description);
void checkTrue(bool flag, std::string description);
int failures();
};



#endif



