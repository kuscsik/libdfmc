#ifndef DFMC_GRAPHICS_PROCEDURAL_MODELBUILDER_HPP
#define DFMC_GRAPHICS_PROCEDURAL_MODELBUILDER_HPP
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
#include <dfmc/graphics/render3D/DataTypes.hpp>
#include <dfmc/graphics/render3D/util/SimpleModel.hpp>

namespace dfmc {
namespace procedural
{

  //! Use this when you want to combine multiple simple models.
  //  Its generally faster than using the Util class.
  class ModelBuilder
  {
    std::vector<VertexPositionNormalTexture> mVertices;
    std::vector<int> mIndices;

    PrimitiveType::Enum mPrimitiveType;

    int mVertexCount;
    int mIndexCount;

  public:
    ModelBuilder(const PrimitiveType::Enum primitiveType);
    ModelBuilder(const PrimitiveType::Enum primitiveType, const int vertexCapacity, const int indexCapacity);

    void Clear();
    void Append(const SimpleModel& model);
    void Append(const SimpleModel& model, const Vector3& positionMod);
    void Append(const SimpleModel& model, const float xMod, const float yMod, const float zMod);

    int GetVertexCount() const;
    int GetIndexCount() const;

    const SimpleModel GetModel() const;
  private:
  };

}}

#endif
