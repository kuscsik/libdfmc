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

#include <dfmc/cbase/ParseString.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define BOOL_TRUE 1
#define BOOL_FALSE 0

// Nasty C style template method :)
#define PARSE_ARRAY_STRING(sUBsTRINGfUNCTION) \
  const char* pszCurrent = psz; \
  const int len = strlen(psz); \
  const char*const pszEnd = psz + len; \
  int count; \
  int index = 0; \
  int charactersConsumed; \
  \
  if (len < 3 || psz[0] != '[' || psz[len - 1] != ']') \
    return -1; \
  \
  ++pszCurrent; \
  while (pszCurrent < pszEnd && index < dstLength) \
  { \
    count = strcspn(pszCurrent, ",]"); \
    if (index >= dstLength) \
      return -1; \
    charactersConsumed = sUBsTRINGfUNCTION(pDstArray + index, pszCurrent, 0, count); \
    if (charactersConsumed == 0 || charactersConsumed != count) \
      return -1; \
    pszCurrent += count + 1; \
    ++index; \
  } \
  return (pszCurrent == pszEnd ? index : 0);



static int DoParseSubString_uint32_t(uint32_t* pDst, const char*const psz, const int startIndex, const int length)
{
  const int actualLength = strlen(psz);
  const int endIndex = startIndex + length;
  const char* pszSrc = psz + startIndex;
  char* pEnd = NULL;
  long int value;

  if (startIndex < 0 || length < 1 || endIndex > actualLength)
    return 0;

  // Check the string contains a digit as expected
  if ((pszSrc[0] >= '0' && pszSrc[0] <= '9') || (length >= 2 && pszSrc[0] == '+' && (pszSrc[1] >= '0' && pszSrc[1] <= '9')))
  {
    errno = 0;
    value = strtoul(pszSrc, &pEnd, 0);
    if (value == ULONG_MAX && errno == ERANGE)
      return 0;
    *pDst = value;
    return pEnd == (pszSrc + endIndex) ? length : 0;
  }
  return 0;
}


static int DoParseSubString_int32_t(int32_t* pDst, const char*const psz, const int startIndex, const int length)
{
  const int actualLength = strlen(psz);
  const int endIndex = startIndex + length;
  const char* pszSrc = psz + startIndex;
  char* pEnd = NULL;
  long int value;

  if (startIndex < 0 || length < 1 || endIndex > actualLength)
    return 0;

  // Check the string contains a digit as expected
  if ((pszSrc[0] >= '0' && pszSrc[0] <= '9') || (length >= 2 && (pszSrc[0] == '+' || pszSrc[0] == '-') && (pszSrc[1] >= '0' && pszSrc[1] <= '9')))
  {
    errno = 0;
    value = strtol(pszSrc, &pEnd, 0);
    if ((value == LONG_MIN || value == LONG_MAX) && errno == ERANGE)
      return 0;
    *pDst = value;
    return pEnd == (pszSrc + endIndex) ? length : 0;
  }
  return 0;
}

static int DoParseSubString_double(double* pDst, const char*const psz, const int startIndex, const int length)
{
  const int actualLength = strlen(psz);
  const int endIndex = startIndex + length;
  const char* pszSrc = psz + startIndex;
  char* pEnd = NULL;
  double value;

  if (startIndex < 0 || length < 1 || endIndex > actualLength)
    return 0;

  // Check the string doesn't start with a white space
  if (pszSrc[0] != ' ')
  {
    errno = 0;
    value = strtod(pszSrc, &pEnd);
    if (value == HUGE_VAL && errno == ERANGE)
      return 0;
    *pDst = value;
    return pEnd == (pszSrc + endIndex) ? length : 0;
  }
  return 0;
}



int ParseString_bool(int* pDst, const char*const psz)
{
  return ParseSubString_bool(pDst, psz, 0, strlen(psz));
}

