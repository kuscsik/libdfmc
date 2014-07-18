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

#ifdef EGL_API_DFB
#include "NativeWindowDirectFB.hpp"
#include <dfmc/base/BasicTypes.hpp>
#include <dfmc/base/Exceptions.hpp>
#include <cassert>
#include <iostream>

#define DFBCHECK(X) \
    { \
        DFBResult err = X; \
        if (err != DFB_OK) \
        { \
            throw DirectFBException(#X, err); \
        } \
    }


namespace dfmc {
namespace eglhelper
{

namespace
{
    struct _DFBDisplay gHALDisplay;
    bool gIsInitialized = false;
}

EGLNativeDisplayType NativeWindowDirectFB::Open()
{
    assert( ! gIsInitialized );
    IDirectFB* dfb = nullptr;
    IDirectFBDisplayLayer* dfblayer = nullptr;
    IDirectFBEventBuffer* pEventBuffer = nullptr;
    EGLNativeDisplayType display;
    DFBDisplayLayerConfig config;

    try
    {
        DFBCHECK (DirectFBInit(nullptr,nullptr));
        DFBCHECK (DirectFBCreate(&dfb));
        DFBCHECK (dfb->GetDisplayLayer(dfb, DLID_PRIMARY, &dfblayer));
        DFBCHECK (dfblayer->GetConfiguration(dfblayer, &config));

        DFBCHECK (dfb->CreateInputEventBuffer(dfb, DICAPS_KEYS, DFB_FALSE, &(pEventBuffer)));
    }
    catch (const std::exception& ex)
    {
        if( pEventBuffer != nullptr )
            pEventBuffer->Release(pEventBuffer);

        if( dfb != nullptr )
            dfb->Release(dfb);
        throw;
    }

    gHALDisplay.pDirectFB = dfb;
    gHALDisplay.pEventBuffer = pEventBuffer;
    gHALDisplay.winWidth = config.width;
    gHALDisplay.winHeight = config.height;
    gIsInitialized = true;
    display = (EGLNativeDisplayType)(&gHALDisplay);
    return display;
}

void NativeWindowDirectFB::Close(EGLNativeDisplayType)
{
    if( ! gIsInitialized )
      return;

    if( gHALDisplay.pEventBuffer != nullptr )
    {
        gHALDisplay.pEventBuffer->Release(gHALDisplay.pEventBuffer);
        gHALDisplay.pEventBuffer = nullptr;
    }
    if( gHALDisplay.pDirectFB != nullptr )
    {
        gHALDisplay.pDirectFB->Release(gHALDisplay.pDirectFB);
        gHALDisplay.pDirectFB = nullptr;
    }
    gIsInitialized = false;
}

NativeWindowDirectFB::NativeWindowDirectFB(const EGLNativeDisplayType display, const RenderConfig& renderConfig, const EGLDisplay&, const EGLConfig&)
  : mDFBLayer(nullptr)
  , mDFBWindow(nullptr)
  , mDFB(nullptr)
{
    assert(gIsInitialized);
    try
    {
//        std::cout << "WARNING: NativeWindowDirectFB does not implement native window correctly" << std::endl;
        const Rectangle targetRectangle = renderConfig.GetTargetRectangle();
        RenderWindowMode::Enum windowMode = renderConfig.GetWindowMode();
        bool hasValidRect = true;
        if(targetRectangle.Width() == 0 || targetRectangle.Height() == 0)
        {
            hasValidRect = false;
        }

        mDFB 		= gHALDisplay.pDirectFB;

        DFBWindowDescription dfbWindowDesc;

        dfbWindowDesc.flags = (DFBWindowDescriptionFlags) (DWDESC_CAPS | DWDESC_PIXELFORMAT | DWDESC_OPTIONS |DWDESC_SURFACE_CAPS | DWDESC_POSX | DWDESC_POSY | DWDESC_WIDTH | DWDESC_HEIGHT);

        if(windowMode == RenderWindowMode::Enum::Fullscreen || hasValidRect == false)
        {
            dfbWindowDesc.posx   = 0;
            dfbWindowDesc.posy   = 0;
            dfbWindowDesc.width  = gHALDisplay.winWidth;
            dfbWindowDesc.height = gHALDisplay.winHeight;
        }
        else
        {
            dfbWindowDesc.posx   = targetRectangle.X();
            dfbWindowDesc.posy   = targetRectangle.Y();
            dfbWindowDesc.width  = targetRectangle.Width();
            dfbWindowDesc.height = targetRectangle.Height();
        }

        dfbWindowDesc.surface_caps = DSCAPS_DOUBLE;
        dfbWindowDesc.caps = (DFBWindowCapabilities)(DWCAPS_ALPHACHANNEL | DWCAPS_DOUBLEBUFFER);
        dfbWindowDesc.pixelformat = DSPF_ARGB;

        if(windowMode == RenderWindowMode::Enum::Fullscreen && hasValidRect == true)
        {
            dfbWindowDesc.options = (DFBWindowOptions)(DWOP_ALPHACHANNEL | DWOP_SCALE);
        }
        else
        {
            dfbWindowDesc.options = DWOP_ALPHACHANNEL;
        }

        DFBCHECK (mDFB->GetDisplayLayer(mDFB, DLID_PRIMARY, &mDFBLayer));
        DFBCHECK (mDFBLayer->SetCooperativeLevel (mDFBLayer, DLSCL_ADMINISTRATIVE));
        DFBCHECK (mDFBLayer->EnableCursor (mDFBLayer, 0));
        DFBCHECK (mDFBLayer->CreateWindow(mDFBLayer, &dfbWindowDesc,	&mDFBWindow));
        DFBCHECK (mDFBWindow->SetOpacity( mDFBWindow, 0xff ));

        if(windowMode == RenderWindowMode::Enum::Fullscreen && hasValidRect == true)
        {
            DFBCHECK (mDFBWindow->MoveTo( mDFBWindow, targetRectangle.X(), targetRectangle.Y() ));
            DFBCHECK (mDFBWindow->Resize( mDFBWindow, targetRectangle.Width(), targetRectangle.Height() ));
        }

        mEGLWindow = mDFBWindow;
    }
    catch (const std::exception& ex)
    {
        if( mDFBWindow != nullptr )
        {
            mDFBWindow->Release(mDFBWindow);
            mDFBWindow = nullptr;
        }
    }
}

NativeWindowDirectFB::~NativeWindowDirectFB()
{
    if( mDFBWindow != nullptr )
    {
        mDFBWindow->Release(mDFBWindow);
        mDFBWindow = nullptr;
    }
}

EGLNativeDisplayType NativeWindowDirectFB::GetDisplayType() const
{
    assert(gIsInitialized);
    return (EGLNativeDisplayType)(&gHALDisplay);
}

EGLNativeWindowType NativeWindowDirectFB::GetWindowType() const
{
    assert(gIsInitialized);
    return mEGLWindow;
}

bool NativeWindowDirectFB::ProcessMessages() const
{
    assert(gIsInitialized);
    return true;
}

}}
#endif
