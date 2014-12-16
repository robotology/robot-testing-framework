#include "Logger.h"
#include <string>

#include "TestSet.h"

static Log _log;

void Logger::report(std::string text)
{
    _log.log("++ "+text);
}

void Logger::checkTrue(bool flag, std::string description)
{
    if (!flag)
    {
        _log.addFailure();
        _log.log("FAILED " + description+"\n");
    }
    else
    {
        _log.log("PASSED " + description+"\n");
    }
}

int Logger::failures()
{
    return _log.getFailures();
}

