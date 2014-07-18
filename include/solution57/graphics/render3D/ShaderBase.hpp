#ifndef DFMC_GRAPHICS_RENDER3D_SHADERBASE_HPP
#define DFMC_GRAPHICS_RENDER3D_SHADERBASE_HPP
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
#include "ShaderVertexConfig.hpp"

namespace dfmc
{
  class ShaderBase : private Noncopyable
  {
    bool mIsLoaded;
    CompiledShaderPtr mFragShader;
    CompiledShaderPtr mVertShader;
    GLuint mProgramId;
  protected:
    ShaderVertexConfig mShaderVertexConfig;
  public:

    class ScopedUse : Noncopyable
    {
      ShaderBase& mShader;
    public:
      ScopedUse(ShaderBase& shader) : mShader(shader) { mShader.Load(); }
      ~ScopedUse() { mShader.Unload(); }
    };

    ShaderBase(const char*const pszVertFile, const char*const pszFragFile, const bool bIsFileNames);
    virtual ~ShaderBase();

    GLuint GetProgramId() const { return mProgramId; }

    const ShaderVertexConfig GetShaderConfig() const { return mShaderVertexConfig; }
  protected:
    void Load();
    void Unload();

    bool IsLoaded() const { return mIsLoaded; }
  };

}
#endif