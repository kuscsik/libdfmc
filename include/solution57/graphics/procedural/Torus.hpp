#ifndef DFMC_GRAPHICS_PROCEDURAL_TORUS_HPP
#define DFMC_GRAPHICS_PROCEDURAL_TORUS_HPP
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

#include <dfmc/graphics/render3D/util/SimpleModel.hpp>

namespace dfmc {
namespace procedural
{
  class Torus
  {
  public:
    static SimpleModel Generate(const int sides, const int rings, const float radius, const float ringRadius, const bool bInsideOut);
  };

}}

#endif
