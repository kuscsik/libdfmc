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
#include <cstddef>
#include <dfmc/base/BasicTypes.hpp>
#include <dfmc/graphics/procedural/Util.hpp>
#include <dfmc/graphics/render3D/util/ModelRenderNormals.hpp>

namespace dfmc
{

  ModelRenderNormals::ModelRenderNormals( const SimpleModel& model )
    : mVertexCount(model.GetVertexCount() * 2)
    , mpVertices(nullptr)
  {
    const std::vector<VertexPositionColor> normals = procedural::Util::ExtractNormalsAsLineList(model, 5);

    mpVertices = new float[mVertexCount*3];
    for( int i=0; i<mVertexCount; ++i )
    {
      mpVertices[i*3+0] = normals[i].Position.X;
      mpVertices[i*3+1] = normals[i].Position.Y;
      mpVertices[i*3+2] = normals[i].Position.Z;
    }
  }

  ModelRenderNormals::~ModelRenderNormals()
  {
    delete [] mpVertices;
    mpVertices = nullptr;
  }

  void ModelRenderNormals::Bind(const ShaderVertexConfig& shaderConfig)
  {
    assert( shaderConfig.Position != GL_INVALID_VALUE );

    glVertexAttribPointer(shaderConfig.Position, 3, GL_FLOAT, GL_FALSE, 0, mpVertices);
    glEnableVertexAttribArray(shaderConfig.Position);
  }

  void ModelRenderNormals::Draw()
  {
    glDrawArrays(GL_LINES, 0, mVertexCount);
  }

  void ModelRenderNormals::Unbind()
  {
  }

}