int ParseString_uint8_t(uint8_t* pDst, const char*const psz)
{
  return ParseSubString_uint8_t(pDst, psz, 0, strlen(psz));
}

int ParseString_uint16_t(uint16_t* pDst, const char*const psz)
{
  return ParseSubString_uint16_t(pDst, psz, 0, strlen(psz));
}

int ParseString_uint32_t(uint32_t* pDst, const char*const psz)
{
  return ParseSubString_uint32_t(pDst, psz, 0, strlen(psz));
}

//int ParseString_uint64_t(uint64_t* pDst, const char*const psz)
//{
//  return ParseSubString_uint64_t(pDst, psz, 0, strlen(psz));
//}

int ParseString_int8_t(int8_t* pDst, const char*const psz)
{
  return ParseSubString_int8_t(pDst, psz, 0, strlen(psz));
}

int ParseString_int16_t(int16_t* pDst, const char*const psz)
{
  return ParseSubString_int16_t(pDst, psz, 0, strlen(psz));
}

int ParseString_int32_t(int32_t* pDst, const char*const psz)
{
  return ParseSubString_int32_t(pDst, psz, 0, strlen(psz));
}

//int ParseString_int64_t(int64_t* pDst, const char*const psz)
//{
//  return ParseSubString_int64_t(pDst, psz, 0, strlen(psz));
//}

int ParseString_float(float* pDst, const char*const psz)
{
  return ParseSubString_float(pDst, psz, 0, strlen(psz));
}

int ParseString_double(double* pDst, const char*const psz)
{
  return ParseSubString_double(pDst, psz, 0, strlen(psz));
}


int ParseSubString_bool(int* pDst, const char*const psz, const int startIndex, const int length)
{
  const int actualLength = strlen(psz);
  const char* pszSrc = psz + startIndex;
  int charactersConsumed = 0;

  if (startIndex < 0 || length < 1 || (startIndex + length) > actualLength)
    return 0;

  if ( length == 4 && strncmp(pszSrc, "true", 4) == 0)
  {
    *pDst = BOOL_TRUE;
    charactersConsumed = 4;
  }
  else if (length == 1 && strncmp(pszSrc, "1", 1) == 0)
  {
    *pDst = BOOL_TRUE;
    charactersConsumed = 1;
  }
  else if (length == 1 && strncmp(pszSrc, "0", 1) == 0)
  {
    *pDst = BOOL_FALSE;
    charactersConsumed = 1;
  }
  else if (length == 5 && strncmp(pszSrc, "false", 5) == 0)
  {
    *pDst = BOOL_FALSE;
    charactersConsumed = 5;
  }
  return charactersConsumed;
}

int ParseSubString_uint8_t(uint8_t* pDst, const char*const psz, const int startIndex, const int length)
{
  uint32_t res;
  int charactersConsumed = DoParseSubString_uint32_t(&res, psz, startIndex, length);
  if (charactersConsumed <= 0 || res > UINT8_MAX)
    return 0;
  *pDst = (uint8_t)res;
  return charactersConsumed;
}

int ParseSubString_uint16_t(uint16_t* pDst, const char*const psz, const int startIndex, const int length)
{
  uint32_t res;
  int charactersConsumed = DoParseSubString_uint32_t(&res, psz, startIndex, length);
  if ( charactersConsumed <= 0 || res > UINT16_MAX )
    return 0;
  *pDst = (uint16_t)res;
  return charactersConsumed;
}

int ParseSubString_uint32_t(uint32_t* pDst, const char*const psz, const int startIndex, const int length)
{
  uint32_t res;
  int charactersConsumed = DoParseSubString_uint32_t(&res, psz, startIndex, length);
  if (charactersConsumed <= 0 || res > UINT32_MAX)
    return 0;
  *pDst = (uint32_t)res;
  return charactersConsumed;
}

//int ParseSubString_uint64_t(uint64_t* pDst, const char*const psz, const int startIndex, const int length)
//{
//  // Not implemented
//  return 0;
//}

