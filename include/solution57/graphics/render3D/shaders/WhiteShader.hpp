#ifndef DFMC_GRAPHICS_RENDER3D_SHADERS_WHITESHADER_HPP
#define DFMC_GRAPHICS_RENDER3D_SHADERS_WHITESHADER_HPP
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

#include <dfmc/base/math/Matrix.hpp>
#include <dfmc/base/math/Vector3.hpp>
#include <dfmc/graphics/render3D/ShaderBase.hpp>

namespace dfmc
{
  class WhiteShader : public ShaderBase
  {
    GLint mLocWVP;
  public:
    WhiteShader();

    void SetWorldViewProjection(const Matrix& matrix);
  };

}
#endif