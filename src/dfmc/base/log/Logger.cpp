#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
// ----------------------------------------------------------------------------
// Copyright 2013 DFMC Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------------------------------------------------------

#include <dfmc/base/log/Logger.hpp>
#include <cassert>
#include <ctime>
#include <sstream>
#include <dfmc/base/thread/Mutex.hpp>
#include <dfmc/base/thread/LockGuard.hpp>
#include "adapter/LogAdapter.hpp"
#include "LogStringEncoder.hpp"

#include "LogConfig.hpp"

namespace dfmc
{

  namespace
  {
    Mutex gMutex;
    adapter::LogAdapter gAdapter;
    LogStringEncoder gEncoder;
    std::stringstream gStream;

    std::ostream& operator<<(std::ostream& stream, const LogLocation& location)
    {
      stream << gEncoder.Encode(location.pszFile) 
             << LOG_SEPERATOR_CHAR 
             << gEncoder.Encode(location.pszFunction) 
             << LOG_SEPERATOR_CHAR 
             << location.line;
      return stream;
   }

    void PrepareStream(std::stringstream& rStream, const LogLocation& location)
    {
      char szTimestamp[128];
      // Get current gmt time.
      time_t rawtime;
      struct tm* pTimeInfo;
      time(&rawtime);
      pTimeInfo = gmtime(&rawtime);

      strftime(szTimestamp, 128, "%Y-%m-%d %H:%M:%S", pTimeInfo);

      // FIX: read the thread id
      const int threadId = 0;

      // Reuse the string stream. Ugly but its the way its done :/
      rStream.str( std::string() );
      rStream.clear();

      rStream << gEncoder.Encode(szTimestamp) << LOG_SEPERATOR_CHAR << threadId << LOG_SEPERATOR_CHAR << location << LOG_SEPERATOR_CHAR;
    }
  }

  void Logger::WriteLine(const LogLocation& location, const char*const psz)
  {
    LockGuard<Mutex> lock(gMutex);

    PrepareStream(gStream, location);
    gStream << gEncoder.Encode(psz);

    gAdapter.WriteLine(gStream.str());
  }

  void Logger::WriteLine(const LogLocation& location, const char*const psz, const LogKeyValueStringBuilder& builder)
  {
    LockGuard<Mutex> lock(gMutex);

    PrepareStream(gStream, location);
    gStream << gEncoder.Encode(psz) << LOG_SEPERATOR_CHAR << builder.GetString();

    gAdapter.WriteLine(gStream.str());
  }


  void Logger::WriteLine(const LogLocation& location, const std::string& str)
  {
    LockGuard<Mutex> lock(gMutex);
    //std::string t1("Hello world");
    //std::string t2("Hel\"lo world");
    //std::string t3("Hel\"\"lo world");
    //std::string t4("\"Hel\"\"lo world\"");

    //std::string r1 = gEncoder.Encode(t1);
    //std::string r2 = gEncoder.Encode(t2);
    //std::string r3 = gEncoder.Encode(t3);
    //std::string r4 = gEncoder.Encode(t4);

    PrepareStream(gStream, location);
    gStream << gEncoder.Encode(str);

    gAdapter.WriteLine(gStream.str());
  }

  void Logger::WriteLine(const LogLocation& location, const std::string& str, const LogKeyValueStringBuilder& builder)
  {
    LockGuard<Mutex> lock(gMutex);

    PrepareStream(gStream, location);
    gStream << gEncoder.Encode(str) << LOG_SEPERATOR_CHAR << builder.GetString();

    gAdapter.WriteLine(gStream.str());
  }


  void Logger::WriteLine(const LogLocation& location, const std::stringstream& stream)
  {
    WriteLine(location, stream.str());
  }

  void Logger::WriteLine(const LogLocation& location, const std::stringstream& stream, const LogKeyValueStringBuilder& builder)
  {
    WriteLine(location, stream.str(), builder);
  }


  void Logger::WriteLine(const LogLocation& location, const LogKeyValueStringBuilder& builder)
  {
    LockGuard<Mutex> lock(gMutex);

    PrepareStream(gStream, location);
    gStream << builder.GetString();

    gAdapter.WriteLine(gStream.str());
  }

}
