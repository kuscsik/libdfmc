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

#include <dfmc/graphics/renderVG/PathBuffer.hpp>
#include <cassert>

namespace dfmc
{

  namespace
  {
    VGPath CreatePath(const std::vector<VGfloat>& vertices, const std::vector<VGubyte>& segments)
    {
      VGPath hPath = vgCreatePath(VG_PATH_FORMAT_STANDARD,
        VG_PATH_DATATYPE_F,
        1.0f, // scale
        0.0f, // bias
        segments.size(), // segmentCapacityHint
        vertices.size(),   // coordCapacityHint
        VG_PATH_CAPABILITY_ALL);

      vgAppendPathData(hPath, segments.size(), &segments[0], &vertices[0]);
      return hPath;
    }
  }


  PathBuffer::PathBuffer()
    : mPath(VG_INVALID_HANDLE)
    , mVertices()
    , mSegments()
  {
  }


  PathBuffer::PathBuffer(const std::vector<VGfloat>& vertices, const std::vector<VGubyte>& segments)
    : mPath(VG_INVALID_HANDLE)
    , mVertices(vertices)
    , mSegments(segments)
  {
    mPath = CreatePath(mVertices, mSegments);
  }


  PathBuffer::PathBuffer(const std::vector<Vector2>& vertices, const std::vector<VGubyte>& segments)
    : mPath(VG_INVALID_HANDLE)
    , mVertices()
    , mSegments()
  {
    SetContent(vertices, segments);
  }

  
  PathBuffer::~PathBuffer()
  {
    if( mPath != VG_INVALID_HANDLE )
      vgDestroyPath(mPath);
  }

  void PathBuffer::SetContent(const std::vector<VGfloat>& vertices, const std::vector<VGubyte>& segments)
  {
    SetContent(vertices, 0, vertices.size(), segments);
  }

  void PathBuffer::SetContent(const std::vector<Vector2>& vertices, const std::vector<VGubyte>& segments)
  {
    SetContent(vertices, 0, vertices.size(), segments);
  }

  void PathBuffer::SetContent(const std::vector<VGfloat>& vertices, const int startVertex, const int vertexCount, const std::vector<VGubyte>& segments)
  {
    assert( startVertex >= 0 );
    assert( vertexCount >= 0 );
    assert( (startVertex+vertexCount) <= static_cast<int>(vertices.size()) );

    if( mPath != VG_INVALID_HANDLE )
    {
      vgDestroyPath(mPath);
      mPath = VG_INVALID_HANDLE;
    }

    mVertices.resize(vertexCount);
    std::copy(vertices.begin() + startVertex,  vertices.begin() + (startVertex + vertexCount), mVertices.begin());

    mSegments = segments;

    mPath = CreatePath(mVertices, mSegments);
  }


  void PathBuffer::SetContent(const std::vector<Vector2>& vertices, const int startVertex, const int vertexCount, const std::vector<VGubyte>& segments)
  {
    assert( startVertex >= 0 );
    assert( vertexCount >= 0 );
    assert( (startVertex+vertexCount) <= static_cast<int>(vertices.size()) );

    if( mPath != VG_INVALID_HANDLE )
    {
      vgDestroyPath(mPath);
      mPath = VG_INVALID_HANDLE;
    }

    mVertices.resize(vertexCount * 2);
    int dstIdx = 0;
    for( int i=0; i<vertexCount; ++i )
    {
      mVertices[dstIdx+0] = vertices[startVertex+i].X;
      mVertices[dstIdx+1] = vertices[startVertex+i].Y;
      dstIdx += 2;
    }

    mSegments = segments;

    mPath = CreatePath(mVertices, mSegments);
  }


  VGPath PathBuffer::GetHandle() const
  {
    return mPath;
  }

}
