#ifndef DFMC_RENDER_GL_GLCHECK_HPP
#define DFMC_RENDER_GL_GLCHECK_HPP
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

#include <dfmc/base/Exceptions.hpp>

#define GL_CHECKERR(X) \
  X; \
  { \
    GLenum glError = glGetError(); \
    if (glError != GL_NO_ERROR) \
      throw dfmc::OpenGLException(#X, glError); \
  }

#define GL_LOGERR(X) \
  X; \
  { \
    GLenum glError = glGetError(); \
    if (glError != GL_NO_ERROR) \
    { \
      DFMCLOG_LINE("ERROR: " << #X << " glGetError() == " << glError); \
      return; \
    } \
  }

#endif
