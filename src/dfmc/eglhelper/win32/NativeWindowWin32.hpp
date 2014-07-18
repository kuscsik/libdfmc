#ifdef _WIN32
#ifndef DFMC_EGLHELPER_NATIVEWINDOWWIN32_HPP
#define DFMC_EGLHELPER_NATIVEWINDOWWIN32_HPP
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
#include <dfmc/eglhelper/INativeWindow.hpp>

namespace dfmc {
namespace eglhelper
{
  class NativeWindowWin32 : public INativeWindow
  {
    EGLNativeWindowType mhWindow;
  public:
    static EGLNativeDisplayType Open();
    static void Close(EGLNativeDisplayType  hDisplay);

    NativeWindowWin32(const EGLNativeDisplayType hDisplay, const RenderConfig& renderConfig, const EGLDisplay& eglDisplay, const EGLConfig& config);
    virtual ~NativeWindowWin32();

    virtual EGLNativeDisplayType GetDisplayType() const;
    virtual EGLNativeWindowType GetWindowType() const;
    virtual bool ProcessMessages() const;
  };


}}

#endif
#endif
