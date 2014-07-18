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
#include <dfmc/graphics/procedural/ModelBuilder.hpp>
#include <dfmc/graphics/procedural/VertexUtil.hpp>
#include <dfmc/graphics/procedural/IndexUtil.hpp>

namespace dfmc {
namespace procedural
{

  ModelBuilder::ModelBuilder(const PrimitiveType::Enum primitiveType)
    : mVertices()
    , mIndices()
    , mPrimitiveType(primitiveType)
    , mVertexCount(0)
    , mIndexCount(0)
  {
  }

  ModelBuilder::ModelBuilder(const PrimitiveType::Enum primitiveType, const int vertexCapacity, const int indexCapacity)
    : mVertices(vertexCapacity)
    , mIndices(indexCapacity)
    , mPrimitiveType(primitiveType)
    , mVertexCount(0)
    , mIndexCount(0)
  {
  }

  void ModelBuilder::Clear()
  {
    //mIndices.clear();
    //mVertices.clear();
    mVertexCount = 0;
    mIndexCount = 0;
  }


  void ModelBuilder::Append(const SimpleModel& model)
  {
    Append(model, Vector3::Zero());
  }


  void ModelBuilder::Append(const SimpleModel& model, const Vector3& positionMod)
  {
    assert(model.GetPrimitiveType() == mPrimitiveType);

    mIndexCount += IndexUtil::Append(mIndices, mIndexCount, model.GetIndexVector(), mVertexCount, model.GetPrimitiveType());
    mVertexCount += VertexUtil::Append(mVertices, mVertexCount, model.GetVertexVector(), positionMod);
  }


  void ModelBuilder::Append(const SimpleModel& model, const float xMod, const float yMod, const float zMod)
  {
    Append(model, Vector3(xMod, yMod, zMod));
  }


  int ModelBuilder::GetVertexCount() const
  {
    return mVertexCount;
  }


  int ModelBuilder::GetIndexCount() const
  {
    return mIndexCount;
  }

  
  const SimpleModel ModelBuilder::GetModel() const
  {
    return SimpleModel(mVertices, 0, mVertexCount, mIndices, 0, mIndexCount, mPrimitiveType);
  }

}}
