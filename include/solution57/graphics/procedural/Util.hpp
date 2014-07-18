#ifndef DFMC_GRAPHICS_PROCEDURAL_UTIL_HPP
#define DFMC_GRAPHICS_PROCEDURAL_UTIL_HPP
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

#include <vector>
#include <dfmc/base/Noncopyable.hpp>
#include <dfmc/graphics/render3D/DataTypes.hpp>
#include <dfmc/graphics/render3D/util/SimpleModel.hpp>

namespace dfmc {
namespace procedural
{
  class Util : private Noncopyable
  {
  public:
    static void GenerateNormals(std::vector<VertexPositionNormalTexture>& rVertices, const std::vector<int>& indices);

    static const std::vector<VertexPositionColor> ExtractNormalsAsLineList(const SimpleModel& model, const int len);

    static const SimpleModel CombineModel(const SimpleModel& m1, const SimpleModel& m2, const float x, const float y, const float z);

    //! Calculate how many times the model can be duplicated and still fit inside the index limit
    static int CalcDuplicationsThatFitWithinIndexLimit(const SimpleModel& srcModel, const int maxIndices);

    /// Duplicate the model the requested number of times
    static const SimpleModel DuplicateModel(const SimpleModel& srcModel, const int instanceCount, const bool shareInstanceVertices = false);

  };
}}

#endif
