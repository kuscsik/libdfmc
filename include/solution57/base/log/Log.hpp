#ifndef DFMC_BASE_LOG_LOG_HPP
#define DFMC_BASE_LOG_LOG_HPP
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
#include <sstream>

#define DFMCLOG(...) dfmc::Logger::WriteLine(dfmc::LogLocation(__FILE__, __FUNCTION__, __LINE__),  __VA_ARGS__)

// FIX: Collapse this to something that doesnt require {} since it behaves strange if used like this
// 1.   if( something )
// 2.     DFMCLOG_LINE("");
// 3.   else
// 4.     DFMCLOG_LINE("");
// It produces a compile error on line3 (else without if) due to the ending ';' on line 2 
#define DFMCLOG_LINE(lINE) \
  { \
    std::stringstream sTREAM; \
    sTREAM << lINE; \
    dfmc::Logger::WriteLine(dfmc::LogLocation(__FILE__, __FUNCTION__, __LINE__), sTREAM); \
  }

#define DFMCLOG_LINE_IF(cOND, lINE) \
if (cOND) \
  { \
    std::stringstream sTREAM; \
    sTREAM << lINE; \
    dfmc::Logger::WriteLine(dfmc::LogLocation(__FILE__, __FUNCTION__, __LINE__), sTREAM); \
  }

#endif
