#ifndef DFMC_STRING_PARSEUTIL_HPP
#define DFMC_STRING_PARSEUTIL_HPP
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

#include <dfmc/base/BasicTypes.hpp>
#include <dfmc/base/Noncopyable.hpp>

namespace dfmc
{
  class ParseUtil : private Noncopyable
  {
  public:
    // Returns the number of characters that was consumed from psz (0 on error)
    static int ParseString(bool& rDst, const char*const psz);
    static int ParseString(uint8_t& rDst, const char*const psz);
    static int ParseString(uint16_t& rDst, const char*const psz);
    static int ParseString(uint32_t& rDst, const char*const psz);
    //static int ParseString(uint64_t& rDst, const char*const psz);
    static int ParseString(int8_t& rDst, const char*const psz);
    static int ParseString(int16_t& rDst, const char*const psz);
    static int ParseString(int32_t& rDst, const char*const psz);
    //static int ParseString(int64_t& rDst, const char*const psz);
    static int ParseString(float& rDst, const char*const psz);
    static int ParseString(double& rDst, const char*const psz);

    // Returns the number of characters that was consumed from psz (0 on error)
    static int ParseSubString(bool& rDst, const char*const psz, const int startIndex, const int length);
    static int ParseSubString(uint8_t& rDst, const char*const psz, const int startIndex, const int length);
    static int ParseSubString(uint16_t& rDst, const char*const psz, const int startIndex, const int length);
    static int ParseSubString(uint32_t& rDst, const char*const psz, const int startIndex, const int length);
    //static int ParseSubString(uint64_t& rDst, const char*const psz, const int startIndex, const int length);
    static int ParseSubString(int8_t& rDst, const char*const psz, const int startIndex, const int length);
    static int ParseSubString(int16_t& rDst, const char*const psz, const int startIndex, const int length);
    static int ParseSubString(int32_t& rDst, const char*const psz, const int startIndex, const int length);
    //static int ParseSubString(int64_t& rDst, const char*const psz, const int startIndex, const int length);
    static int ParseSubString(float& rDst, const char*const psz, const int startIndex, const int length);
    static int ParseSubString(double& rDst, const char*const psz, const int startIndex, const int length);

    // Arrays

    // Return <0 on error
    //static int ParseArrayString(bool* pDstArray, const int dstLength, const char*const psz);
    static int ParseArrayString(uint8_t* pDstArray, const int dstLength, const char*const psz);
    static int ParseArrayString(uint16_t* pDstArray, const int dstLength, const char*const psz);
    static int ParseArrayString(uint32_t* pDstArray, const int dstLength, const char*const psz);
    //static int ParseArrayString(uint64_t* pDstArray, const int dstLength, const char*const psz);
    static int ParseArrayString(int8_t* pDstArray, const int dstLength, const char*const psz);
    static int ParseArrayString(int16_t* pDstArray, const int dstLength, const char*const psz);
    static int ParseArrayString(int32_t* pDstArray, const int dstLength, const char*const psz);
    //static int ParseArrayString(int64_t* pDstArray, const int dstLength, const char*const psz);
    //static int ParseArrayString(float* pValue, const int dstLength, const char*const psz);
    //static int ParseArrayString(double* pValue, const int dstLength, const char*const psz);
  };
}

#endif
