#ifndef DFMC_BASE_MATH_VECTOR2_HPP
#define DFMC_BASE_MATH_VECTOR2_HPP
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

#include <dfmc/base/math/Math.hpp>

namespace dfmc
{

  struct Vector2
  {
  public:
    float X;
    float Y;

    Vector2() 
      : X(0.0f), Y(0.0f)
    {
    }

    Vector2(float x, float y) 
      : X(x), Y(y)
    {
    }

    float Length() const
    {
        return Math::Sqrt(LengthSquared());
    }

    float LengthSquared() const
    {
        return X * X + Y * Y;
    }

    void Normalize()
    {
      float factor = Length();
      factor = 1.0f / factor;
      X *= factor;
      Y *= factor;
    }

    Vector2& operator+=(const Vector2& arg) 
    { 
      X += arg.X;
      Y += arg.Y;
      return *this;
    }

    Vector2& operator-=(const Vector2& arg) 
    { 
      X -= arg.X;
      Y -= arg.Y;
      return *this;
    }

    Vector2& operator*=(const Vector2& arg) 
    { 
      X *= arg.X;
      Y *= arg.Y;
      return *this;
    }

    Vector2& operator*=(const float arg) 
    { 
      X *= arg;
      Y *= arg;
      return *this;
    }

    Vector2& operator*=(const int arg) 
    { 
      X *= arg;
      Y *= arg;
      return *this;
    }

    static Vector2 Zero() { return Vector2(); }
    static Vector2 One() { return Vector2(1.0f, 1.0f); }
  };



  namespace 
  {
    const Vector2 operator+(const Vector2& lhs, const Vector2& rhs) 
    { 
      return Vector2(lhs.X + rhs.X, lhs.Y + rhs.Y);
    }

    const Vector2 operator-(const Vector2& lhs, const Vector2& rhs) 
    { 
      return Vector2(lhs.X - rhs.X, lhs.Y - rhs.Y);
    }

    const Vector2 operator*(const Vector2& lhs, const Vector2& rhs) 
    { 
      return Vector2(lhs.X * rhs.X, lhs.Y * rhs.Y);
    }

    const Vector2 operator*(const Vector2& lhs, const float rhs) 
    { 
      return Vector2(lhs.X * rhs, lhs.Y * rhs);
    }

    const Vector2 operator*(const float lhs, const Vector2& rhs) 
    { 
      return rhs * lhs;
    }

    const Vector2 operator*(const Vector2& lhs, const int rhs) 
    { 
      return Vector2(lhs.X * rhs, lhs.Y * rhs);
    }
    
    const Vector2 operator*(const int lhs, const Vector2& rhs) 
    { 
      return rhs * lhs;
    }
  }
}

#endif
