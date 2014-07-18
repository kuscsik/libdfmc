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
#include <dfmc/graphics/render3D/shaders/WhiteShader.hpp>
#include "../gl/GLCheck.hpp"

namespace dfmc
{
  namespace 
  {
#ifndef FIXED_SHADERS
    const char*const gpszVert = "res/White.vert";
    const char*const gpszFrag = "res/White.frag";
    const bool gIsFiles = true;
#else
    const char*const gpszVert = "attribute vec4 VertexPosition;\nuniform mat4 mvp;\nvoid main()\n{\ngl_Position = mvp * VertexPosition;\n}\n";
    const char*const gpszFrag = "precision lowp float;\nvoid main()\n{\ngl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n}\n";
    const bool gIsFiles = false;
#endif
  }

  WhiteShader::WhiteShader()
    : ShaderBase(gpszVert, gpszFrag, gIsFiles)
    , mLocWVP(GL_INVALID_VALUE)
  {
    const GLuint programId = GetProgramId();

    // Get attribute locations of non-fixed attributes like color and texture coordinates. 
    mShaderVertexConfig.Position = GL_CHECKERR(glGetAttribLocation(programId, "VertexPosition"));
    mLocWVP = GL_CHECKERR(glGetUniformLocation(programId, "mvp"));
  }


  void WhiteShader::SetWorldViewProjection(const Matrix& matrix)
  {
    assert( IsLoaded() );
    GL_CHECKERR(glUniformMatrix4fv(mLocWVP, 1, GL_FALSE, matrix.GetRaw()));
  }
}
