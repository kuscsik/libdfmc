#ifndef DFMC_EGLHELPER_INATIVEWINDOW_HPP
#define DFMC_EGLHELPER_INATIVEWINDOW_HPP
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

#include <dfmc/base/Noncopyable.hpp>

#include <EGL/egl.h>

namespace dfmc {
namespace eglhelper
{
  class INativeWindow : private Noncopyable
  {
  public:
    virtual ~INativeWindow() {}

    virtual EGLNativeDisplayType GetDisplayType() const = 0;
    virtual EGLNativeWindowType GetWindowType() const = 0;

    //! return false if a the window was closed by the user
    virtual bool ProcessMessages() const = 0;
  };


}}

#endif
