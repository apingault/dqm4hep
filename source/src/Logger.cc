/// \file Logger.cc
/*
 *
 * Logger.cc source template automatically generated by a class generator
 * Creation date : dim. mars 29 2015
 *
 * This file is part of DQM4HEP libraries.
 *
 * DQM4HEP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 *
 * DQM4HEP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DQM4HEP.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */


#include "dqm4hep/Logger.h"

#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/ansicolor_sink.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/sink.h"

namespace dqm4hep {

  namespace core {

    std::shared_ptr<spdlog::logger>  Logger::m_mainLogger = Logger::createLogger("main", {
      Logger::coloredConsole()
    });

    //-------------------------------------------------------------------------------------------------

    std::shared_ptr<spdlog::logger> Logger::createLogger(const std::string &name, std::initializer_list<Logger::AppenderPtr> appenders)
    {
      std::shared_ptr<spdlog::logger> logger_ptr(spdlog::get(name));

      if(nullptr != logger_ptr)
        return logger_ptr;

      logger_ptr = std::make_shared<spdlog::logger>(name, begin(appenders), end(appenders));
      spdlog::register_logger(logger_ptr);

      return logger_ptr;
    }

    //-------------------------------------------------------------------------------------------------

    std::shared_ptr<spdlog::logger> Logger::createLogger(const std::string &name, const std::vector<Logger::AppenderPtr> &appenders)
    {
      std::shared_ptr<spdlog::logger> logger_ptr(spdlog::get(name));

      if(nullptr != logger_ptr)
        return logger_ptr;

      logger_ptr = std::make_shared<spdlog::logger>("main", begin(appenders), end(appenders));
      spdlog::register_logger(logger_ptr);

      return logger_ptr;
    }

    //-------------------------------------------------------------------------------------------------

    Logger::LoggerPtr Logger::mainLogger()
    {
      return m_mainLogger;
    }

    //-------------------------------------------------------------------------------------------------

    Logger::LoggerPtr Logger::setMainLogger(const std::string &logger)
    {
      LoggerPtr logger_ptr(Logger::logger(logger));

      if(nullptr != logger_ptr)
        m_mainLogger = logger_ptr;

      return m_mainLogger;
    }

    //-------------------------------------------------------------------------------------------------

    Logger::LoggerPtr Logger::logger(const std::string &name)
    {
      return spdlog::get(name);
    }

    //-------------------------------------------------------------------------------------------------

    void Logger::setLogLevel(Level level)
    {
      m_mainLogger->set_level(static_cast<spdlog::level::level_enum>(level));
    }

    //-------------------------------------------------------------------------------------------------

    std::string Logger::logLevelToString(Logger::Level level)
    {
      return spdlog::level::to_str(static_cast<spdlog::level::level_enum>(level));
    }

    //-------------------------------------------------------------------------------------------------

    void Logger::setLoggerPattern(const std::string &logger, const std::string &pattern)
    {
      LoggerPtr logger_ptr = Logger::logger(logger);

      if(logger_ptr)
        logger_ptr->set_pattern(pattern);
    }

    //-------------------------------------------------------------------------------------------------

    Logger::AppenderPtr Logger::simpleFile(const std::string &fileName, bool truncated)
    {
      return std::make_shared<spdlog::sinks::simple_file_sink_mt>(fileName, truncated);
    }

    //-------------------------------------------------------------------------------------------------

    Logger::AppenderPtr Logger::rotatingFile(const std::string &baseFileName, size_t maxSize, size_t maxNFiles)
    {
      return std::make_shared<spdlog::sinks::rotating_file_sink_mt>(baseFileName, maxSize, maxNFiles);
    }

    //-------------------------------------------------------------------------------------------------

    Logger::AppenderPtr Logger::dailyFile(const std::string &baseFileName, int rotationHour, int rotationMinute)
    {
      return std::make_shared<spdlog::sinks::daily_file_sink_mt>(baseFileName, rotationHour, rotationMinute);
    }

    //-------------------------------------------------------------------------------------------------

    Logger::AppenderPtr Logger::console()
    {
      return std::make_shared<spdlog::sinks::stdout_sink_mt>();
    }

    //-------------------------------------------------------------------------------------------------

    Logger::AppenderPtr Logger::coloredConsole()
    {
      return std::make_shared<spdlog::sinks::ansicolor_sink>(Logger::console());
    }

    //-------------------------------------------------------------------------------------------------

    Logger::AppenderPtr Logger::remote()
    {
      return std::make_shared<remote_sink>();
    }

  }

}
