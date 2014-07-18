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

#include <cassert>
#include <dfmc/graphics/procedural/Util.hpp>
#include <dfmc/graphics/procedural/IndexUtil.hpp>
#include <dfmc/graphics/procedural/VertexUtil.hpp>

namespace dfmc {
namespace procedural
{
  void Util::GenerateNormals(std::vector<VertexPositionNormalTexture>& rVertices, const std::vector<int>& indices)
  {
    const int vertexCount = rVertices.size();

    for (int i = 0; i < vertexCount; i++)
      rVertices[i].Normal = Vector3(0, 0, 0);

    const int indexCount = indices.size();
    for (int i = 0; i < indexCount / 3; ++i)
    {
      int idx0 = indices[i * 3];
      int idx1 = indices[i * 3 + 1];
      int idx2 = indices[i * 3 + 2];
      Vector3 firstvec = rVertices[idx1].Position - rVertices[idx0].Position;
      Vector3 secondvec = rVertices[idx0].Position - rVertices[idx2].Position;
      Vector3 normal = Vector3::Cross(firstvec, secondvec);
      normal.Normalize();
      rVertices[idx0].Normal += normal;
      rVertices[idx1].Normal += normal;
      rVertices[idx2].Normal += normal;
    }

    for (int i = 0; i < vertexCount; i++)
      rVertices[i].Normal.Normalize();
  }

  // FIX: passing the vector as a return value is slow except in c++11 with move semantics
  const std::vector<VertexPositionColor> Util::ExtractNormalsAsLineList(const SimpleModel& model, const int len)
  {
    const int vertexCount = model.GetVertexCount();
    const VertexPositionNormalTexture* pSrcVertices = model.GetVertices();

    std::vector<VertexPositionColor> dstVertices(vertexCount*2);
    for (int i = 0; i < vertexCount; ++i)
    {
      const Vector3 pos = pSrcVertices[i].Position;
      dstVertices[i * 2 + 0].Position = pos;
      dstVertices[i * 2 + 1].Position = pos + (pSrcVertices[i].Normal * len);
    }
    return dstVertices;
  }


  const SimpleModel Util::CombineModel(const SimpleModel& m1, const SimpleModel& m2, const float x, const float y, const float z)
  {
    assert( m1.GetPrimitiveType() == m2.GetPrimitiveType() );

    const PrimitiveType::Enum primitiveType = m1.GetPrimitiveType();

    // Combine the models
    const Vector3 mod(x,y,z);
    const int vertexCount = m1.GetVertexCount() + m2.GetVertexCount();
    std::vector<VertexPositionNormalTexture> dstVertices(vertexCount);
    int dstOffset = 0;
    dstOffset += VertexUtil::Append(dstVertices, dstOffset, m1.GetVertexVector());
    dstOffset += VertexUtil::Append(dstVertices, dstOffset, m2.GetVertexVector(), mod);

    // Combine the indices
    const int indexCount = m1.GetIndexCount() + m2.GetIndexCount();
    std::vector<int> indices(indexCount);
    IndexUtil::Append(indices, 0, m1.GetIndexVector(), 0, primitiveType);
    IndexUtil::Append(indices, m1.GetIndexCount(), m2.GetIndexVector(), m1.GetVertexCount(), primitiveType);
    return SimpleModel(dstVertices, indices, primitiveType);
  }

  int Util::CalcDuplicationsThatFitWithinIndexLimit(const SimpleModel& srcModel, const int maxIndices)
  {
    return IndexUtil::CalcDuplicationsThatFitWithinIndexLimit(srcModel.GetIndexVector(), maxIndices, srcModel.GetPrimitiveType());
  }

  const SimpleModel Util::DuplicateModel(const SimpleModel& srcModel, const int instanceCount, const bool shareInstanceVertices)
  {
    assert(instanceCount > 0);

    // Combine the models
    const int vertexCount = srcModel.GetVertexCount();
    const int vertexInstanceCount = (! shareInstanceVertices ? instanceCount : 1);
    std::vector<VertexPositionNormalTexture> vertices(vertexCount * vertexInstanceCount);
    for (int i = 0; i < vertexInstanceCount; ++i)
    {
      VertexUtil::Append(vertices, (i * vertexCount), srcModel.GetVertexVector());
      //VertexUtil::Append(vertices, (i * vertexCount), srcModel.GetVertexVector(), Vector3(15.0f * i, 0, 0));
    }


    // Combine the indices
    const int instanceVertexOffset = (! shareInstanceVertices ? vertexCount : 0);
    const std::vector<int> indices = IndexUtil::Duplicate(srcModel.GetIndexVector(), instanceVertexOffset, instanceCount, srcModel.GetPrimitiveType());
    return SimpleModel(vertices, indices, srcModel.GetPrimitiveType());
  }

}}
