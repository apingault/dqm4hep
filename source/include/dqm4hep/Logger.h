/// \file DQMLogger.h
/*
 *
 * DQMLogger.h header template automatically generated by a class generator
 * Creation date : jeu. mai 7 2015
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


#ifndef DQM4HEP_LOGGER_H
#define DQM4HEP_LOGGER_H

// -- dqm4hep headers
#include "dqm4hep/DQM4HEP.h"

// -- std headers
#include <string>
#include <mutex>
#include <fstream>
#include <memory>

#include "spdlog/logger.h"
#include "spdlog/spdlog.h"

namespace dqm4hep {

  namespace core {

    class Logger
    {
    public:
      typedef std::shared_ptr<spdlog::logger> LoggerPtr;
      typedef std::shared_ptr<spdlog::sinks::sink> AppenderPtr;
      typedef spdlog::level::level_enum Level;

    public:
      /**
       * Create a new logger with the target appenders
       *
       * @param  name      the logger name
       * @param  appenders the list of appenders
       * @return           a logger pointer (smart ptr)
       */
      static LoggerPtr createLogger(const std::string &name, std::initializer_list<AppenderPtr> appenders);

      /**
       * Create a new logger with the target appenders
       *
       * @param  name      the logger name
       * @param  appenders the list of appenders
       * @return           a logger pointer (smart ptr)
       */
      static LoggerPtr createLogger(const std::string &name, const std::vector<AppenderPtr> &appenders);

      /**
       * Create a simple file appender
       * @param  fileName  the file name
       * @param  truncated whether to truncate the file if needed
       * @return           an appender pointer (smart pointer)
       */
      static AppenderPtr simpleFile(const std::string &fileName, bool truncated = false);

      /**
       * Create a rotating file appender
       * @param  baseFileName the base file name
       * @param  maxSize      the maximum single file size (unit bytes)
       * @param  maxNFiles    the maximum number of files to rotate with
       * @return              an appender pointer (smart pointer)
       */
      static AppenderPtr rotatingFile(const std::string &baseFileName, size_t maxSize, size_t maxNFiles);

      /**
       * Create a daily file appender
       * @param  baseFileName   the base file name
       * @param  rotationHour   the hour for rotation
       * @param  rotationMinute the minute for rotation
       * @return                an appender pointer (smart pointer)
       */
      static AppenderPtr dailyFile(const std::string &baseFileName, int rotationHour, int rotationMinute);

      /**
       * Create a console appender
       * @return an appender pointer (smart pointer)
       */
      static AppenderPtr console();

      /**
       * Create a colored console appender
       * @return an appender pointer (smart pointer)
       */
      static AppenderPtr coloredConsole();

      /**
       * Create a remote appender
       * @return an appender pointer (smart pointer)
       */
      static AppenderPtr remote();

      /**
       * Get an existing logger
       * @param  name the logger name
       * @return      a logger pointer (smart pointer) or nullptr if doesn't exists
       */
      static LoggerPtr logger(const std::string &name);

      /**
       * Set the log level of the main logger
       * @param level the log level
       */
      static void setLogLevel(Level level);

      /**
       * Get the main logger
       * @return  a logger pointer (smart pointer)
       */
      static LoggerPtr mainLogger();

      /**
       * Change the main logger or the target one
       * @param  logger the new main logger name
       * @return        a pointer to the main logger
       */
      static LoggerPtr setMainLogger(const std::string &logger);

      /**
       * Convert log level to std::string
       * @param  level the log level
       * @return       log level in string format
       */
      static std::string logLevelToString(Level level);

      /**
       * Set the logger log format pattern
       *
       * %v 	The actual text to log
       * %t 	Thread id
       * %P 	Process id
       * %n 	Logger's name
       * %l 	The log level of the message
       * %L 	Short log level of the message, i.e	"D", "I", etc
       * %a 	Abbreviated weekday name, i.e "Thu"
       * %A 	Full weekday name, i.e "Thursday"
       * %b 	Abbreviated month name, i.e "Aug"
       * %B 	Full month name, i.e "August"
       * %c 	Date and time representation, i.e "Thu Aug 23 15:35:46 2014"
       * %C 	Year in 2 digits, i.e "14"
       * %Y 	Year in 4 digits, i.e "2014"
       * %D   (or %x) 	Short MM/DD/YY date
       * %m 	Month 1-12
       * %d 	Day of month 1-31
       * %H 	Hours in 24 format 0-23
       * %I 	Hours in 12 format 1-12
       * %M 	Minutes 0-59
       * %S 	Seconds 0-59
       * %e 	Millisecond part of the current second 0-999 	"678"
       * %f 	Microsecond part of the current second 0-999999 	"056789"
       * %F 	Nanosecond part of the current second 0-999999999 	"256789123"
       * %p 	AM/PM 	"AM"
       * %r 	12 hour clock 	"02:55:02 pm"
       * %R 	24-hour HH:MM time, equivalent to %H:%M 	"23:55"
       * %T   (or %X) 	ISO 8601 time format (HH:MM:SS), equivalent to %H:%M:%S 	"23:55:59"
       * %z 	ISO 8601 offset from UTC in timezone ([+/-]HH:MM) 	"+02:00"
       * %% 	The % sign 	"%"
       * %+ 	default format 	"[2014-31-10 23:46:59.678] [mylogger] [info] Some message"
       *
       * @param logger  the logger name
       * @param pattern the logging pattern
       */
      static void setLoggerPattern(const std::string &logger, const std::string &pattern);

    private:
      static LoggerPtr      m_mainLogger;   ///< The main logger instance
    };

  }

}

#endif  //  DQM4HEP_LOGGER_H
