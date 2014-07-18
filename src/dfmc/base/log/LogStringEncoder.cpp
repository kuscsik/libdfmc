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

#include "LogStringEncoder.hpp"
#include <algorithm>

namespace dfmc
{
  const std::string LogStringEncoder::Encode(const char*const psz)
  {
    return (psz != nullptr ? Encode(std::string(psz)) : std::string());
  }


  const std::string LogStringEncoder::Encode(const std::string& str)
  {
    // Reuse the string stream. Ugly but its the way its done :/
    mStream.str( std::string() );
    mStream.clear();

    mStream << '"';
    {
      std::string::const_iterator itrFrom = str.begin();
      std::string::const_iterator itrTo = str.end();
      std::string::const_iterator itrFound;
      do 
      {
        itrFound = std::find(itrFrom, itrTo, '"');

        while(itrFrom != itrFound)
        {
          mStream << *itrFrom;
          ++itrFrom;
        }
        if( itrFound != itrTo )
        {
          mStream << "\"\"";
          ++itrFound;
          itrFrom = itrFound;
        }
      } while ( itrFound != itrTo );
    }
    mStream << '"';
    return mStream.str();
  }
}

