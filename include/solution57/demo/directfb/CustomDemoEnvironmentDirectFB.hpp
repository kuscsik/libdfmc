#ifdef DFMC_HAS_DIRECTFB
#ifndef DFMC_DEMO_CUSTOMDEMOENVIRONMENTDIRECTFB_HPP
#define DFMC_DEMO_CUSTOMDEMOENVIRONMENTDIRECTFB_HPP
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

#include <dfmc/demo/ICustomDemoEnvironment.hpp>
#include <directfb.h>

namespace dfmc
{
  class CustomDemoEnvironmentDirectFB : public ICustomDemoEnvironment
  {
    IDirectFB* mpDfb;
    IDirectFBSurface* mpDfbsurface;
  public:
    CustomDemoEnvironmentDirectFB(IDirectFB* pDfb, IDirectFBSurface* pDfbsurface)
      : mpDfb(pDfb)
      , mpDfbsurface(pDfbsurface)
    {
    }

    IDirectFB* GetDirectFB() const
    {
      return mpDfb;
    }

    IDirectFBSurface* GetSurfaceHandle() const
    {
      return mpDfbsurface;
    }
  };
}
#endif
#endif
