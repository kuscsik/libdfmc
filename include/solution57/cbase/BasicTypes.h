#ifndef DFMC_CBASE_BASICTYPES_H
#define DFMC_CBASE_BASICTYPES_H
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

// C99 Headers - Hopefully must compilers have them these days
#include <stdint.h>

// Naive type definitions - FIX: so it matches a given platform
//typedef unsigned char uint8_t;
//typedef signed char int8_t;
//typedef unsigned short uint16_t;
//typedef signed short int16_t;
//typedef unsigned int uint32_t;
//typedef signed int int32_t;
//typedef unsigned long long uint64_t;
//typedef signed long long int64_t;

//#ifdef DFMC_COMPILER_C99_BOOL_H
//# include <stdbool.h>
//#elif !defined(__cplusplus)
//// Fallback 'C' bool type
//# define false (0)
//# define true (!0)
//  typedef int bool;
//#endif

#endif