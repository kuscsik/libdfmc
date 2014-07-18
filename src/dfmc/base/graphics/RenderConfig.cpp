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

#include <dfmc/base/graphics/RenderConfig.hpp>
#include <cassert>
#include <dfmc/base/Exceptions.hpp>

namespace dfmc
{
  RenderConfig::RenderConfig()
    : mTargetRectangle()
    , mWindowMode(RenderWindowMode::Fullscreen)
  {
  }


  const dfmc::Rectangle RenderConfig::GetTargetRectangle() const
  {
    return mTargetRectangle;
  }


  void RenderConfig::SetTargetRectangle(const dfmc::Rectangle& value)
  {
    mTargetRectangle = value;
  }


  void RenderConfig::SetTargetRectangle(const int16_t x, const int16_t y, const int16_t width, const int16_t height)
  {
    if (x < 0 || y < 0 || width < 0 || height < 0)
      throw dfmc::ArgumentException("The supplied rectangle is invalid");

    mTargetRectangle = dfmc::Rectangle(x, y, width, height);
  }


  RenderWindowMode::Enum RenderConfig::GetWindowMode() const
  {
    return mWindowMode;
  }


  void RenderConfig::SetWindowMode(const RenderWindowMode::Enum value)
  {
    mWindowMode = value;
  }
}
