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

#include <dfmc/graphics/render3D/ShaderCompiler.hpp>
#include <dfmc/base/BasicTypes.hpp>
#include <dfmc/base/log/Log.hpp>
#include <dfmc/base/Exceptions.hpp>
#include "gl/GLCheck.hpp"
#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>

namespace dfmc
{

  ShaderCompiler::ShaderCompiler(const bool bVerbose)
    : mbVerbose(bVerbose)
  {

  }

  const CompiledShaderPtr ShaderCompiler::Compile(const char*const pszShader, const GLint shaderType)
  {
    const char* shaderCode[1] = { pszShader };

    CompiledShaderPtr compiledShader(new CompiledShader(shaderType));

    GL_CHECKERR(glShaderSource(compiledShader->GetShaderHandle(), 1, shaderCode, nullptr));
    shaderCode[0] = nullptr;

    // Lets compile the shader
    GL_CHECKERR(glCompileShader(compiledShader->GetShaderHandle()));

    GLint status;
    GL_CHECKERR(glGetShaderiv(compiledShader->GetShaderHandle(), GL_COMPILE_STATUS, &status));

    // Dump debug info (source and log) if compilation failed.
    if (status != GL_TRUE && mbVerbose)
      DumpDebugInfo(compiledShader->GetShaderHandle());
    return compiledShader;
  }


  void ShaderCompiler::DumpDebugInfo(const GLuint shaderId)
  {
    // We utilize GL_LOGERR here since we can safely just exit this method when a error occurs

    // Get shader source.
    GLint length;
    GL_LOGERR(glGetShaderiv(shaderId, GL_SHADER_SOURCE_LENGTH, &length));
    std::vector<GLchar> source(length);
    GL_LOGERR(glGetShaderSource(shaderId, source.size(), NULL, &source[0]));

    DFMCLOG_LINE("Debug source START:\n" << &source[0] << "\nDebug source END\n\n");

    // Fetch the log
    GL_LOGERR(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length));
    std::vector<GLchar> errorLog(length);
    GL_LOGERR(glGetShaderInfoLog(shaderId, errorLog.size(), NULL, &errorLog[0]));

    DFMCLOG_LINE("Log START:\n" << &errorLog[0] << "\nLog END\n\n");
  }

}
