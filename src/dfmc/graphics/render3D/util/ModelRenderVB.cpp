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

#include <cstddef>
#include <dfmc/graphics/render3D/util/ModelRenderVB.hpp>

namespace dfmc
{
  namespace
  {
    GLenum Convert(const PrimitiveType::Enum pt)
    {
      switch( pt )
      {
      case PrimitiveType::TriangleList:
        return GL_TRIANGLES;
      case PrimitiveType::TriangleStrip:
        return GL_TRIANGLE_STRIP;
      case PrimitiveType::LineList:
        return GL_LINES;
      case PrimitiveType::LineStrip:
        return GL_LINE_STRIP;
      default:
        return GL_POINTS;
      }
    }
  }


  ModelRenderVB::ModelRenderVB( const SimpleModel& model )
    : mVB(model.GetVertices(), model.GetVertexCount())
    , mIB(model.GetIndices(), model.GetIndexCount(), IndexFormat::UInt16)
    , mPrimitiveType(Convert(model.GetPrimitiveType()))
  {
  }


  void ModelRenderVB::Bind(const ShaderVertexConfig& shaderConfig)
  {
    mVB.Bind(shaderConfig);
    mIB.Bind();
  }

  void ModelRenderVB::Draw()
  {
    glDrawElements(mPrimitiveType, mIB.GetCount(), mIB.GetOpenGLType(), (void*)0);
  }

  void ModelRenderVB::Unbind()
  {
    mIB.Unbind();
    mVB.Unbind();
  }

}

