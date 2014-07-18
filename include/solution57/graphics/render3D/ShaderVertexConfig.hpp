#ifndef DFMC_GRAPHICS_RENDER3D_SHADERVERTEXCONFIG_HPP
#define DFMC_GRAPHICS_RENDER3D_SHADERVERTEXCONFIG_HPP
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

#include <GLES2/gl2.h>

namespace dfmc
{
  struct ShaderVertexConfig
  {
    GLuint Position;
    GLuint Normal;
    GLuint TexCoord;

    ShaderVertexConfig()
      : Position(GL_INVALID_VALUE)
      , Normal(GL_INVALID_VALUE)
      , TexCoord(GL_INVALID_VALUE)
    {
    }

    ShaderVertexConfig(const GLuint position)
      : Position(position)
      , Normal(GL_INVALID_VALUE)
      , TexCoord(GL_INVALID_VALUE)
    {
    }

    ShaderVertexConfig(const GLuint position, const GLuint normal)
      : Position(position)
      , Normal(normal)
      , TexCoord(GL_INVALID_VALUE)
    {
    }

    ShaderVertexConfig(const GLuint position, const GLuint normal, const GLuint texCoord)
      : Position(position)
      , Normal(normal)
      , TexCoord(texCoord)
    {
    }

  };
}

#endif
