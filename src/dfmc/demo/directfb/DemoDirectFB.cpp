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

#ifdef DFMC_HAS_DIRECTFB
#include <dfmc/demo/directfb/DemoDirectFB.hpp>
#include <dfmc/base/BasicTypes.hpp>
#include <dfmc/base/Exceptions.hpp>
#include <dfmc/base/log/Log.hpp>
#include <cassert>
#include <deque>
#include <iostream>
#include <vector>

#include <stdio.h>
#include <unistd.h>

#define DFBCHECK(X)\
{ \
  DFBResult err = X; \
  if (err != DFB_OK) \
  { \
    throw DirectFBException(#X, err); \
  } \
}

namespace dfmc
{
  DemoDirectFB::DemoDirectFB(const DemoConfig& demoConfig, IDemoController& demoController)
    : mConfig(demoConfig.GetAppFactory()->GetConfig())
    , mScreenArea()
    , mpDfb(nullptr)
    , mpDfbsurface(nullptr)
    , mpDfblayer(nullptr)
    , mpDfbwindow(nullptr)
    , mCustomDemoEnv()
    , mAppController()
    , mDirectMode(false)
  {
      DFBDisplayLayerConfig config;

      try
      {
        mScreenArea = demoConfig.GetRenderConfig().GetTargetRectangle();
        RenderWindowMode::Enum windowMode = demoConfig.GetRenderConfig().GetWindowMode();
        bool hasValidRect = true;
        if(mScreenArea.Width() == 0 || mScreenArea.Height() == 0)
        {
            hasValidRect = false;
        }

        DFBCHECK(DirectFBInit(nullptr, nullptr));
        DFBCHECK(DirectFBCreate(&mpDfb));

        if( windowMode == RenderWindowMode::Fullscreen && hasValidRect == false)
        {
          mDirectMode = true;
          DFBCHECK (mpDfb->SetCooperativeLevel (mpDfb, DFSCL_FULLSCREEN));
          DFBSurfaceDescription dsc;
          dsc.flags = DSDESC_CAPS;
          dsc.caps  = (DFBSurfaceCapabilities)(DSCAPS_PRIMARY | DSCAPS_FLIPPING);
          int scrW, scrH;
          DFBCHECK (mpDfb->CreateSurface( mpDfb, &dsc, &mpDfbsurface ));
          DFBCHECK (mpDfbsurface->GetSize (mpDfbsurface, &scrW, &scrH));
          mScreenArea = Rectangle(0, 0, scrW, scrH);
        }
        else
        {
          DFBCHECK (mpDfb->GetDisplayLayer(mpDfb, DLID_PRIMARY, &mpDfblayer));
          DFBCHECK (mpDfblayer->SetCooperativeLevel (mpDfblayer, DLSCL_ADMINISTRATIVE));
          DFBCHECK (mpDfblayer->EnableCursor (mpDfblayer, 0));
          DFBCHECK (mpDfblayer->GetConfiguration(mpDfblayer, &config));

          if(windowMode != RenderWindowMode::Offscreen)
          {
            DFBWindowDescription dfbWindowDesc;

            dfbWindowDesc.flags = (DFBWindowDescriptionFlags) (DWDESC_CAPS | DWDESC_PIXELFORMAT | DWDESC_OPTIONS |DWDESC_SURFACE_CAPS | DWDESC_POSX | DWDESC_POSY | DWDESC_WIDTH | DWDESC_HEIGHT);

            if(windowMode == RenderWindowMode::Fullscreen || hasValidRect == false)
            {
              dfbWindowDesc.posx   = 0;
              dfbWindowDesc.posy   = 0;
              dfbWindowDesc.width  = config.width;
              dfbWindowDesc.height = config.height;
            }
            else
            {
              dfbWindowDesc.posx   = mScreenArea.X();
              dfbWindowDesc.posy   = mScreenArea.Y();
              dfbWindowDesc.width  = mScreenArea.Width();
              dfbWindowDesc.height = mScreenArea.Height();
            }

            dfbWindowDesc.surface_caps = DSCAPS_DOUBLE;
            dfbWindowDesc.caps = (DFBWindowCapabilities)(DWCAPS_ALPHACHANNEL | DWCAPS_DOUBLEBUFFER);
            dfbWindowDesc.pixelformat = DSPF_ARGB;

            if(windowMode == RenderWindowMode::Fullscreen && hasValidRect == true)
            {
              dfbWindowDesc.options = (DFBWindowOptions)(DWOP_ALPHACHANNEL | DWOP_SCALE);
            }
            else
            {
              dfbWindowDesc.options = DWOP_ALPHACHANNEL;
            }

            DFBCHECK (mpDfblayer->CreateWindow(mpDfblayer, &dfbWindowDesc, &mpDfbwindow));
            DFBCHECK (mpDfbwindow->SetOpacity( mpDfbwindow, 0xff ));

            if(windowMode == RenderWindowMode::Fullscreen && hasValidRect == true)
            {
              DFBCHECK (mpDfbwindow->MoveTo( mpDfbwindow, mScreenArea.X(), mScreenArea.Y() ));
              DFBCHECK (mpDfbwindow->Resize( mpDfbwindow, mScreenArea.Width(), mScreenArea.Height() ));
            }

            DFBCHECK(mpDfbwindow->GetSurface(mpDfbwindow, &mpDfbsurface));
          }
        }


        mCustomDemoEnv.reset( new CustomDemoEnvironmentDirectFB(mpDfb, mpDfbsurface) );

        // Everything is setup lets spawn the app and let it play
        const Point2 screenResolution(mScreenArea.Width(), mScreenArea.Height());
        const DemoEnvironment demoEnvironment(demoConfig.GetDemoDataProvider(), screenResolution, mCustomDemoEnv);
        mAppController.reset(new DemoAppController(demoConfig, demoController, demoEnvironment, true, mConfig.RestartOnResize));
      }
      catch (const std::exception&)
      {
        Cleanup();
        throw;
      }
  }


  DemoDirectFB::~DemoDirectFB()
  {
    Cleanup();
  }


  int DemoDirectFB::RunDemo()
  {
    const Point2 screenResolution(mScreenArea.Width(), mScreenArea.Height());

    while (! mAppController->HasExitRequest())
    {
      if( mAppController->GetDemoState() == DemoState::Running )
      {
        //DFBCHECK(dfbsurface->SetColor(dfbsurface, 0x00, 0x00, 0x00, 0xff));
        //DFBCHECK(dfbsurface->FillRectangle(dfbsurface, 0, 0, screen_width, screen_height));
        //DFBCHECK(dfbsurface->SetColor(dfbsurface, 0xff, 0xff, 0xff, 0xff));
        //DFBCHECK(dfbsurface->DrawLine(dfbsurface, 0, (screen_height / 2) + crawler, screen_width - 1, screen_height / 2));
        //DFBCHECK(dfbwindow->SetOpacity(dfbwindow, 0xcd + crawler));

        mAppController->Render(screenResolution);

        if(mpDfbsurface != nullptr)
        {
          DFBCHECK(mpDfbsurface->Flip(mpDfbsurface, NULL, DSFLIP_WAITFORSYNC));
        }
      }
      mAppController->SequenceCompleted();
    }

    return mAppController->CloseApp();
  }


  void DemoDirectFB::Cleanup()
  {
    // Release the app first, since it expects GL to be ready
    mAppController.reset();

    // Release the custom demo environment
    mCustomDemoEnv.reset();

    // We only get this surface so no need to release (unless we are in direct mode)
    if( mpDfbsurface != nullptr && mDirectMode )
    {
      mpDfbsurface->Release( mpDfbsurface );
    }
    mpDfbsurface = nullptr;

    if( mpDfbwindow != nullptr )
    {
      mpDfbwindow->Release(mpDfbwindow);
      mpDfbwindow = nullptr;
    }
    if( mpDfb != nullptr )
    {
      mpDfb->Release(mpDfb);
      mpDfb = nullptr;
    }
  }

}
#endif
