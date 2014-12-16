#include "Logger.h"
#include <string>
#include <stdarg.h>
#include <stdio.h>

#include "TestSet.h"

static Log _log;

void Logger::report(const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    if (msg) {
        char buf[255];
        int w = vsnprintf(buf, 255, msg, args);
        _log.log("++"+std::string(buf));
    }
    va_end(args);
}

void Logger::checkTrue(bool flag, const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    if (msg) {
        char buf[255];
        int w = vsnprintf(buf, 255, msg, args);

        //chomp ending \n because we will be forcing one ourself
        if (w>0 && buf[w-1]=='\n') {
            buf[w-1]=0;
        }

        if (!flag)
        {
            _log.addFailure();
            _log.log("!!FAILED " + std::string(buf)+"\n");
        }
        else
        {
            _log.log("Ok " + std::string(buf)+"\n");
        }
    }
    va_end(args);
}

int Logger::failures()
{
    return _log.getFailures();
}

