#ifndef DFMC_BASE_MATH_VECTOR3_HPP
#define DFMC_BASE_MATH_VECTOR3_HPP
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

  struct Vector3
  {
  public:

    float X;
    float Y;
    float Z;

    Vector3() 
      : X(0.0f), Y(0.0f), Z(0.0f)
    {
    }

    Vector3(float x, float y, float z) 
      : X(x), Y(y), Z(z)
    {
    }

    float Length() const
    {
        return Math::Sqrt(LengthSquared());
    }

    float LengthSquared() const
    {
        return X * X + Y * Y + Z * Z;
    }

    void Normalize()
    {
      float factor = Length();
      factor = 1.0f / factor;
      X *= factor;
      Y *= factor;
      Z *= factor;    
    }


    static const Vector3 Cross(const Vector3& v1, const Vector3& v2)
    {
      return Vector3(v1.Y * v2.Z - v2.Y * v1.Z,
                     v1.X * v2.Z - v2.X * v1.Z,
                     v1.X * v2.Y - v2.X * v1.Y);
    }


    Vector3& operator+=(const Vector3& arg) 
    { 
      X += arg.X;
      Y += arg.Y;
      Z += arg.Z;
      return *this;
    }

    Vector3& operator-=(const Vector3& arg) 
    { 
      X -= arg.X;
      Y -= arg.Y;
      Z -= arg.Z;
      return *this;
    }

    Vector3& operator*=(const Vector3& arg) 
    { 
      X *= arg.X;
      Y *= arg.Y;
      Z *= arg.Z;
      return *this;
    }

    Vector3& operator*=(const float arg) 
    { 
      X *= arg;
      Y *= arg;
      Z *= arg;
      return *this;
    }

    Vector3& operator*=(const int arg) 
    { 
      X *= arg;
      Y *= arg;
      Z *= arg;
      return *this;
    }

    static Vector3 Zero() { return Vector3(); }
    static Vector3 One() { return Vector3(1.0f, 1.0f, 1.0f); }
  };


  namespace 
  {
    const Vector3 operator+(const Vector3& lhs, const Vector3& rhs) 
    { 
      return Vector3(lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z);
    }

    const Vector3 operator-(const Vector3& lhs, const Vector3& rhs) 
    { 
      return Vector3(lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z);
    }

    const Vector3 operator*(const Vector3& lhs, const Vector3& rhs) 
    { 
      return Vector3(lhs.X * rhs.X, lhs.Y * rhs.Y, lhs.Z * rhs.Z);
    }

    const Vector3 operator*(const Vector3& lhs, const float rhs) 
    { 
      return Vector3(lhs.X * rhs, lhs.Y * rhs, lhs.Z * rhs);
    }

    const Vector3 operator*(const float lhs, const Vector3& rhs) 
    { 
      return rhs * lhs;
    }

    const Vector3 operator*(const Vector3& lhs, const int rhs) 
    { 
      return Vector3(lhs.X * rhs, lhs.Y * rhs, lhs.Z * rhs);
    }

    const Vector3 operator*(const int lhs, const Vector3& rhs) 
    { 
      return rhs * lhs;
    }
  }
}

#endif
