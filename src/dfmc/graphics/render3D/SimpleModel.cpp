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

#include <dfmc/graphics/render3D/util/SimpleModel.hpp>
#include <cassert>
#include <algorithm>

namespace dfmc
{
  namespace 
  {
    int CalcPrimitiveCount(const int numIndices, const PrimitiveType::Enum primitiveType)
    {
      switch (primitiveType)
      {
      case PrimitiveType::LineList:
        return numIndices / 2;
        break;
      case PrimitiveType::LineStrip:
        return numIndices - 1;
        break;
      case PrimitiveType::TriangleList:
        return numIndices / 3;
      case PrimitiveType::TriangleStrip:
        return numIndices - 2;
      default:
        return 0;
      }
    }
  }


  SimpleModel::SimpleModel()
    : mVertices()
    , mIndices()
    , mPrimitiveType(PrimitiveType::TriangleList)
    , mPrimitiveCount(0)
  {
  }


  SimpleModel::SimpleModel(const PrimitiveType::Enum primitiveType)
    : mVertices()
    , mIndices()
    , mPrimitiveType(primitiveType)
    , mPrimitiveCount(0)
  {
  }


  SimpleModel::SimpleModel(const std::vector<VertexPositionNormalTexture>& vertices, const std::vector<int>& indices, const PrimitiveType::Enum primitiveType)
    : mVertices(vertices)
    , mIndices(indices)
    , mPrimitiveType(primitiveType)
    , mPrimitiveCount(CalcPrimitiveCount(indices.size(), primitiveType))
  {
  }


  SimpleModel::SimpleModel(const std::vector<VertexPositionNormalTexture>& vertices, const int vertexStartOffset, const int vertexCount, 
                           const std::vector<int>& indices, const int indexStartOffset, const int indexCount, 
                           const PrimitiveType::Enum primitiveType)
    : mVertices(vertexCount)
    , mIndices(indexCount)
    , mPrimitiveType(primitiveType)
    , mPrimitiveCount(CalcPrimitiveCount(indexCount, primitiveType))
  {
    assert(vertexStartOffset >= 0);
    assert(vertexCount >= 0);
    assert((vertexStartOffset + vertexCount) <= static_cast<int>(vertices.size()));
    assert(indexStartOffset >= 0);
    assert(indexCount >= 0);
    assert((indexStartOffset + indexCount) <= static_cast<int>(indices.size()));

    std::copy(vertices.begin() + vertexStartOffset,  vertices.begin() + (vertexStartOffset + vertexCount), mVertices.begin());
    std::copy(indices.begin() + indexStartOffset,  indices.begin() + (indexStartOffset + indexCount), mIndices.begin());
  }


  int SimpleModel::GetVertexCount() const
  { 
    return mVertices.size();
  }


  int SimpleModel::GetIndexCount() const
  { 
    return mIndices.size();
  }


  int SimpleModel::GetPrimitiveCount() const
  { 
    return mPrimitiveCount;
  }


  PrimitiveType::Enum SimpleModel::GetPrimitiveType() const
  { 
    return mPrimitiveType;
  }


  const VertexPositionNormalTexture* SimpleModel::GetVertices() const
  {
    return &mVertices[0];
  }


  const int* SimpleModel::GetIndices() const
  {
    return &mIndices[0];
  }


  const std::vector<VertexPositionNormalTexture>& SimpleModel::GetVertexVector() const 
  { 
    return mVertices; 
  }


  const std::vector<int>& SimpleModel::GetIndexVector() const 
  { 
    return mIndices; 
  }

}
