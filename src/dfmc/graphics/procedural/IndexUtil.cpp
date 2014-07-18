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
#include <dfmc/graphics/procedural/IndexUtil.hpp>

namespace dfmc {
namespace procedural
{
  namespace 
  {
    void EnsureCapacity(std::vector<int>& rDst, const int minimumCapacity)
    {
      // Ensure that the array has enough capacity for the appended indices
      if( minimumCapacity > static_cast<int>(rDst.size()) )
        rDst.resize(minimumCapacity + 256);
    }
  }


  int IndexUtil::Append(std::vector<int>& rDst, const int dstIndex, const std::vector<int>& srcIndices, const int startVertex, const PrimitiveType::Enum primitiveType)
  {
    assert(dstIndex >= 0);
    assert(dstIndex <= static_cast<int>(rDst.size()));

    switch (primitiveType)
    {
    case PrimitiveType::LineList:
    case PrimitiveType::TriangleList:
      return AppendListIndices(rDst, dstIndex, srcIndices, startVertex);
    case PrimitiveType::TriangleStrip:
      return AppendTriangleStripIndices(rDst, dstIndex, srcIndices, startVertex);
    case PrimitiveType::LineStrip:
    default:
      // Unsupported primitive type
      assert(false);
      return 0;
    }
  }


  int IndexUtil::AppendListIndices(std::vector<int>& rDst, const int dstIndex, const std::vector<int>& srcIndices, const int startVertex)
  {
    assert(dstIndex >= 0);
    assert(dstIndex <= static_cast<int>(rDst.size()));

    const int srcCount = srcIndices.size();
    // Ensure that the array has enough capacity for the appended indices
    EnsureCapacity(rDst, dstIndex + srcCount);

    assert((dstIndex + srcCount) <= static_cast<int>(rDst.size()));

    for (int i = 0; i < srcCount; ++i)
    {
      rDst[dstIndex + i] = startVertex + srcIndices[i];
    }
    return srcCount;
  }


  int IndexUtil::AppendTriangleStripIndices(std::vector<int>& rDst, const int dstIndex, const std::vector<int>& srcIndices, const int startVertex)
  {
    assert(dstIndex >= 0);
    assert(dstIndex <= static_cast<int>(rDst.size()));

    // FIX: this does not work for odd length triangle strips (those that start and end with triangles that face the same way)
    assert( (srcIndices.size() & 1) == 0);
    // FIX: this does not work for odd length triangle strips (those that start and end with triangles that face the same way)
    assert( (dstIndex & 1) == 0);

    // CW
    //             A  |B  |C* |D* |E* |F* |G  |H  
    //             ---|---|---|---|---|---|---|---
    // 0-1    4-5  0  |0-1|1  |1  |1  |4  |4  |4-5   
    // |\| -> |\|  |\ | \|||  | \ | \ ||  ||\ | \|
    // 2-3    6-7  2-3|  3|3  |  6|  6|6  |6-7|  7 
    //                |   |   |   |   |   |   |   
    //                |   |   |   |   |   |   |   
    //                |   |   |   |   |   |   |   
    //                |   |   |   |   |   |   |   
    // - Instance #1  A: 2,0,3 cw|B: 0,3,1 ccw         
    // - Degenerated  C: 3,1,1 cw|D: 1,1,6 ccw|E: 1,6,6 CW|F: 6,6,4 CCW  (always four)
    // - Instance #2  G: 6,4,7 cw|H: 4,7,5 ccw

    // CCW
    //             A  |B  |C* |D* |E* |F* |G  |H  
    //             ---|---|---|---|---|---|---|---
    // 0-1    4-5  0 1|  1|1  |  4|  4|4  |4-5|  5   
    // |/| -> |/|  |/ | /|||  | / | / ||  ||/ | /|
    // 2-3    6-7  2  |2-3|3  |3  |3  |6  |6  |6-7 
    //                |   |   |   |   |   |   |   
    //                |   |   |   |   |   |   |   
    //                |   |   |   |   |   |   |   
    //                |   |   |   |   |   |   |   
    // - Instance #1  A: 0,2,1 ccw|B: 2,1,3 cw         
    // - Degenerated  C: 1,3,3 ccw|D: 3,3,4 cw|E: 3,4,4 CCW|F: 4,4,6 CW  (always four)
    // - Instance #2  G: 4,6,5 ccw|H: 6,5,7 cw

    const int srcCount = srcIndices.size();
    // Ensure that the array has enough capacity for the appended indices
    EnsureCapacity(rDst, dstIndex + srcCount + 4);

    int dstIndexAdd = 0;
    if( dstIndex > 0 )
    {
      // Stitch the triangle strips with degenerated triangles
      // Optimization for later: Check it its necessary :)
      rDst[dstIndex + 0] = rDst[dstIndex - 1];
      rDst[dstIndex + 1] = startVertex + srcIndices[0];
      rDst[dstIndex + 2] = startVertex + srcIndices[0];
      rDst[dstIndex + 3] = startVertex + srcIndices[1];
      dstIndexAdd += 4;
    }
    AppendListIndices(rDst, dstIndex + dstIndexAdd, srcIndices, startVertex);
    return srcCount + dstIndexAdd;
  }


