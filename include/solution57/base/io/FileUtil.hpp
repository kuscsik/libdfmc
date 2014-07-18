#ifndef DFMC_BASE_IO_FILEUTIL_HPP
#define DFMC_BASE_IO_FILEUTIL_HPP
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

// Must be the first include!!
#include <dfmc/base/Config.hpp>

#include <string>

namespace dfmc
{
  class FileUtil
  {
  public:
    // @brief Open the given file reads all lines and closes it again, then returns the content
    // @throws IOException if there is a problem reading the file
    // @return the content of the file.
    static const std::string ReadAllText(const std::string& strFilename);
  };
}
#endif
