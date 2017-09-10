#ifndef TN_LOGGER_H
#define TN_LOGGER_H

#include <Common.h>
#include <string>

#define __LOG(level, message)   \
    do{   \
       Logger::getInstance().log(level, __FILE__, __PRETTY_FUNCTION__, __LINE__, message);  \
    }while(0);

#define TN_FATAL(message) \
    do {  \
        __LOG(Logger::LEVEL_FATAL, message);  \
        exit(EXIT_FAILURE);   \
    }while(0);

#define TN_ERROR(message) __LOG(Logger::LEVEL_ERROR, message)
#define TN_INFO(message) __LOG(Logger::LEVEL_INFO, message)
#define TN_DEBUG(message) __LOG(Logger::LEVEL_DEBUG, message)
#define TN_WARNING(message)  __LOG(Logger::LEVEL_WARNING, message)
#define TN_TRACE(message)  __LOG(Logger::LEVEL_TRACE, message)
#define TN_CHECK(expression) \
    do{ \
        if(expression == false) { \
            TN_FATAL("check failed : " + #expression);  \
        }   \
    }   \

namespace TinyNet {
    TN_API class Logger : public SingleTon<Logger>
    {
    public:
        enum LogLevel {
            LEVEL_NONE = 0,
            LEVEL_FATAL,
            LEVEL_ERROR,
            LEVEL_WARNING,
            LEVEL_INFO,
            LEVEL_DEBUG,
            LEVEL_TRACE,
            LEVEL_ALL
        };

        const std::string log_level_tag_[8] = {
            "[THIS SHOULD NOT OCCUR]",
            "[FATAL]",
            "[ERROR]",
            "[WARNING]",
            "[INFO]",
            "[DEBUG]",
            "[TRACE]",
            "[THIS SHOULD NOT OCCUR]"
        };

    public:
        void log(LogLevel level, const std::string& file, const std::string& function,
                 int line, const std::string& message);

        void setLogFile(const std::string& log_file) { log_file_ = log_file; }

    private:
        std::string log_file_ = "log.txt";
    };
}

#endif
