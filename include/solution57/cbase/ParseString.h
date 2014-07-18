#ifndef DFMC_PARSESTRING_H
#define DFMC_PARSESTRING_H
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

#include <dfmc/cbase/BasicTypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

  // Returns the number of characters that was consumed from psz (0 on error)
  int ParseString_bool(int* pDst, const char*const psz);
  int ParseString_uint8_t(uint8_t* pDst, const char*const psz);
  int ParseString_uint16_t(uint16_t* pDst, const char*const psz);
  int ParseString_uint32_t(uint32_t* pDst, const char*const psz);
  //int ParseString_uint64_t(uint64_t* pDst, const char*const psz);
  int ParseString_int8_t(int8_t* pDst, const char*const psz);
  int ParseString_int16_t(int16_t* pDst, const char*const psz);
  int ParseString_int32_t(int32_t* pDst, const char*const psz);
  //int ParseString_int64_t(int64_t* pDst, const char*const psz);
  int ParseString_float(float* pDst, const char*const psz);
  int ParseString_double(double* pDst, const char*const psz);

  // Returns the number of characters that was consumed from psz (0 on error)
  int ParseSubString_bool(int* pDst, const char*const psz, const int startIndex, const int length);
  int ParseSubString_uint8_t(uint8_t* pDst, const char*const psz, const int startIndex, const int length);
  int ParseSubString_uint16_t(uint16_t* pDst, const char*const psz, const int startIndex, const int length);
  int ParseSubString_uint32_t(uint32_t* pDst, const char*const psz, const int startIndex, const int length);
  //int ParseSubString_uint64_t(uint64_t* pDst, const char*const psz, const int startIndex, const int length);
  int ParseSubString_int8_t(int8_t* pDst, const char*const psz, const int startIndex, const int length);
  int ParseSubString_int16_t(int16_t* pDst, const char*const psz, const int startIndex, const int length);
  int ParseSubString_int32_t(int32_t* pDst, const char*const psz, const int startIndex, const int length);
  //int ParseSubString_int64_t(int64_t* pDst, const char*const psz, const int startIndex, const int length);
  int ParseSubString_float(float* pDst, const char*const psz, const int startIndex, const int length);
  int ParseSubString_double(double* pDst, const char*const psz, const int startIndex, const int length);

  // Arrays

  // Return <0 on error
  int ParseArrayString_bool(int* pDstArray, const int dstLength, const char*const psz);
  int ParseArrayString_uint8_t(uint8_t* pDstArray, const int dstLength, const char*const psz);
  int ParseArrayString_uint16_t(uint16_t* pDstArray, const int dstLength, const char*const psz);
  int ParseArrayString_uint32_t(uint32_t* pDstArray, const int dstLength, const char*const psz);
  //int ParseArrayString_uint64_t(uint64_t* pDstArray, const int dstLength, const char*const psz);
  int ParseArrayString_int8_t(int8_t* pDstArray, const int dstLength, const char*const psz);
  int ParseArrayString_int16_t(int16_t* pDstArray, const int dstLength, const char*const psz);
  int ParseArrayString_int32_t(int32_t* pDstArray, const int dstLength, const char*const psz);
  //int ParseArrayString_int64_t(int64_t* pDstArray, const int dstLength, const char*const psz);
  //int ParseArrayString_float_t(float* pValue, const int dstLength, const char*const psz);
  //int ParseArrayString_double_t(double* pValue, const int dstLength, const char*const psz);

#ifdef __cplusplus
}
#endif

#endif
