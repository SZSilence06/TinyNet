#include <Logger.h>
#include <sstream>
#include <ctime>
#include <cstdio>
#include <iostream>

namespace TinyNet
{
    void Logger::log(LogLevel level, const std::string &file,
                     const std::string &function, int line,
                     const std::string &message)
    {
        std::stringstream ss;
        ss << log_level_tag_[level] << "  ";

        std::time_t t = std::time(0);
        std::tm now;
        localtime_r(&t, &now);
        char buffer[1000];
        std::snprintf(buffer, sizeof(buffer), "%4d/%02d/%02d %02d:%02d:%02d",
                      now.tm_year + 1900,
                      now.tm_mon + 1,
                      now.tm_mday,
                      now.tm_hour,
                      now.tm_min,
                      now.tm_sec);
        ss << buffer << "  ";

        ss << message << "  ";
        if(level <= LEVEL_WARNING)
        {
             ss << file << "," << function << "," << "line " << line;
        }
        std::cout << ss.str() << std::endl;
    }
}
