#ifndef DFMC_BASE_MATH_MATRIX_HPP
#define DFMC_BASE_MATH_MATRIX_HPP
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

  struct Matrix
  {
    float mContent[4*4];
  public:
  
    Matrix();

    void SetIdentity();

    const float* GetRaw() const { return mContent; }
    float* DirectAccess() { return mContent; }

    Matrix& operator*=(const Matrix& arg);

    // @brief CreatePerspective matrix
    static const Matrix CreatePerspective(const float width, const float height, const float nearPlaneDistance, const float farPlaneDistance);
    static const Matrix CreatePerspectiveFieldOfView(const float fieldOfView, const float aspectRatio, const float nearPlaneDistance, const float farPlaneDistance);

    // @brief Create a orthographic projection matrix.
    static const Matrix CreateOrthographic(const float width, const float height, const float zNearPlane, const float zFarPlane);

    // @brief Create a matrix that rotates around the x-axis
    static const Matrix CreateRotationX(const float radians);

    // @brief Create a matrix that rotates around the y-axis
    static const Matrix CreateRotationY(const float radians);

    // @brief Create a matrix that rotates around the z-axis
    static const Matrix CreateRotationZ(const float radians);

    static const Matrix CreateTranslation(const float x, const float y, const float z);

    // @brief Transpose the given matrix (supports in place transpose, so srcMatrix can be equal to the rResult matrix)
    static void Transpose(const Matrix& srcMatrix, Matrix& rResult);

    static Matrix Identity() { return Matrix(); }
  };

  
  const Matrix operator*(const Matrix& lhs, const Matrix& rhs);
}

#endif
