#pragma once
#include "common/include/common_global.h"
#include <string_view>
#include <memory>
#include "common/include/format.h"

namespace common
{
enum Level{
    Trace = 0,
    Debug = 1,
    Info = 2,
    Warn = 3,
    Error = 4,
    Fatal = 5,
    None  = 6
};
class COMMON_EXPORT ILogger
{
public:
struct  Option{
        int level;
        std::string name;
        std::string file_name;
        std::size_t max_size;
        std::size_t max_files;
    };
    virtual ~ILogger();

    virtual void info(std::string_view view) = 0;

    virtual void warn(std::string_view view) = 0;

    virtual void error(std::string_view view) = 0;

    virtual void fatal(std::string_view view) = 0;
};

namespace logger_builder{
    

    COMMON_EXPORT std::shared_ptr<ILogger> createLogger(const ILogger::Option& option);
}
}