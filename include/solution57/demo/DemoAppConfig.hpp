#ifndef DFMC_DEMO_DEMOAPPCONFIG_HPP
#define DFMC_DEMO_DEMOAPPCONFIG_HPP
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

#include <dfmc/base/math/Rectangle.hpp>

namespace dfmc
{
  struct DemoAppConfig
  {
    bool UseOpenGLES;
    bool UseOpenVG;
    bool ForceConformance;
    // If this is set the demo will be restarted when a screen resize is detected
    bool RestartOnResize;

    DemoAppConfig(const bool useOpenGLES, const bool useOpenVG, const bool forceConformance)
      : UseOpenGLES(useOpenGLES)
      , UseOpenVG(useOpenVG)
      , ForceConformance(forceConformance)
      , RestartOnResize(true)
    {
    }

    DemoAppConfig(const bool useOpenGLES, const bool useOpenVG, const bool forceConformance, const bool restartOnResize)
      : UseOpenGLES(useOpenGLES)
      , UseOpenVG(useOpenVG)
      , ForceConformance(forceConformance)
      , RestartOnResize(restartOnResize)
    {
    }
  };
}
#endif
