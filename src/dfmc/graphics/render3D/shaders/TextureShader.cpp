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
#include <dfmc/graphics/render3D/shaders/TextureShader.hpp>
#include "../gl/GLCheck.hpp"

namespace dfmc
{
  namespace 
  {
#ifndef FIXED_SHADERS
    const char*const gpszVert = "res/Texture.vert";
    const char*const gpszFrag = "res/Texture.frag";
    const bool gIsFiles = true;
#else
    const char*const gpszVert = "attribute vec4 VertexPosition;attribute vec2 VertexTexCoord;uniform mat4 mvp;varying mediump vec2 v_texcoord;void main() {  gl_Position = mvp * VertexPosition;  v_texcoord = VertexTexCoord;}\n";
    const char*const gpszFrag = "precision lowp float;varying mediump vec2 v_texcoord;uniform sampler2D texture;void main() {	gl_FragColor =  texture2D(texture, v_texcoord);}\n";
    const bool gIsFiles = false;
#endif
  }


  TextureShader::TextureShader()
    : ShaderBase(gpszVert, gpszFrag, gIsFiles)
    , mLocWVP(GL_INVALID_VALUE)
    , mLocTexture(GL_INVALID_VALUE)
  {
    const GLuint programId = GetProgramId();

    // Get attribute locations of non-fixed attributes like color and texture coordinates. 
    mShaderVertexConfig.Position = GL_CHECKERR(glGetAttribLocation(programId, "VertexPosition"));
    mShaderVertexConfig.TexCoord = GL_CHECKERR(glGetAttribLocation(programId, "VertexTexCoord"));

    // Get uniform locations
    mLocWVP = GL_CHECKERR(glGetUniformLocation(programId, "mvp"));
    mLocTexture = GL_CHECKERR(glGetUniformLocation(programId, "texture"));
  }

  void TextureShader::SetWorldViewProjection(const Matrix& matrix)
  {
    assert( IsLoaded() );
    GL_CHECKERR(glUniformMatrix4fv(mLocWVP, 1, GL_FALSE, matrix.GetRaw()));
  }

  void TextureShader::SetTexture(const int unit)
  {
    assert( IsLoaded() );
    GL_CHECKERR(glUniform1i(mLocTexture, unit));
  }




}
