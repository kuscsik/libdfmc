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
#include <gtest/gtest.h>

TEST(ParseString, bool)
{
  int res;
  int value;

  value = 1;
  res = ParseString_bool(&value, "0");
  EXPECT_EQ(1, res);
  EXPECT_EQ(0, value);

  value = 0;
  res = ParseString_bool(&value, "1");
  EXPECT_EQ(1, res);
  EXPECT_EQ(1, value);
  
  value = 0;
  res = ParseString_bool(&value, "-1");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);

  value = 1;
  res = ParseString_bool(&value, "+1");
  EXPECT_EQ(0, res);
  EXPECT_EQ(1, value);

  value = 0;
  res = ParseString_bool(&value, "true");
  EXPECT_EQ(4, res);
  EXPECT_EQ(1, value);

  value = 1;
  res = ParseString_bool(&value, "false");
  EXPECT_EQ(5, res);
  EXPECT_EQ(0, value);

  value = 0;
  res = ParseString_bool(&value, "True");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);

  value = 1;
  res = ParseString_bool(&value, "False");
  EXPECT_EQ(0, res);
  EXPECT_EQ(1, value);

  value = 0;
  res = ParseString_bool(&value, "TRUE");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);

  value = 1;
  res = ParseString_bool(&value, "FALSE");
  EXPECT_EQ(0, res);
  EXPECT_EQ(1, value);

  // Postfix characters should not be accepted
  value = 0;
  res = ParseString_bool(&value, "trueA");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);

  value = 1;
  res = ParseString_bool(&value, "falseA");
  EXPECT_EQ(0, res);
  EXPECT_EQ(1, value);

  // Postfix characters should not be accepted
  value = 0;
  res = ParseString_bool(&value, "10");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);

  value = 1;
  res = ParseString_bool(&value, "00");
  EXPECT_EQ(0, res);
  EXPECT_EQ(1, value);

  // prefix white space characters should not be accepted
  value = 0;
  res = ParseString_bool(&value, " 1");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);

  value = 1;
  res = ParseString_bool(&value, " 0");
  EXPECT_EQ(0, res);
  EXPECT_EQ(1, value);

  value = 0;
  res = ParseString_bool(&value, " true");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);

  value = 1;
  res = ParseString_bool(&value, " false");
  EXPECT_EQ(0, res);
  EXPECT_EQ(1, value);

  // postfix white space characters should not be accepted
  value = 0;
  res = ParseString_bool(&value, "1 ");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);

  value = 1;
  res = ParseString_bool(&value, "0 ");
  EXPECT_EQ(0, res);
  EXPECT_EQ(1, value);

  value = 0;
  res = ParseString_bool(&value, "true ");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);

  value = 1;
  res = ParseString_bool(&value, "false ");
  EXPECT_EQ(0, res);
  EXPECT_EQ(1, value);
}

TEST(ParseString, uint8_t)
{
  int res;
  uint8_t value;
  value = 1;
  res = ParseString_uint8_t(&value, "0");
  EXPECT_EQ(1, res);
  EXPECT_EQ(0, value);

  value = 42;
  res = ParseString_uint8_t(&value, "-1");
  EXPECT_EQ(0, res);
  EXPECT_EQ(42, value);

  value = 0;
  res = ParseString_uint8_t(&value, "+42");
  EXPECT_TRUE(res > 0);
  EXPECT_EQ(42, value);

  value = 0;
  res = ParseString_uint8_t(&value, "255");
  EXPECT_TRUE(res > 0);
  EXPECT_EQ(255, value);

  value = 0;
  res = ParseString_uint8_t(&value, "0xFF");
  EXPECT_TRUE(res > 0);
  EXPECT_EQ(255, value);

  value = 0;
  res = ParseString_uint8_t(&value, "256");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);

  // prefix characters should not be accepted
  value = 0;
  res = ParseString_uint8_t(&value, "a2");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);

  // postfix characters should not be accepted
  value = 0;
  res = ParseString_uint8_t(&value, "2a");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);

  // prefix white space characters should not be accepted
  value = 0;
  res = ParseString_uint8_t(&value, " 2");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);

  // postfix white space characters should not be accepted
  value = 0;
  res = ParseString_uint8_t(&value, "2 ");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);
}


