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

#include <dfmc/base/string/ParseUtil.hpp>
#include <dfmc/cbase/ParseString.h>
#include <cassert>

namespace dfmc
{
  int ParseUtil::ParseString(bool& rDst, const char*const psz)
  {
    assert(psz != nullptr);
    int res;
    int returned = ParseString_bool(&res, psz);
    if (returned > 0)
      rDst = res != 0;
    return returned;
  }

  int ParseUtil::ParseString(uint8_t& rDst, const char*const psz)
  { 
    assert(psz != nullptr);
    return ParseString_uint8_t(&rDst, psz); 
  }

  int ParseUtil::ParseString(uint16_t& rDst, const char*const psz)
  {
    assert(psz != nullptr);
    return ParseString_uint16_t(&rDst, psz);
  }

  int ParseUtil::ParseString(uint32_t& rDst, const char*const psz)
  {
    assert(psz != nullptr);
    return ParseString_uint32_t(&rDst, psz);
  }

  //int ParseUtil::ParseString(uint64_t& rDst, const char*const psz)
  //{
  //  assert(psz != nullptr);
  //  return ParseString_uint64_t(&rDst, psz);
  //}

  int ParseUtil::ParseString(int8_t& rDst, const char*const psz)
  {
    assert(psz != nullptr);
    return ParseString_int8_t(&rDst, psz);
  }

  int ParseUtil::ParseString(int16_t& rDst, const char*const psz)
  {
    assert(psz != nullptr);
    return ParseString_int16_t(&rDst, psz);
  }

  int ParseUtil::ParseString(int32_t& rDst, const char*const psz)
  {
    assert(psz != nullptr);
    return ParseString_int32_t(&rDst, psz);
  }

  //int ParseUtil::ParseString(int64_t& rDst, const char*const psz);
  //{
  //  assert(psz != nullptr);
  //  return ParseString_int64_t(&rDst, psz);
  //}

  int ParseUtil::ParseString(float& rDst, const char*const psz)
  {
    assert(psz != nullptr);
    return ParseString_float(&rDst, psz);
  }

  int ParseUtil::ParseString(double& rDst, const char*const psz)
  {
    assert(psz != nullptr);
    return ParseString_double(&rDst, psz);
  }

  // Returns the number of characters that was consumed from psz (0 on error)
  int ParseUtil::ParseSubString(bool& rDst, const char*const psz, const int startIndex, const int length)
  {
    assert(psz != nullptr);
    int res;
    int returned = ParseSubString_bool(&res, psz, startIndex, length);
    if (returned > 0)
      rDst = res != 0;
    return returned;
  }

  int ParseUtil::ParseSubString(uint8_t& rDst, const char*const psz, const int startIndex, const int length)
  {
    assert(psz != nullptr);
    return ParseSubString_uint8_t(&rDst, psz, startIndex, length);
  }

  int ParseUtil::ParseSubString(uint16_t& rDst, const char*const psz, const int startIndex, const int length)
  {
    assert(psz != nullptr);
    return ParseSubString_uint16_t(&rDst, psz, startIndex, length);
  }

  int ParseUtil::ParseSubString(uint32_t& rDst, const char*const psz, const int startIndex, const int length)
  {
    assert(psz != nullptr);
    return ParseSubString_uint32_t(&rDst, psz, startIndex, length);
  }

  //int ParseUtil::ParseSubString(uint64_t& rDst, const char*const psz, const int startIndex, const int length);
  //{
  //  assert(psz != nullptr);
  //  return ParseSubString_uint64_t(&rDst, psz, startIndex, length);
  //}

  int ParseUtil::ParseSubString(int8_t& rDst, const char*const psz, const int startIndex, const int length)
  {
    assert(psz != nullptr);
    return ParseSubString_int8_t(&rDst, psz, startIndex, length);
  }

  int ParseUtil::ParseSubString(int16_t& rDst, const char*const psz, const int startIndex, const int length)
  {
    assert(psz != nullptr);
    return ParseSubString_int16_t(&rDst, psz, startIndex, length);
  }

