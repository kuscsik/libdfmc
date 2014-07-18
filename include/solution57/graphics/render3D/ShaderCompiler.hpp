#ifndef DFMC_GRAPHICS_RENDER3D_SHADERCOMPILER_HPP
#define DFMC_GRAPHICS_RENDER3D_SHADERCOMPILER_HPP
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
#include <dfmc/base/BasicTypes.hpp>
#include <dfmc/base/Noncopyable.hpp>
#include <dfmc/graphics/render3D/CompiledShader.hpp>

namespace dfmc
{
  class ShaderCompiler : private Noncopyable
  {
    bool mbVerbose;
  public:
    ShaderCompiler(const bool bVerbose);

    const CompiledShaderPtr Compile(const char*const pszShader, const GLint shaderType);

  private:
    void DumpDebugInfo(const GLuint shaderId);
  };
}
#endif