TEST(ParseString, uint16_t)
{
  int res;
  uint16_t value;
  value = 1;
  res = ParseString_uint16_t(&value, "0");
  EXPECT_TRUE(res > 0);
  EXPECT_EQ(0, value);

  value = 42;
  res = ParseString_uint16_t(&value, "-1");
  EXPECT_EQ(0, res);
  EXPECT_EQ(42, value);

  value = 0;
  res = ParseString_uint16_t(&value, "+42");
  EXPECT_TRUE(res > 0);
  EXPECT_EQ(42, value);

  value = 0;
  res = ParseString_uint16_t(&value, "65535");
  EXPECT_TRUE(res > 0);
  EXPECT_EQ(65535, value);

  value = 0;
  res = ParseString_uint16_t(&value, "0xFFFF");
  EXPECT_TRUE(res > 0);
  EXPECT_EQ(65535, value);

  value = 0;
  res = ParseString_uint16_t(&value, "0x10000");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);
}


TEST(ParseString, uint32_t)
{
  int res;
  uint32_t value;
  value = 1;
  res = ParseString_uint32_t(&value, "0");
  EXPECT_EQ(1, res);
  EXPECT_EQ(0, value);

  value = 42;
  res = ParseString_uint32_t(&value, "-1");
  EXPECT_EQ(0, res);
  EXPECT_EQ(42, value);

  value = 0;
  res = ParseString_uint32_t(&value, "+42");
  EXPECT_EQ(3, res);
  EXPECT_EQ(42, value);

  value = 0;                        //1234567890
  res = ParseString_uint32_t(&value, "4294967295");
  EXPECT_EQ(10, res);
  EXPECT_EQ(0xFFFFFFFF, value);

  value = 0;                        //1234567890
  res = ParseString_uint32_t(&value, "0xFFFFFFFF");
  EXPECT_EQ(10, res);
  EXPECT_EQ(0xFFFFFFFF, value);

  value = 0;                        
  res = ParseString_uint32_t(&value, "0x100000000");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);
}

//TEST(ParseString, uint64_t)
//{
//  int res;
//  uint64_t value;
//  value = 1;
//  res = ParseString_uint64_t(&value, "0");
//  EXPECT_EQ(res, 1);
//  EXPECT_EQ(value, 0);
//}

TEST(ParseString, int8_t)
{
  int res;
  int8_t value;
  value = 1;
  res = ParseString_int8_t(&value, "0");
  EXPECT_EQ(1, res);
  EXPECT_EQ(0, value);

  value = 0;
  res = ParseString_int8_t(&value, "-1");
  EXPECT_EQ(2, res);
  EXPECT_EQ(-1, value);

  value = 0;
  res = ParseString_int8_t(&value, "+42");
  EXPECT_EQ(3, res);
  EXPECT_EQ(42, value);

  value = 0;
  res = ParseString_int8_t(&value, "127");
  EXPECT_EQ(3, res);
  EXPECT_EQ(127, value);

  value = 0;
  res = ParseString_int8_t(&value, "0x7f");
  EXPECT_TRUE(res > 0);
  EXPECT_EQ(127, value);

  value = 0;
  res = ParseString_int8_t(&value, "128");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);

  value = 0;
  res = ParseString_int8_t(&value, "-128");
  EXPECT_EQ(4, res);
  EXPECT_EQ(-128, value);

  value = 0;
  res = ParseString_int8_t(&value, "-129");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);
}

TEST(ParseString, int16_t)
{
  int res;
  int16_t value;
  value = 1;
  res = ParseString_int16_t(&value, "0");
  EXPECT_EQ(1, res);
  EXPECT_EQ(0, value);

  value = 0;
  res = ParseString_int16_t(&value, "-1");
  EXPECT_EQ(2, res);
  EXPECT_EQ(-1, value);

  value = 0;
  res = ParseString_int16_t(&value, "+42");
  EXPECT_EQ(3, res);
  EXPECT_EQ(42, value);

  value = 0;
  res = ParseString_int16_t(&value, "32767");
  EXPECT_EQ(5, res);
  EXPECT_EQ(0x7fff, value);

  value = 0;
  res = ParseString_int16_t(&value, "0x7fff");
  EXPECT_EQ(6, res);
  EXPECT_EQ(0x7fff, value);

  value = 0;
  res = ParseString_int16_t(&value, "32768");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);

  value = 0;
  res = ParseString_int16_t(&value, "-32768");
  EXPECT_EQ(6, res);
  EXPECT_EQ(-32768, value);

  value = 0;
  res = ParseString_int16_t(&value, "-32769");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);
}

