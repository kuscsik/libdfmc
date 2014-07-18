#ifndef DFMC_GRAPHICS_PROCEDURAL_INDEXUTIL_HPP
#define DFMC_GRAPHICS_PROCEDURAL_INDEXUTIL_HPP
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

namespace dfmc {
namespace procedural
{
  class IndexUtil : private Noncopyable
  {
  public:
    static int Append(std::vector<int>& rDst, const int dstIndex, const std::vector<int>& srcIndices, const int startVertex, const PrimitiveType::Enum primitiveType);
    static int AppendListIndices(std::vector<int>& rDst, const int dstIndex, const std::vector<int>& srcIndices, const int startVertex);
    static int AppendTriangleStripIndices(std::vector<int>& rDst, const int dstIndex, const std::vector<int>& srcIndices, const int startVertex);

    //! Calculate how many times the indices can be duplicated and still fit inside the index limit (taking into account stitching if needed)
    static int CalcDuplicationsThatFitWithinIndexLimit(const std::vector<int>& srcIndices, const int maxIndices, const PrimitiveType::Enum primitiveType);

    static const std::vector<int> Duplicate(const std::vector<int>& srcIndices, const int vertexCount, const int instanceCount, const PrimitiveType::Enum primitiveType);
    static const std::vector<int> DuplicateListIndices(const std::vector<int>& srcIndices, const int vertexCount, const int instanceCount);
    static const std::vector<int> DuplicateTriangleStripIndices(const std::vector<int>& srcIndices, const int vertexCount, const int instanceCount);
  };

}}

#endif
