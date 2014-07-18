#ifndef DFMC_BASE_EXCEPTIONS_HPP
#define DFMC_BASE_EXCEPTIONS_HPP
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

// Must be the first include!!
#include <dfmc/base/Config.hpp>

#include <stdexcept>

namespace dfmc
{
  class NotImplementedException : public std::logic_error
  {
  public:
    NotImplementedException()
      : std::logic_error("Not implemented")
    {
    }

    explicit NotImplementedException(const std::string& what_arg)
      : std::logic_error(what_arg)
    {
    }
  };


  class UsageErrorException : public std::logic_error
  {
  public:
    UsageErrorException()
      : std::logic_error("UsageErrorException")
    {
    }

    explicit UsageErrorException(const std::string& what_arg)
      : std::logic_error(what_arg)
    {
    }
  };
  

  class IOException : public std::runtime_error
  {
  public:
    explicit IOException(const std::string& what_arg)
      : std::runtime_error(what_arg)
    {
    }
  };

  class ArgumentException : public std::invalid_argument
  {
  public:
    explicit ArgumentException(const std::string& what_arg)
      : std::invalid_argument(what_arg)
    {
    }
  };

  class UnknownTypeException : public std::runtime_error
  {
  public:
    explicit UnknownTypeException(const std::string& what_arg)
      : std::runtime_error(what_arg)
    {
    }
  };

  class GraphicsException : public std::runtime_error
  {
  public:
    explicit GraphicsException(const std::string& what_arg)
      : std::runtime_error(what_arg)
    {
    }
  };


  class OpenGLException : public GraphicsException
  {
    int mglError;
  public:
    explicit OpenGLException(const std::string& what_arg);
    explicit OpenGLException(const std::string& what_arg, const int glError);
    explicit OpenGLException(const int glError);
  };


  class DirectFBException : public GraphicsException
  {
    int mError;
  public:
    explicit DirectFBException(const std::string& what_arg);
    explicit DirectFBException(const std::string& what_arg, const int error);
    explicit DirectFBException(const int error);
  };

}

#endif
