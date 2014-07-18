#ifndef DFMC_GRAPHICS_RENDER3D_UTIL_SIMPLEMODEL_HPP
#define DFMC_GRAPHICS_RENDER3D_UTIL_SIMPLEMODEL_HPP
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

namespace dfmc
{
  class SimpleModel
  {
  private:
    std::vector<VertexPositionNormalTexture> mVertices;
    std::vector<int> mIndices;

    PrimitiveType::Enum mPrimitiveType;
    int mPrimitiveCount;

  public:
    SimpleModel();
    SimpleModel(const PrimitiveType::Enum primitiveType);
    SimpleModel(const std::vector<VertexPositionNormalTexture>& vertices, const std::vector<int>& indices, const PrimitiveType::Enum primitiveType);
    SimpleModel(const std::vector<VertexPositionNormalTexture>& vertices, const int vertexStartOffset, const int vertexCount, 
                const std::vector<int>& indices, const int indexStartOffset, const int indexCount, 
                const PrimitiveType::Enum primitiveType);
    int GetVertexCount() const;
    int GetIndexCount() const;
    int GetPrimitiveCount() const;
    PrimitiveType::Enum GetPrimitiveType() const;
    const VertexPositionNormalTexture* GetVertices() const;
    const int* GetIndices() const;
    const std::vector<VertexPositionNormalTexture>& GetVertexVector() const;
    const std::vector<int>& GetIndexVector() const;
  };
}

#endif
