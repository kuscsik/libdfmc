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

#include <algorithm>
#include <cstring>
#include <dfmc/base/Pointers.hpp>
#include <dfmc/graphics/render3D/Texture.hpp>
#include <dfmc/base/graphics/RawBitmapUtil.hpp>

namespace dfmc
{
  Texture::Texture()
    : mId(GL_INVALID_VALUE)
    , mTextureSize()
    , mSourceWidth(0)
    , mSourceHeight(0)
  {
  }


  Texture::Texture(const RawBitmap& srcBitmap, const GLenum type, const bool bNearestFiltering)
    : mId(GL_INVALID_VALUE)
    , mTextureSize()
    , mSourceWidth(0)
    , mSourceHeight(0)
  {
    SetData(srcBitmap, type, bNearestFiltering);
  }


  Texture::~Texture()
  {
    ReleaseContent();
  }

  void Texture::ReleaseContent()
  {
    if( mId != GL_INVALID_VALUE )
    {
      glDeleteTextures(1, &mId);
      mId = GL_INVALID_VALUE;
    }
    mTextureSize = Point2(0,0);
    mSourceWidth = 0;
    mSourceHeight = 0;
  }

  void Texture::SetData(const RawBitmap& srcBitmap, const GLenum type, const bool bNearestFiltering)
  {
    ReleaseContent();

    // Make sure that the texture is a square pow2 size.
    int texWidth = Math::ToPowerOfTwo(srcBitmap.Width);
    int texHeight = Math::ToPowerOfTwo(srcBitmap.Height);
    if( texWidth >= texHeight )
      texHeight = texWidth;
    else
      texWidth = texHeight;

    const uint8_t* pSrc = srcBitmap.pContent;
    std::auto_ptr<uint8_t> tmpSrc;
    if( srcBitmap.Width != texWidth || srcBitmap.Height != texHeight )
    {
      const int cbDst = texWidth * texHeight * 4;
      tmpSrc.reset(new uint8_t[cbDst]);
      uint8_t* pDst = tmpSrc.get();
      memset(pDst, 0, cbDst);

      RawBitmapEx dst(pDst, texWidth, texHeight);
      RawBitmapUtil::Copy(dst, Point2(0, 0), srcBitmap);
      pSrc = pDst;
    }

    glGenTextures(1, &mId);

    glBindTexture(GL_TEXTURE_2D, mId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, type, texWidth, texHeight, 0, type, GL_UNSIGNED_BYTE, pSrc);
    
    const GLint filter = (bNearestFiltering ? GL_NEAREST : GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    mSourceWidth = srcBitmap.Width;
    mSourceHeight = srcBitmap.Height;

    mTextureSize = Point2(texWidth, texHeight);
  }

  const Point2 Texture::GetTextureSize() const
  {
    return mTextureSize;
  }

  int Texture::GetWidth() const
  {
    return mSourceWidth;
  }

  int Texture::GetHeight() const
  {
    return mSourceHeight;
  }

}