  const std::vector<int> IndexUtil::Duplicate(const std::vector<int>& srcIndices, const int vertexCount, const int instanceCount, const PrimitiveType::Enum primitiveType)
  {
    switch (primitiveType)
    {
    case PrimitiveType::LineList:
    case PrimitiveType::TriangleList:
      return DuplicateListIndices(srcIndices, vertexCount, instanceCount);
    case PrimitiveType::TriangleStrip:
      return DuplicateTriangleStripIndices(srcIndices, vertexCount, instanceCount);
    case PrimitiveType::LineStrip:
    default:
      //throw std::exception("Unsupported primitive type");
      return std::vector<int>();
    }
  }

  int IndexUtil::CalcDuplicationsThatFitWithinIndexLimit(const std::vector<int>& srcIndices, const int maxIndices, const PrimitiveType::Enum primitiveType)
  {
    assert(maxIndices >= 0);
    switch( primitiveType )
    {
    case PrimitiveType::LineList:
    case PrimitiveType::TriangleList:
      return maxIndices / srcIndices.size();
    case PrimitiveType::TriangleStrip:
      // maxIndices = indices * numInstances + ((numInstances-1) * 4) // FIX: update this when we fix stitching to work with all kinds of strips
      // numInstances = (maxIndices + 4) / (indices + 4)
      return (maxIndices + 4) / (srcIndices.size() + 4);
    case PrimitiveType::LineStrip:
    default:
      // Not implemented for the given primitive type
      assert(false);
      return 0;
    }
  }


  const std::vector<int> IndexUtil::DuplicateListIndices(const std::vector<int>& srcIndices, const int vertexCount, const int instanceCount)
  {
    const int indexCount = srcIndices.size();
    std::vector<int> indices(indexCount * instanceCount);
    for (int i = 0; i < instanceCount; ++i)
    {
      AppendListIndices(indices, i * indexCount, srcIndices, i * vertexCount);
    }
    return indices;
  }


  const std::vector<int> IndexUtil::DuplicateTriangleStripIndices(const std::vector<int>& srcIndices, const int vertexCount, const int instanceCount)
  {
    const int indexCount = srcIndices.size();
    std::vector<int> dstIndices((indexCount * instanceCount) + (4 * (instanceCount-1)));
    int dstStartIndex = 0;
    int vertexOffset = 0;
    for (int i = 0; i < instanceCount; ++i)
    {
      dstStartIndex += AppendTriangleStripIndices(dstIndices, dstStartIndex, srcIndices, vertexOffset);
      vertexOffset += vertexCount;
    }
    // Ensure that the array is the minimum required size
    if( dstStartIndex < static_cast<int>(dstIndices.size()) )
      dstIndices.resize(dstStartIndex);
    return dstIndices;
  }

}}
