#include "common/include/logger.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/spdlog.h"
#include "spdlog/logger.h"
ILogger::~ILogger() = default;


class LoggerImpl : public ILogger
{
public:
    explicit LoggerImpl(const logger_builder::Option& option){
       logger_= spdlog::create<spdlog::sinks::rotating_file_sink_mt>(option.name, option.file_name, option.max_size, option.max_files);
       logger_->set_level((spdlog::level::level_enum)(option.level));
    }
    void info(std::string_view view) override{
        logger_->info(view);
    }

    void warn(std::string_view view) override{
        logger_->warn(view);
    }

    void error(std::string_view view) override{
        logger_->error(view);
    }

    void fatal(std::string_view view) override{
        logger_->critical(view);
    }

private:
    std::shared_ptr<spdlog::logger> logger_;
};

 std::shared_ptr<ILogger> logger_builder::create_logger(const Option& option){
     auto logger = std::make_shared<LoggerImpl>(option);
     return logger;
 }