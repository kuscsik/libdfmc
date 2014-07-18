#ifndef DFMC_BASE_MATH_VECTOR4_HPP
#define DFMC_BASE_MATH_VECTOR4_HPP
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

  struct Vector4
  {
  public:

    float X;
    float Y;
    float Z;
    float W;

    Vector4() 
      : X(0.0f), Y(0.0f), Z(0.0f), W(0.0f)
    {
    }

    Vector4(const float x, const float y, const float z, const float w) 
      : X(x), Y(y), Z(z), W(w)
    {
    }

    float Length() const
    {
        return Math::Sqrt(LengthSquared());
    }

    float LengthSquared() const
    {
        return X * X + Y * Y + Z * Z + W * W;
    }

    void Normalize()
    {
      float factor = Length();
      factor = 1.0f / factor;
      X *= factor;
      Y *= factor;
      Z *= factor;    
      W *= factor;    
    }


    Vector4& operator+=(const Vector4& arg) 
    { 
      X += arg.X;
      Y += arg.Y;
      Z += arg.Z;
      return *this;
    }

    Vector4& operator-=(const Vector4& arg) 
    { 
      X -= arg.X;
      Y -= arg.Y;
      Z -= arg.Z;
      return *this;
    }

    Vector4& operator*=(const Vector4& arg) 
    { 
      X *= arg.X;
      Y *= arg.Y;
      Z *= arg.Z;
      return *this;
    }

    Vector4& operator*=(const float arg) 
    { 
      X *= arg;
      Y *= arg;
      Z *= arg;
      return *this;
    }

    Vector4& operator*=(const int arg) 
    { 
      X *= arg;
      Y *= arg;
      Z *= arg;
      return *this;
    }

    static Vector4 Zero() { return Vector4(); }
    static Vector4 One() { return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }
  };


  namespace 
  {
    const Vector4 operator+(const Vector4& lhs, const Vector4& rhs) 
    { 
      return Vector4(lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z, lhs.W + rhs.W);
    }

    const Vector4 operator-(const Vector4& lhs, const Vector4& rhs) 
    { 
      return Vector4(lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z, lhs.W - rhs.W);
    }

    const Vector4 operator*(const Vector4& lhs, const Vector4& rhs) 
    { 
      return Vector4(lhs.X * rhs.X, lhs.Y * rhs.Y, lhs.Z * rhs.Z, lhs.W * rhs.W);
    }

    const Vector4 operator*(const Vector4& lhs, const float rhs) 
    { 
      return Vector4(lhs.X * rhs, lhs.Y * rhs, lhs.Z * rhs, lhs.W * rhs);
    }

    const Vector4 operator*(const float lhs, const Vector4& rhs) 
    { 
      return rhs * lhs;
    }

    const Vector4 operator*(const Vector4& lhs, const int rhs) 
    { 
      return Vector4(lhs.X * rhs, lhs.Y * rhs, lhs.Z * rhs, lhs.W * rhs);
    }

    const Vector4 operator*(const int lhs, const Vector4& rhs) 
    { 
      return rhs * lhs;
    }
  }
}

#endif
