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
#include <stddef.h>
#include <dfmc/graphics/render3D/VertexBuffer.hpp>

namespace dfmc
{


  VertexBuffer::VertexBuffer(const VertexPositionNormalTexture*const vertices, const int vertexCount)
  {
    const int cbVertices = sizeof(VertexPositionNormalTexture) * vertexCount;

    glGenBuffers(1, &mId);
    glBindBuffer(GL_ARRAY_BUFFER, mId);
    glBufferData(GL_ARRAY_BUFFER, cbVertices, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }


  void VertexBuffer::Bind(const ShaderVertexConfig& shaderConfig)
  {
     glBindBuffer(GL_ARRAY_BUFFER, mId);

    if( shaderConfig.Position != GL_INVALID_VALUE )
    {
      glVertexAttribPointer(shaderConfig.Position, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormalTexture), (void*)offsetof(VertexPositionNormalTexture,Position));
      glEnableVertexAttribArray(shaderConfig.Position);
    }
    if( shaderConfig.Normal != GL_INVALID_VALUE )
    {
      glVertexAttribPointer(shaderConfig.Normal, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormalTexture), (void*)offsetof(VertexPositionNormalTexture,Normal));
      glEnableVertexAttribArray(shaderConfig.Normal);
    }

    if( shaderConfig.TexCoord != GL_INVALID_VALUE )
    {
      glVertexAttribPointer(shaderConfig.TexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormalTexture), (void*)offsetof(VertexPositionNormalTexture,TextureCoordinate));
      glEnableVertexAttribArray(shaderConfig.TexCoord);
    }
  }

  void VertexBuffer::Unbind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }



}