  int ParseSubString(int32_t& rDst, const char*const psz, const int startIndex, const int length)
  {
    assert(psz != nullptr);
    return ParseSubString_int32_t(&rDst, psz, startIndex, length);
  }

  //int ParseUtil::ParseSubString(int64_t& rDst, const char*const psz, const int startIndex, const int length)
  //{
  //  assert(psz != nullptr);
  //  return ParseSubString_uint64_t(&rDst, psz, startIndex, length);
  //}

  int ParseUtil::ParseSubString(float& rDst, const char*const psz, const int startIndex, const int length)
  {
    assert(psz != nullptr);
    return ParseSubString_float(&rDst, psz, startIndex, length);
  }

  int ParseUtil::ParseSubString(double& rDst, const char*const psz, const int startIndex, const int length)
  {
    assert(psz != nullptr);
    return ParseSubString_double(&rDst, psz, startIndex, length);
  }

  // Arrays

  // Return <0 on error
  //int ParseUtil::ParseArrayString(int* pDstArray, const int dstLength, const char*const psz);

  int ParseUtil::ParseArrayString(uint8_t* pDstArray, const int dstLength, const char*const psz)
  {
    assert(pDstArray != nullptr);
    assert(psz != nullptr);
    return ParseArrayString_uint8_t(pDstArray, dstLength, psz);
  }

  int ParseUtil::ParseArrayString(uint16_t* pDstArray, const int dstLength, const char*const psz)
  {
    assert(pDstArray != nullptr);
    assert(psz != nullptr);
    return ParseArrayString_uint16_t(pDstArray, dstLength, psz);
  }

  int ParseUtil::ParseArrayString(uint32_t* pDstArray, const int dstLength, const char*const psz)
  {
    assert(pDstArray != nullptr);
    assert(psz != nullptr);
    return ParseArrayString_uint32_t(pDstArray, dstLength, psz);
  }

  //int ParseUtil::ParseArrayString(uint64_t* pDstArray, const int dstLength, const char*const psz)
  //{
  //  assert(pDstArray != nullptr);
  //  assert(psz != nullptr);
  //  return ParseArrayString_uint64_t(pDstArray, dstLength, psz);
  //}

  int ParseUtil::ParseArrayString(int8_t* pDstArray, const int dstLength, const char*const psz)
  {
    assert(pDstArray != nullptr);
    assert(psz != nullptr);
    return ParseArrayString_int8_t(pDstArray, dstLength, psz);
  }

  int ParseUtil::ParseArrayString(int16_t* pDstArray, const int dstLength, const char*const psz)
  {
    assert(pDstArray != nullptr);
    assert(psz != nullptr);
    return ParseArrayString_int16_t(pDstArray, dstLength, psz);
  }

  int ParseUtil::ParseArrayString(int32_t* pDstArray, const int dstLength, const char*const psz)
  {
    assert(pDstArray != nullptr);
    assert(psz != nullptr);
    return ParseArrayString_int32_t(pDstArray, dstLength, psz);
  }

  //int ParseUtil::ParseArrayString(int64_t* pDstArray, const int dstLength, const char*const psz)
  //{
  //  assert(pDstArray != nullptr);
  //  assert(psz != nullptr);
  //  return ParseArrayString_int64_t(pDstArray, dstLength, psz);
  //}

  //int ParseUtil::ParseArrayString(float* pValue, const int dstLength, const char*const psz)
  //{
  //  assert(pDstArray != nullptr);
  //  assert(psz != nullptr);
  //  return ParseArrayString_float(pDstArray, dstLength, psz);
  //}

  //int ParseUtil::ParseArrayString(double* pValue, const int dstLength, const char*const psz)
  //{
  //  assert(pDstArray != nullptr);
  //  assert(psz != nullptr);
  //  return ParseArrayString_double(pDstArray, dstLength, psz);
  //}

}
