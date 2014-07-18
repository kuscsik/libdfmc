#ifndef DFMC_GRAPHICS_RENDER3D_TEXTURE_HPP
#define DFMC_GRAPHICS_RENDER3D_TEXTURE_HPP
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
#include "DataTypes.hpp"
#include <dfmc/base/Noncopyable.hpp>
#include <dfmc/base/BasicTypes.hpp>
#include <dfmc/base/graphics/RawBitmap.hpp>
#include <dfmc/base/math/Point2.hpp>

namespace dfmc
{

  // For now this only supports simple 32bpp textures
  class Texture : private Noncopyable
  {
    GLuint mId;
    Point2 mTextureSize;
    int mSourceWidth;
    int mSourceHeight;
  public:
    Texture();
    Texture(const RawBitmap& srcBitmap, const GLenum type, const bool bNearestFiltering);
    virtual ~Texture();

    void ReleaseContent();

    void SetData(const RawBitmap& srcBitmap, const GLenum type, const bool bNearestFiltering);

    const Point2 GetTextureSize() const;

    int GetWidth() const;
    int GetHeight() const;

    GLuint GetTextureId() const { return mId; }
  };
}

#endif
