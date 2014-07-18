#ifndef DFMC_GRAPHICS_RENDER3D_UTIL_MODELRENDERBASIC_HPP
#define DFMC_GRAPHICS_RENDER3D_UTIL_MODELRENDERBASIC_HPP
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

#include "ModelRender.hpp"
#include <dfmc/base/BasicTypes.hpp>
#include <dfmc/graphics/render3D/util/SimpleModel.hpp>

namespace dfmc
{
  // Render the model using basic client side arrays (slow but easy)
  class ModelRenderBasic : public ModelRender
  {
    const int mVertexCount;
    const int mIndexCount;
    float* mpVertices;
    float* mpNormals;
    float* mpTextureCoords;
    uint16_t* mpIndices; 
  public:
    ModelRenderBasic( const SimpleModel& model );
    virtual ~ModelRenderBasic();

    virtual void Bind(const ShaderVertexConfig& shaderConfig);
    virtual void Draw();
    virtual void Unbind();
  };

}
#endif