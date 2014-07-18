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

#include <dfmc/base/io/FileUtil.hpp>
#include <dfmc/base/Exceptions.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

namespace dfmc
{
  const std::string FileUtil::ReadAllText(const std::string& strFilename)
  {
    std::ifstream file(strFilename, std::ios::in | std::ios::binary);

    if (!file)
    {
      std::string str("File doesn't exist '");
      str += strFilename;
      str += "'";
      throw IOException(str);
    }

    try
    {
      // Get length of file:
      file.seekg(0, file.end);
      const std::streamoff fileLength = file.tellg();
      file.seekg(0, file.beg);
      if (fileLength > std::numeric_limits<std::size_t>::max())
      {
        std::string str("File is too large '");
        str += strFilename;
        str += "'";
        throw IOException(str);
      }

      const size_t length = static_cast<size_t>(fileLength);

      // Read the entire content of the file
      std::vector<char> content(length + 1);
      file.read(&content[0], length);
      content[length] = 0;

      if (length != static_cast<size_t>(file.gcount()))
      {
        std::string str("Failed to read entire file '");
        str += strFilename;
        str += "'";
        throw IOException(str);
      }

      // Convert it to a string
      return std::string(&content[0]);
    }
    catch (const std::ios_base::failure& ex)
    {
      throw IOException(ex.what());
    }
  }
}
