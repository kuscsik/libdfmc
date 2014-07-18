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

#include "LogAdapter.hpp"
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace dfmc {
namespace adapter 
{

  FILE * gpLogFile = nullptr;
  LogAdapter::LogAdapter()
  {
    std::string fileName;
    fileName.append("/StressLog_");

    char szTimestamp[128];
    // Get current gmt time.
    time_t rawtime;
    struct tm* pTimeInfo;
    time(&rawtime);
    pTimeInfo = gmtime(&rawtime);

    strftime(szTimestamp, 128, "%Y-%m-%d %H:%M:%S", pTimeInfo);

    fileName.append(szTimestamp);

    memset(szTimestamp, 0, 128);
#ifdef _WIN32
    sprintf(szTimestamp, "_%i", GetCurrentProcessId());
#else
    sprintf(szTimestamp, "_%i", getpid());
#endif
    fileName.append(szTimestamp);

    fileName.append(".log");

    gpLogFile = fopen(fileName.c_str(), "wb");
    std::cout << "Writing test log to file: " << fileName << std::endl;
    std::cout.flush();
  }


  LogAdapter::~LogAdapter()
  {
    if (gpLogFile != nullptr)
    {
      fflush(gpLogFile);
      fclose(gpLogFile);
    }

  }


  void LogAdapter::WriteLine(const std::string& str)
  {
    const char *end = "\n\n";
    std::cout << str << std::endl;
    std::cout.flush();
    if (gpLogFile != nullptr)
    {
      fwrite((void*)str.c_str(), 1, str.size(), gpLogFile);
      fwrite((void*)(end), 1, 1, gpLogFile);
    }
  }

}}
