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
#include <dfmc/graphics/render3D/util/ModelRenderBasic.hpp>

namespace dfmc
{

  ModelRenderBasic::ModelRenderBasic( const SimpleModel& model )
    : mVertexCount(model.GetVertexCount())
    , mIndexCount(model.GetIndexCount())
    , mpVertices(nullptr)
    , mpNormals(nullptr)
    , mpTextureCoords(nullptr)
    , mpIndices(nullptr)
  {
    const int indexCount = model.GetIndexCount();
    const int* pSrcIndices = model.GetIndices();
    const VertexPositionNormalTexture*const src = model.GetVertices();
    const int vertexCount = model.GetVertexCount();
    mpVertices = new float[3*vertexCount];
    mpNormals = new float[3*vertexCount];
    mpTextureCoords = new float[2*vertexCount];
    mpIndices = new unsigned short[indexCount];
    for( int i=0; i<vertexCount; ++i )
    {
      mpVertices[i*3+0] = src[i].Position.X;
      mpVertices[i*3+1] = src[i].Position.Y;
      mpVertices[i*3+2] = src[i].Position.Z;

      mpNormals[i*3+0] = src[i].Normal.X;
      mpNormals[i*3+1] = src[i].Normal.Y;
      mpNormals[i*3+2] = src[i].Normal.Z;

      mpTextureCoords[i*2+0] = src[i].TextureCoordinate.X;
      mpTextureCoords[i*2+1] = src[i].TextureCoordinate.Y;
    }

    for( int i=0; i<indexCount; ++i )
    {
      mpIndices[i] = (unsigned short)pSrcIndices[i];
    }
  }

  ModelRenderBasic::~ModelRenderBasic()
  {
    delete [] mpVertices;
    mpVertices = nullptr;
    delete [] mpNormals;
    mpNormals = nullptr;
    delete [] mpTextureCoords;
    mpTextureCoords = nullptr;
    delete [] mpIndices;
    mpIndices = nullptr;
  }

  void ModelRenderBasic::Bind(const ShaderVertexConfig& shaderConfig)
  {
    if( shaderConfig.Position != GL_INVALID_VALUE )
    {
      glVertexAttribPointer(shaderConfig.Position, 3, GL_FLOAT, GL_FALSE, 0, mpVertices);
      glEnableVertexAttribArray(shaderConfig.Position);   
    }

    if( shaderConfig.Normal != GL_INVALID_VALUE )
    {
      glVertexAttribPointer(shaderConfig.Normal, 3, GL_FLOAT, GL_FALSE, 0, mpNormals);
      glEnableVertexAttribArray(shaderConfig.Normal);
    }

    if( shaderConfig.TexCoord != GL_INVALID_VALUE )
    {
      glVertexAttribPointer(shaderConfig.TexCoord, 2, GL_FLOAT, GL_FALSE, 0, mpTextureCoords);
      glEnableVertexAttribArray(shaderConfig.TexCoord);
    }
  }

  void ModelRenderBasic::Draw()
  {
    glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_SHORT, mpIndices);

    // glDrawElements(GL_TRIANGLES, model.GetIndexCount(), GL_UNSIGNED_SHORT, pIndices);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, pIndices);
  }

  void ModelRenderBasic::Unbind()
  {
  }

}

