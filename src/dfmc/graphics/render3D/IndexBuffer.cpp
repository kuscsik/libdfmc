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
#include <dfmc/graphics/render3D/IndexBuffer.hpp>

namespace dfmc
{

  namespace
  {
    GLuint Create(const uint16_t*const indices, const int indexCount)
    {
      GLuint id;
      const int cbIndices = sizeof(uint16_t) * indexCount;

      glGenBuffers(1, &id);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, cbIndices, indices, GL_STATIC_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      return id;
    }
  }


  IndexBuffer::IndexBuffer(const uint16_t*const indices, const int indexCount)
  {
    mId = Create(indices, indexCount);
    mIndexCount = indexCount;
    mOpenGLType = GL_UNSIGNED_SHORT;
  }


  IndexBuffer::IndexBuffer(const int*const indices, const int indexCount, const IndexFormat::Enum format)
  {
    // FIX: implement support for the other index formats
    assert(format == IndexFormat::UInt16);

    uint16_t* newIndices = new uint16_t[indexCount];
    for( int i=0; i<indexCount; ++i )
    {
      assert( indices[i] >= 0 );
      assert( indices[i] <= 0xFFFF );
      newIndices[i] = static_cast<uint16_t>(indices[i]);
    }

    mId = Create(newIndices, indexCount);
    mIndexCount = indexCount;
    mOpenGLType = GL_UNSIGNED_SHORT;
  }


  void IndexBuffer::Bind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
  }

  void IndexBuffer::Unbind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

}