int ParseSubString_int8_t(int8_t* pDst, const char*const psz, const int startIndex, const int length)
{
  int32_t res;
  int charactersConsumed = DoParseSubString_int32_t(&res, psz, startIndex, length);
  if (charactersConsumed <= 0 || res < INT8_MIN ||res > INT8_MAX)
    return 0;
  *pDst = (int8_t)res;
  return charactersConsumed;
}

int ParseSubString_int16_t(int16_t* pDst, const char*const psz, const int startIndex, const int length)
{
  int32_t res;
  int charactersConsumed = DoParseSubString_int32_t(&res, psz, startIndex, length);
  if (charactersConsumed <= 0 || res < INT16_MIN || res > INT16_MAX)
    return 0;
  *pDst = (int16_t)res;
  return charactersConsumed;
}

int ParseSubString_int32_t(int32_t* pDst, const char*const psz, const int startIndex, const int length)
{
  int32_t res;
  int charactersConsumed = DoParseSubString_int32_t(&res, psz, startIndex, length);
  if (charactersConsumed <= 0 || res < INT32_MIN || res > INT32_MAX)
    return 0;
  *pDst = (int32_t)res;
  return charactersConsumed;
}

//int ParseSubString_int64_t(int64_t* pDst, const char*const psz, const int startIndex, const int length)
//{
//  // FIX:
//  return 0;
//}

int ParseSubString_float(float* pDst, const char*const psz, const int startIndex, const int length)
{
  double res;
  int charactersConsumed = DoParseSubString_double(&res, psz, startIndex, length);
  if (charactersConsumed <= 0)
    return 0;
  *pDst = (float)res;
  return charactersConsumed;
}

int ParseSubString_double(double* pDst, const char*const psz, const int startIndex, const int length)
{
  double res;
  int charactersConsumed = DoParseSubString_double(&res, psz, startIndex, length);
  if (charactersConsumed <= 0)
    return 0;
  *pDst = res;
  return charactersConsumed;
}

// Arrays

int ParseArrayString_bool(int* pDstArray, const int dstLength, const char*const psz)
{
  PARSE_ARRAY_STRING(ParseSubString_bool)
}

int ParseArrayString_uint8_t(uint8_t* pDstArray, const int dstLength, const char*const psz)
{
  PARSE_ARRAY_STRING(ParseSubString_uint8_t)
}

int ParseArrayString_uint16_t(uint16_t* pDstArray, const int dstLength, const char*const psz)
{
  PARSE_ARRAY_STRING(ParseSubString_uint16_t)
}

int ParseArrayString_uint32_t(uint32_t* pDstArray, const int dstLength, const char*const psz)
{
  PARSE_ARRAY_STRING(ParseSubString_uint32_t)
}

//int ParseArrayString_uint64_t(uint64_t* pDstArray, const int dstLength, const char*const psz)
//{
//  // FIX:
//  return 0;
//}


int ParseArrayString_int8_t(int8_t* pDstArray, const int dstLength, const char*const psz)
{
  PARSE_ARRAY_STRING(ParseSubString_int8_t)
}

int ParseArrayString_int16_t(int16_t* pDstArray, const int dstLength, const char*const psz)
{
  PARSE_ARRAY_STRING(ParseSubString_int16_t)
}

int ParseArrayString_int32_t(int32_t* pDstArray, const int dstLength, const char*const psz)
{
  PARSE_ARRAY_STRING(ParseSubString_int32_t)
}

//int ParseArrayString_int64_t(int64_t* pDstArray, const int dstLength, const char*const psz)
//{
//  // FIX:
//  return 0;
//}


//int ParseArrayString_float_t(float* pValue, const char*const psz)
//{
//  // FIX:
//  return 0;
//}
//
//int ParseArrayString_double_t(double* pValue, const char*const psz)
//{
//  // FIX:
//  return 0;
//}
//
