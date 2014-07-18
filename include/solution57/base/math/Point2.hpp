#ifndef DFMC_BASE_MATH_POINT2_HPP
#define DFMC_BASE_MATH_POINT2_HPP
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

namespace dfmc
{

  struct Point2
  {
  public:
    int X;
    int Y;

    Point2() 
      : X(0), Y(0)
    {
    }

    Point2(const int x, const int y) 
      : X(x), Y(y)
    {
    }

    Point2& operator+=(const Point2& arg) 
    { 
      X += arg.X;
      Y += arg.Y;
      return *this;
    }

    Point2& operator-=(const Point2& arg) 
    { 
      X -= arg.X;
      Y -= arg.Y;
      return *this;
    }

    Point2& operator*=(const Point2& arg) 
    { 
      X *= arg.X;
      Y *= arg.Y;
      return *this;
    }

    Point2& operator*=(const int arg) 
    { 
      X *= arg;
      Y *= arg;
      return *this;
    }

    bool operator==(const Point2 &rhs) const
    {
      return X == rhs.X && Y == rhs.Y;
    }

    bool operator!=(const Point2 &rhs) const
    {
      return X != rhs.X || Y != rhs.Y;
    }

  };


  namespace 
  {
    const Point2 operator+(const Point2& lhs, const Point2& rhs) 
    { 
      return Point2(lhs.X + rhs.X, lhs.Y + rhs.Y);
    }

    const Point2 operator-(const Point2& lhs, const Point2& rhs) 
    { 
      return Point2(lhs.X - rhs.X, lhs.Y - rhs.Y);
    }

    const Point2 operator*(const Point2& lhs, const Point2& rhs) 
    { 
      return Point2(lhs.X * rhs.X, lhs.Y * rhs.Y);
    }

    const Point2 operator*(const Point2& lhs, const int rhs) 
    { 
      return Point2(lhs.X * rhs, lhs.Y * rhs);
    }

    const Point2 operator*(const int lhs, const Point2& rhs) 
    { 
      return rhs * lhs;
    }
  }
}

#endif