TEST(ParseString, int32_t)
{
  int res;
  int32_t value;
  value = 1;
  res = ParseString_int32_t(&value, "0");
  EXPECT_EQ(res, 1);
  EXPECT_EQ(value, 0);

  value = 0;
  res = ParseString_int32_t(&value, "-1");
  EXPECT_EQ(2, res);
  EXPECT_EQ(-1, value);

  value = 0;
  res = ParseString_int32_t(&value, "+42");
  EXPECT_EQ(3, res);
  EXPECT_EQ(42, value);

  value = 0;                       //1234567890
  res = ParseString_int32_t(&value, "2147483647");
  EXPECT_EQ(10, res);
  EXPECT_EQ(2147483647, value);

  value = 0;                       //1234567890
  res = ParseString_int32_t(&value, "0x7FFFFFFF");
  EXPECT_EQ(10, res);
  EXPECT_EQ(0x7fffffff, value);

  value = 0;
  res = ParseString_int32_t(&value, "2147483648");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);

  value = 0;                       //12345678901
  res = ParseString_int32_t(&value, "-2147483648");
  EXPECT_EQ(11, res);
  EXPECT_EQ(-2147483648, value);

  value = 0;
  res = ParseString_int32_t(&value, "-2147483649");
  EXPECT_EQ(0, res);
  EXPECT_EQ(0, value);
}

//TEST(ParseString, int64_t)
//{
//  int res;
//  int64_t value;
//  value = 1;
//  res = ParseString_int64_t(&value, "0");
//  EXPECT_EQ(res, 1);
//  EXPECT_EQ(value, 0);
//}


TEST(ParseString, float)
{
  int res;
  float value;
  value = 1;
  res = ParseString_float(&value, "0");
  EXPECT_EQ(res, 1);
  ASSERT_FLOAT_EQ(value, 0.0f);

  value = 0;
  res = ParseString_float(&value, "-1");
  EXPECT_EQ(2, res);
  ASSERT_FLOAT_EQ(-1.0f, value);

  value = 0;
  res = ParseString_float(&value, "+42");
  EXPECT_EQ(3, res);
  ASSERT_FLOAT_EQ(42.0f, value);

  value = 0;                       //1234567890
  res = ParseString_float(&value, "2147483647");
  EXPECT_EQ(10, res);
  ASSERT_FLOAT_EQ(2147483647.0f, value);

  value = 0;                       
  res = ParseString_float(&value, "0.5");
  EXPECT_EQ(3, res);
  ASSERT_FLOAT_EQ(0.5f, value);

  value = 0;
  res = ParseString_float(&value, "-0.5");
  EXPECT_EQ(4, res);
  ASSERT_FLOAT_EQ(-0.5f, value);


  value = 0;                     //12345678901
  res = ParseString_float(&value, "-2147483648");
  EXPECT_EQ(11, res);
  ASSERT_FLOAT_EQ(-2147483648.0f, value);
}

TEST(ParseString, double)
{
  int res;
  double value;
  value = 1;
  res = ParseString_double(&value, "0");
  EXPECT_EQ(res, 1);
  ASSERT_DOUBLE_EQ(value, 0.0f);

  value = 0;
  res = ParseString_double(&value, "-1");
  EXPECT_EQ(2, res);
  ASSERT_DOUBLE_EQ(-1.0, value);

  value = 0;
  res = ParseString_double(&value, "+42");
  EXPECT_EQ(3, res);
  ASSERT_DOUBLE_EQ(42.0, value);

  value = 0;                      //1234567890
  res = ParseString_double(&value, "2147483647");
  EXPECT_EQ(10, res);
  ASSERT_DOUBLE_EQ(2147483647.0, value);

  value = 0;                       
  res = ParseString_double(&value, "0.5");
  EXPECT_EQ(3, res);
  ASSERT_DOUBLE_EQ(0.5, value);

  value = 0;
  res = ParseString_double(&value, "-0.5");
  EXPECT_EQ(4, res);
  ASSERT_DOUBLE_EQ(-0.5, value);

  value = 0;                      //12345678901
  res = ParseString_double(&value, "-2147483648");
  EXPECT_EQ(11, res);
  ASSERT_DOUBLE_EQ(-2147483648.0, value);
}


