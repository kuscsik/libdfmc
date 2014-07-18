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
#include <dfmc/graphics/procedural/VertexUtil.hpp>

namespace dfmc {
namespace procedural
{
  namespace
  {
    void EnsureCapacity(std::vector<VertexPositionNormalTexture>& rDst, const int minimumCapacity)
    {
      // Ensure that the array has enough capacity for the appended indices
      if( minimumCapacity > static_cast<int>(rDst.size()) )
        rDst.resize(minimumCapacity + 256);
    }
  }


  int VertexUtil::Append(std::vector<VertexPositionNormalTexture>& rDst, const int dstIndex, const std::vector<VertexPositionNormalTexture>& src)
  {
    const int vertexCount = src.size();
    EnsureCapacity(rDst, dstIndex + vertexCount);

    for (int i = 0; i < vertexCount; ++i)
    {
      rDst[dstIndex + i] = src[i];
    }
    return vertexCount;
  }

  int VertexUtil::Append(std::vector<VertexPositionNormalTexture>& rDst, const int dstIndex, const std::vector<VertexPositionNormalTexture>& src, const Vector3& modVector)
  {
    const int vertexCount = src.size();
    EnsureCapacity(rDst, dstIndex + vertexCount);

    for (int i = 0; i < vertexCount; ++i)
    {
      VertexPositionNormalTexture val = src[i];

      val.Position += modVector;

      rDst[dstIndex + i] = val;
    }
    return vertexCount;
  }

}}
