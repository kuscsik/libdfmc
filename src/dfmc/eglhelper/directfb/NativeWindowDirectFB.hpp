#ifdef EGL_API_DFB
#ifndef DFMC_EGLHELPER_NATIVEWINDOWDIRECTFB_HPP
#define DFMC_EGLHELPER_NATIVEWINDOWDIRECTFB_HPP
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
#include <directfb.h>
#include <egl.h>

namespace dfmc {
namespace eglhelper
{

struct _DFBDisplay
{
    IDirectFB* pDirectFB;
    IDirectFBEventBuffer* pEventBuffer;
    int winWidth, winHeight;
};

class NativeWindowDirectFB : public INativeWindow
{
    EGLNativeWindowType mEGLWindow;
    IDirectFBDisplayLayer* mDFBLayer;
    IDirectFBWindow* mDFBWindow;
    IDirectFB* mDFB;

public:
    static EGLNativeDisplayType Open();
    static void Close(EGLNativeDisplayType  hDisplay);

    NativeWindowDirectFB(const EGLNativeDisplayType hDisplay, const RenderConfig& renderConfig, const EGLDisplay& eglDisplay, const EGLConfig& config);
    virtual ~NativeWindowDirectFB();

    virtual EGLNativeDisplayType GetDisplayType() const;
    virtual EGLNativeWindowType GetWindowType() const;
    virtual bool ProcessMessages() const;
};


}}

#endif
#endif
