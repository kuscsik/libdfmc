#ifndef DFMC_GRAPHICS_RENDERVG_PATH_HPP
#define DFMC_GRAPHICS_RENDERVG_PATH_HPP
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

#include <VG/openvg.h>
#include <vector>
#include <dfmc/base/math/Vector2.hpp>
#include <dfmc/base/Noncopyable.hpp>

namespace dfmc
{
  class PathBuffer : private Noncopyable
  {
    VGPath mPath;
    std::vector<VGfloat> mVertices;
    std::vector<VGubyte> mSegments;
  public:
    PathBuffer();
    PathBuffer(const std::vector<VGfloat>& vertices, const std::vector<VGubyte>& segments);
    PathBuffer(const std::vector<Vector2>& vertices, const std::vector<VGubyte>& segments);
    ~PathBuffer();
    
    void SetContent(const std::vector<VGfloat>& vertices, const std::vector<VGubyte>& segments);
    void SetContent(const std::vector<Vector2>& vertices, const std::vector<VGubyte>& segments);
    void SetContent(const std::vector<VGfloat>& vertices, const int startVertex, const int vertexCount, const std::vector<VGubyte>& segments);
    void SetContent(const std::vector<Vector2>& vertices, const int startVertex, const int vertexCount, const std::vector<VGubyte>& segments);

    VGPath GetHandle() const; 
  };
}

#endif