TEST(ParseArrayString, bool)
{
  const int testArraySize = 10;
  int entries;
  int dstArray[testArraySize];
  entries = ParseArrayString_bool(dstArray, testArraySize, "[]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_bool(dstArray, testArraySize, "[");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_bool(dstArray, testArraySize, "]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_bool(dstArray, testArraySize, "");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_bool(dstArray, testArraySize, "[,]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_bool(dstArray, testArraySize, "[0,]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_bool(dstArray, testArraySize, "[true,]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_bool(dstArray, testArraySize, "[,true]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_bool(dstArray, testArraySize, "[true,true");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_bool(dstArray, testArraySize, "[true ]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_bool(dstArray, testArraySize, "[1 ]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_bool(dstArray, testArraySize, "[ 1]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_bool(dstArray, testArraySize, "[0, true, 0, 1, false]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_bool(dstArray, testArraySize, "[true]");
  EXPECT_EQ(1, entries);

  entries = ParseArrayString_bool(dstArray, testArraySize, "[false]");
  EXPECT_EQ(1, entries);

  entries = ParseArrayString_bool(dstArray, testArraySize, "[0,true,0,1,false]");
  EXPECT_EQ(5, entries);
}

TEST(ParseArrayString, uint8_t)
{
  const int testArraySize = 10;
  int entries;
  uint8_t dstArray[testArraySize];
  entries = ParseArrayString_uint8_t(dstArray, testArraySize, "[]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint8_t(dstArray, testArraySize, "[");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint8_t(dstArray, testArraySize, "]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint8_t(dstArray, testArraySize, "");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint8_t(dstArray, testArraySize, "[,]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint8_t(dstArray, testArraySize, "[0,]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint8_t(dstArray, testArraySize, "[1,]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint8_t(dstArray, testArraySize, "[,1]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint8_t(dstArray, testArraySize, "[1,1");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint8_t(dstArray, testArraySize, "[1 ]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint8_t(dstArray, testArraySize, "[1 ]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint8_t(dstArray, testArraySize, "[ 1]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint8_t(dstArray, testArraySize, "[0, 127, 0, 1, 127]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint8_t(dstArray, testArraySize, "[1]");
  EXPECT_EQ(1, entries);

  entries = ParseArrayString_uint8_t(dstArray, testArraySize, "[0]");
  EXPECT_EQ(1, entries);

  entries = ParseArrayString_uint8_t(dstArray, testArraySize, "[0,6,0,127,1]");
  EXPECT_EQ(5, entries);
}

TEST(ParseArrayString, uint32_t)
{
  const int testArraySize = 10;
  int entries;
  uint32_t dstArray[testArraySize];
  entries = ParseArrayString_uint32_t(dstArray, testArraySize, "[]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint32_t(dstArray, testArraySize, "[");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint32_t(dstArray, testArraySize, "]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint32_t(dstArray, testArraySize, "");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint32_t(dstArray, testArraySize, "[,]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint32_t(dstArray, testArraySize, "[0,]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint32_t(dstArray, testArraySize, "[1,]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint32_t(dstArray, testArraySize, "[,1]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint32_t(dstArray, testArraySize, "[1,1");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint32_t(dstArray, testArraySize, "[1 ]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint32_t(dstArray, testArraySize, "[1 ]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint32_t(dstArray, testArraySize, "[ 1]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint32_t(dstArray, testArraySize, "[0, 127, 0, 1, 127]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_uint32_t(dstArray, testArraySize, "[1]");
  EXPECT_EQ(1, entries);

  entries = ParseArrayString_uint32_t(dstArray, testArraySize, "[0]");
  EXPECT_EQ(1, entries);

  entries = ParseArrayString_uint32_t(dstArray, testArraySize, "[0,6,0,127,1]");
  EXPECT_EQ(5, entries);
}



TEST(ParseArrayString, int32_t)
{
  const int testArraySize = 10;
  int entries;
  int32_t dstArray[testArraySize];
  entries = ParseArrayString_int32_t(dstArray, testArraySize, "[]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_int32_t(dstArray, testArraySize, "[");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_int32_t(dstArray, testArraySize, "]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_int32_t(dstArray, testArraySize, "");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_int32_t(dstArray, testArraySize, "[,]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_int32_t(dstArray, testArraySize, "[0,]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_int32_t(dstArray, testArraySize, "[1,]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_int32_t(dstArray, testArraySize, "[,1]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_int32_t(dstArray, testArraySize, "[1,1");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_int32_t(dstArray, testArraySize, "[1 ]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_int32_t(dstArray, testArraySize, "[1 ]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_int32_t(dstArray, testArraySize, "[ 1]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_int32_t(dstArray, testArraySize, "[0, 127, 0, 1, 127]");
  EXPECT_TRUE(entries < 0);

  entries = ParseArrayString_int32_t(dstArray, testArraySize, "[1]");
  EXPECT_EQ(1, entries);

  entries = ParseArrayString_int32_t(dstArray, testArraySize, "[0]");
  EXPECT_EQ(1, entries);

  entries = ParseArrayString_int32_t(dstArray, testArraySize, "[0,-6,0,127,-188]");
  EXPECT_EQ(5, entries);
}
