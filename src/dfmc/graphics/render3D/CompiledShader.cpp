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

#include <dfmc/graphics/render3D/CompiledShader.hpp>
#include <dfmc/base/Exceptions.hpp>
#include <dfmc/base/log/Log.hpp>
#include <vector>

namespace dfmc
{
  CompiledShader::CompiledShader(const GLint shaderType)
    : mhShader(0)
    , mShaderType(shaderType)
  {
    // Create a new shader in GL
    mhShader = glCreateShader(shaderType);
    GLenum glError = glGetError();
    if (mhShader == 0 || glError != GL_NO_ERROR)
      throw OpenGLException("Failed to create shader", glError);
  }


  CompiledShader::~CompiledShader()
  {
    if (mhShader != 0)
      glDeleteShader(mhShader);
  }


  GLuint CompiledShader::GetShaderHandle() const
  {
    return mhShader;
  }


  GLint CompiledShader::GetShaderType() const
  {
    return mShaderType;
  }
}

