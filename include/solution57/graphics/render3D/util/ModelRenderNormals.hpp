#ifndef DFMC_GRAPHICS_RENDER3D_UTIL_MODELRENDERNORMALS_HPP
#define DFMC_GRAPHICS_RENDER3D_UTIL_MODELRENDERNORMALS_HPP
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

#include <dfmc/graphics/render3D/util/ModelRender.hpp>
#include <dfmc/graphics/render3D/util/SimpleModel.hpp>

namespace dfmc
{
  // Render the model vertex normals
  class ModelRenderNormals : public ModelRender
  {
    const int mVertexCount;
    float* mpVertices;
  public:
    ModelRenderNormals( const SimpleModel& model );
    ~ModelRenderNormals();

    void Bind(const ShaderVertexConfig& shaderConfig);
    void Draw();
    void Unbind();
  };

}
#endif