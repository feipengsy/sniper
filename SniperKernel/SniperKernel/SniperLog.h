#ifndef SNIPER_SNIPER_LOG_H
#define SNIPER_SNIPER_LOG_H

#include <iostream>
#include <iomanip>

namespace SniperLog
{
    enum {
	Debug = 2,
	Info  = 3,
	Warn  = 4,
	Error = 5,
	Fatal = 6
    };

    //2:debug, 3:info, 4:warn, 5:error, 6:fatal
    extern int  LogLevel;
}

#define LogDebug  if (SniperLog::LogLevel <= SniperLog::Debug ) \
    std::cout << std::setiosflags(std::ios::left) << std::setw(24) << (this->name()+'.'+__func__) << "  DEBUG: "

#define LogInfo  if (SniperLog::LogLevel <= SniperLog::Info ) \
    std::cout << std::setiosflags(std::ios::left) << std::setw(24) << (this->name()+'.'+__func__) << "   INFO: "

#define LogWarn  if (SniperLog::LogLevel <= SniperLog::Warn ) \
    std::cout << std::setiosflags(std::ios::left) << std::setw(24) << (this->name()+'.'+__func__) << "   WARN: "

#define LogError  if (SniperLog::LogLevel <= SniperLog::Error ) \
    std::cout << std::setiosflags(std::ios::left) << std::setw(24) << (this->name()+'.'+__func__) << "  ERROR: "

#define LogFatal  if (SniperLog::LogLevel <= SniperLog::Fatal ) \
    std::cout << std::setiosflags(std::ios::left) << std::setw(24) << (this->name()+'.'+__func__) << "  FATAL: "

#define LogAlways \
    std::cout << std::setiosflags(std::ios::left) << std::setw(24) << (this->name()+'.'+__func__) << " ALWAYS: "

#endif
