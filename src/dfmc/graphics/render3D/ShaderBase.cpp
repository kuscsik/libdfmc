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
#include <dfmc/base/Exceptions.hpp>
#include <dfmc/base/io/FileUtil.hpp>
#include <dfmc/graphics/render3D/ShaderBase.hpp>
#include <dfmc/graphics/render3D/ShaderCompiler.hpp>
#include <dfmc/graphics/render3D/ShaderBase.hpp>
#include "gl/GLCheck.hpp"
#include <string>

#include <cstdlib>

namespace dfmc
{
  ShaderBase::ShaderBase(const char*const pszVertFile, const char*const pszFragFile, const bool bIsFileNames)
    : mIsLoaded(false)
    , mFragShader()
    , mVertShader()
    , mProgramId(0)
  {
    ShaderCompiler compiler(true);
    if( bIsFileNames )
    {
      std::string strVert(FileUtil::ReadAllText(pszVertFile));
      std::string strFrag(FileUtil::ReadAllText(pszFragFile));
      mVertShader = compiler.Compile(strVert.c_str(), GL_VERTEX_SHADER);
      mFragShader = compiler.Compile(strFrag.c_str(), GL_FRAGMENT_SHADER);
    }
    else
    {
      mVertShader = compiler.Compile(pszVertFile, GL_VERTEX_SHADER);
      mFragShader = compiler.Compile(pszFragFile, GL_FRAGMENT_SHADER);
    }

    // Create mProgramId (ready to attach shaders)
    mProgramId = glCreateProgram();

    // Attach shaders and link mProgramId
    GL_CHECKERR(glAttachShader(mProgramId, mVertShader->GetShaderHandle()));
    GL_CHECKERR(glAttachShader(mProgramId, mFragShader->GetShaderHandle()));
    GL_CHECKERR(glLinkProgram(mProgramId));
  }

  ShaderBase::~ShaderBase()
  {
    glDeleteProgram(mProgramId);
  }

  void ShaderBase::Load() 
  {
    assert(! mIsLoaded);
    mIsLoaded = true;
    GL_CHECKERR(glUseProgram(mProgramId));
  }

  void ShaderBase::Unload() 
  {
    assert(mIsLoaded);
    GL_CHECKERR(glUseProgram(0));
    mIsLoaded = false;
  }
}

