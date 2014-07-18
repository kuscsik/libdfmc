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

#include <dfmc/base/log/LogKeyValueStringBuilder.hpp>
#include "LogConfig.hpp"
#include "LogStringEncoder.hpp"

namespace dfmc
{

  LogKeyValueStringBuilder::LogKeyValueStringBuilder()
    : mStream()
    , mEntries(0)
    , mEncoder(new LogStringEncoder())
  {
  }

  LogKeyValueStringBuilder::~LogKeyValueStringBuilder()
  {
  }

  void LogKeyValueStringBuilder::Clear()
  {
    mEntries = 0;
    
    // Reuse the string stream. Ugly but its the way its done :/
    mStream.str( std::string() );
    mStream.clear();
  }

  void LogKeyValueStringBuilder::Add(const char*const pszKey, const bool value)
  {
    Add(pszKey, (value ? 1 : 0));
  }

  void LogKeyValueStringBuilder::Add(const char*const pszKey, const uint8_t value)
  {
    if( mEntries > 0 )
      mStream << LOG_SEPERATOR_CHAR;
    mStream << mEncoder->Encode(pszKey) << LOG_SEPERATOR_CHAR << (int)value;
    ++mEntries;
  }

  void LogKeyValueStringBuilder::Add(const char*const pszKey, const int8_t value)
  {
    if( mEntries > 0 )
      mStream << LOG_SEPERATOR_CHAR;
    mStream << mEncoder->Encode(pszKey) << LOG_SEPERATOR_CHAR << (int)value;
    ++mEntries;
  }

  void LogKeyValueStringBuilder::Add(const char*const pszKey, const uint16_t value)
  {
    if( mEntries > 0 )
      mStream << LOG_SEPERATOR_CHAR;
    mStream << mEncoder->Encode(pszKey) << LOG_SEPERATOR_CHAR << value;
    ++mEntries;
  }

  void LogKeyValueStringBuilder::Add(const char*const pszKey, const int16_t value)
  {
    if( mEntries > 0 )
      mStream << LOG_SEPERATOR_CHAR;
    mStream << mEncoder->Encode(pszKey) << LOG_SEPERATOR_CHAR << value;
    ++mEntries;
  }

  void LogKeyValueStringBuilder::Add(const char*const pszKey, const uint32_t value)
  {
    if( mEntries > 0 )
      mStream << LOG_SEPERATOR_CHAR;
    mStream << mEncoder->Encode(pszKey) << LOG_SEPERATOR_CHAR << value;
    ++mEntries;
  }

  void LogKeyValueStringBuilder::Add(const char*const pszKey, const int32_t value)
  {
    if( mEntries > 0 )
      mStream << LOG_SEPERATOR_CHAR;
    mStream << mEncoder->Encode(pszKey) << LOG_SEPERATOR_CHAR << value;
    ++mEntries;
  }

  void LogKeyValueStringBuilder::Add(const char*const pszKey, const uint64_t value)
  {
    if( mEntries > 0 )
      mStream << LOG_SEPERATOR_CHAR;
    mStream << mEncoder->Encode(pszKey) << LOG_SEPERATOR_CHAR << value;
    ++mEntries;
  }

  void LogKeyValueStringBuilder::Add(const char*const pszKey, const int64_t value)
  {
    if( mEntries > 0 )
      mStream << LOG_SEPERATOR_CHAR;
    mStream << mEncoder->Encode(pszKey) << LOG_SEPERATOR_CHAR << value;
    ++mEntries;
  }

  void LogKeyValueStringBuilder::Add(const char*const pszKey, const float value)
  {
    if( mEntries > 0 )
      mStream << LOG_SEPERATOR_CHAR;
    mStream << mEncoder->Encode(pszKey) << LOG_SEPERATOR_CHAR << value;
    ++mEntries;
  }

  void LogKeyValueStringBuilder::Add(const char*const pszKey, const double value)
  {
    if( mEntries > 0 )
      mStream << LOG_SEPERATOR_CHAR;
    mStream << mEncoder->Encode(pszKey) << LOG_SEPERATOR_CHAR << value;
    ++mEntries;
  }

  void LogKeyValueStringBuilder::Add(const char*const pszKey, const char*const pszValue)
  {
    if( mEntries > 0 )
      mStream << LOG_SEPERATOR_CHAR;
    mStream << mEncoder->Encode(pszKey) << LOG_SEPERATOR_CHAR << mEncoder->Encode(pszValue);
    ++mEntries;
  }


  void LogKeyValueStringBuilder::Add(const char*const pszKey, const std::string& value)
  {
    if( mEntries > 0 )
      mStream << LOG_SEPERATOR_CHAR;
    mStream << mEncoder->Encode(pszKey) << LOG_SEPERATOR_CHAR << mEncoder->Encode(value);
    ++mEntries;
  }

  const std::string LogKeyValueStringBuilder::GetString() const
  {
    return mStream.str();
  }

}
