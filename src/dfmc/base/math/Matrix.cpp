#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
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

#include <dfmc/base/math/Matrix.hpp>
#include <cassert>
#include <dfmc/base/math/Math.hpp>

namespace dfmc
{
  Matrix::Matrix()
  {
    SetIdentity();
  }


  void Matrix::SetIdentity()
  {
    mContent[0] = 1.0f; mContent[1] = 0.0f; mContent[2] = 0.0f; mContent[3] = 0.0f;
    mContent[4] = 0.0f; mContent[5] = 1.0f; mContent[6] = 0.0f; mContent[7] = 0.0f;
    mContent[8] = 0.0f; mContent[9] = 0.0f; mContent[10] = 1.0f; mContent[11] = 0.0f;
    mContent[12] = 0.0f; mContent[13] = 0.0f; mContent[14] = 0.0f; mContent[15] = 1.0f;
  }

  Matrix& Matrix::operator*=(const Matrix& rhs)
  {
    float m00 = (((mContent[4*0+0] * rhs.mContent[4*0+0]) + (mContent[4*0+1] * rhs.mContent[4*1+0]) + (mContent[4*0+2] * rhs.mContent[4*2+0])) + (mContent[4*0+3] * rhs.mContent[4*3+0]));
    float m01 = (((mContent[4*0+0] * rhs.mContent[4*0+1]) + (mContent[4*0+1] * rhs.mContent[4*1+1]) + (mContent[4*0+2] * rhs.mContent[4*2+1])) + (mContent[4*0+3] * rhs.mContent[4*3+1]));
    float m02 = (((mContent[4*0+0] * rhs.mContent[4*0+2]) + (mContent[4*0+1] * rhs.mContent[4*1+2]) + (mContent[4*0+2] * rhs.mContent[4*2+2])) + (mContent[4*0+3] * rhs.mContent[4*3+2]));
    float m03 = (((mContent[4*0+0] * rhs.mContent[4*0+3]) + (mContent[4*0+1] * rhs.mContent[4*1+3]) + (mContent[4*0+2] * rhs.mContent[4*2+3])) + (mContent[4*0+3] * rhs.mContent[4*3+3]));
    float m10 = (((mContent[4*1+0] * rhs.mContent[4*0+0]) + (mContent[4*1+1] * rhs.mContent[4*1+0]) + (mContent[4*1+2] * rhs.mContent[4*2+0])) + (mContent[4*1+3] * rhs.mContent[4*3+0]));
    float m11 = (((mContent[4*1+0] * rhs.mContent[4*0+1]) + (mContent[4*1+1] * rhs.mContent[4*1+1]) + (mContent[4*1+2] * rhs.mContent[4*2+1])) + (mContent[4*1+3] * rhs.mContent[4*3+1]));
    float m12 = (((mContent[4*1+0] * rhs.mContent[4*0+2]) + (mContent[4*1+1] * rhs.mContent[4*1+2]) + (mContent[4*1+2] * rhs.mContent[4*2+2])) + (mContent[4*1+3] * rhs.mContent[4*3+2]));
    float m13 = (((mContent[4*1+0] * rhs.mContent[4*0+3]) + (mContent[4*1+1] * rhs.mContent[4*1+3]) + (mContent[4*1+2] * rhs.mContent[4*2+3])) + (mContent[4*1+3] * rhs.mContent[4*3+3]));
    float m20 = (((mContent[4*2+0] * rhs.mContent[4*0+0]) + (mContent[4*2+1] * rhs.mContent[4*1+0]) + (mContent[4*2+2] * rhs.mContent[4*2+0])) + (mContent[4*2+3] * rhs.mContent[4*3+0]));
    float m21 = (((mContent[4*2+0] * rhs.mContent[4*0+1]) + (mContent[4*2+1] * rhs.mContent[4*1+1]) + (mContent[4*2+2] * rhs.mContent[4*2+1])) + (mContent[4*2+3] * rhs.mContent[4*3+1]));
    float m22 = (((mContent[4*2+0] * rhs.mContent[4*0+2]) + (mContent[4*2+1] * rhs.mContent[4*1+2]) + (mContent[4*2+2] * rhs.mContent[4*2+2])) + (mContent[4*2+3] * rhs.mContent[4*3+2]));
    float m23 = (((mContent[4*2+0] * rhs.mContent[4*0+3]) + (mContent[4*2+1] * rhs.mContent[4*1+3]) + (mContent[4*2+2] * rhs.mContent[4*2+3])) + (mContent[4*2+3] * rhs.mContent[4*3+3]));
    float m30 = (((mContent[4*3+0] * rhs.mContent[4*0+0]) + (mContent[4*3+1] * rhs.mContent[4*1+0]) + (mContent[4*3+2] * rhs.mContent[4*2+0])) + (mContent[4*3+3] * rhs.mContent[4*3+0]));
    float m31 = (((mContent[4*3+0] * rhs.mContent[4*0+1]) + (mContent[4*3+1] * rhs.mContent[4*1+1]) + (mContent[4*3+2] * rhs.mContent[4*2+1])) + (mContent[4*3+3] * rhs.mContent[4*3+1]));
    float m32 = (((mContent[4*3+0] * rhs.mContent[4*0+2]) + (mContent[4*3+1] * rhs.mContent[4*1+2]) + (mContent[4*3+2] * rhs.mContent[4*2+2])) + (mContent[4*3+3] * rhs.mContent[4*3+2]));
    float m33 = (((mContent[4*3+0] * rhs.mContent[4*0+3]) + (mContent[4*3+1] * rhs.mContent[4*1+3]) + (mContent[4*3+2] * rhs.mContent[4*2+3])) + (mContent[4*3+3] * rhs.mContent[4*3+3]));

    mContent[4*0 + 0] = m00;
    mContent[4*0 + 1] = m01;
    mContent[4*0 + 2] = m02;
    mContent[4*0 + 3] = m03;
    mContent[4*1 + 0] = m10;
    mContent[4*1 + 1] = m11;
    mContent[4*1 + 2] = m12;
    mContent[4*1 + 3] = m13;
    mContent[4*2 + 0] = m20;
    mContent[4*2 + 1] = m21;
    mContent[4*2 + 2] = m22;
    mContent[4*2 + 3] = m23;
    mContent[4*3 + 0] = m30;
    mContent[4*3 + 1] = m31;
    mContent[4*3 + 2] = m32;
    mContent[4*3 + 3] = m33;
    return *this;
  }

  const Matrix Matrix::CreatePerspective(const float width, const float height, const float nearPlaneDistance, const float farPlaneDistance)
  {
    assert(nearPlaneDistance > 0.0f);
    assert(farPlaneDistance > 0.0f);
    assert(nearPlaneDistance < farPlaneDistance);

    Matrix matrix;
    float* pContent = matrix.mContent;
    pContent[4*0+0] = (2.0f * nearPlaneDistance) / width;
    pContent[4*0+1] = 0.0f;
    pContent[4*0+2] = 0.0f;
    pContent[4*0+3] = 0.0f;
    pContent[4*1+0] = 0.0f;
    pContent[4*1+1] = (2.0f * nearPlaneDistance) / height;
    pContent[4*1+2] = 0.0f;
    pContent[4*1+3] = 0.0f;
    pContent[4*2+3] = -1.0f;
    pContent[4*2+0] = 0.0f;
    pContent[4*2+1] = 0.0f;
    pContent[4*2+2] = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
    pContent[4*3+0] = 0.0f;
    pContent[4*3+1] = 0.0f; 
    pContent[4*3+2] = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);
    pContent[4*3+3] = 0.0f;
    return matrix;
  }


  const Matrix Matrix::CreatePerspectiveFieldOfView(const float fieldOfView, const float aspectRatio, const float nearPlaneDistance, const float farPlaneDistance)
  {
    assert(fieldOfView >= 0.0f && fieldOfView <= Math::PI);
    assert(nearPlaneDistance > 0.0f);
    assert(farPlaneDistance > 0.0f);
    assert(nearPlaneDistance < farPlaneDistance);

    float f = 1.0f / Math::Tan(fieldOfView * 0.5f);

    Matrix matrix;
    float* pContent = matrix.mContent;

    pContent[4*0+0] = f / aspectRatio;
    pContent[4*0+1] = 0.0f;
    pContent[4*0+2] = 0.0f;
    pContent[4*0+3] = 0.0f;
    pContent[4*1+0] = 0.0f;
    pContent[4*1+1] = f;
    pContent[4*1+2] = 0.0f;
    pContent[4*1+3] = 0.0f;
    pContent[4*2+0] = 0.0f;
    pContent[4*2+1] = 0.0f;
    pContent[4*2+2] = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
    pContent[4*2+3] = -1.0f;
    pContent[4*3+0] = 0.0f;
    pContent[4*3+1] = 0.0f; 
    pContent[4*3+2] = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);
    pContent[4*3+3] = 0.0f;
    return matrix;
  }


  const Matrix Matrix::CreateOrthographic(const float width, const float height, const float zNearPlane, const float zFarPlane)
  {
    Matrix matrix;
		matrix.mContent[(4*0)+0] = 2.0f / width;
		matrix.mContent[(4*0)+1] = 0.0f;
    matrix.mContent[(4*0)+2] = 0.0f;
    matrix.mContent[(4*0)+3] = 0.0f;

		matrix.mContent[(4*1)+0] = 0.0f;
		matrix.mContent[(4*1)+1] = 2.0f / height;
    matrix.mContent[(4*1)+2] = 0.0f;
    matrix.mContent[(4*1)+3] = 0.0f;

    matrix.mContent[(4*2)+0] = 0.0f;
    matrix.mContent[(4*2)+1] = 0.0f;
		matrix.mContent[(4*2)+2] = 1.0f / (zNearPlane - zFarPlane);
    matrix.mContent[(4*2)+3] = 0.0f;

		matrix.mContent[(4*3)+0] = 0.0f;
		matrix.mContent[(4*3)+1] = 0.0f;
		matrix.mContent[(4*3)+2] = zNearPlane / (zNearPlane - zFarPlane);
		matrix.mContent[(4*3)+3] = 1.0f;
		return matrix;
  }


  const Matrix Matrix::CreateRotationX(const float radians)
  {
    Matrix result;

    const float val1 = Math::Cos(radians);
    const float val2 = Math::Sin(radians);
			
    result.mContent[(4*1)+1] = val1;
    result.mContent[(4*1)+2] = val2;
    result.mContent[(4*2)+1] = -val2;
    result.mContent[(4*2)+2] = val1;
    return result;
  }


  const Matrix Matrix::CreateRotationY(const float radians)
  {
    Matrix result;
			
    const float val1 = Math::Cos(radians);
    const float val2 = Math::Sin(radians);
			
    result.mContent[(4*0)+0] = val1;
    result.mContent[(4*0)+2] = -val2;
    result.mContent[(4*2)+0] = val2;
    result.mContent[(4*2)+2] = val1;
    return result;
  }


  const Matrix Matrix::CreateRotationZ(const float radians)
  {
    Matrix result;
			
    const float val1 = Math::Cos(radians);
    const float val2 = Math::Sin(radians);
			
    result.mContent[(4*0)+0] = val1;
    result.mContent[(4*0)+1] = val2;
    result.mContent[(4*1)+0] = -val2;
    result.mContent[(4*1)+1] = val1;
    return result;
  }


  const Matrix Matrix::CreateTranslation(const float x, const float y, const float z)
  {
    Matrix res;
    float* pRes = res.DirectAccess();

    pRes[4*0+0] = 1.0f;
    pRes[4*0+1] = 0.0f;
    pRes[4*0+2] = 0.0f;
    pRes[4*0+3] = 0.0f;
    pRes[4*1+0] = 0.0f;
    pRes[4*1+1] = 1.0f;
    pRes[4*1+2] = 0.0f;
    pRes[4*1+3] = 0.0f;
    pRes[4*2+0] = 0.0f;
    pRes[4*2+1] = 0.0f;
    pRes[4*2+2] = 1.0f;
    pRes[4*2+3] = 0.0f;
    pRes[4*3+0] = x;
    pRes[4*3+1] = y;
    pRes[4*3+2] = z;
    pRes[4*3+3] = 1.0f;
    return res;    
  }


  void Matrix::Transpose(const Matrix& srcMatrix, Matrix& rResult)
  {
    // Copy to the same position
    rResult.mContent[(4*0)+0] = srcMatrix.mContent[(4*0)+0];
    rResult.mContent[(4*1)+1] = srcMatrix.mContent[(4*1)+1];
    rResult.mContent[(4*2)+2] = srcMatrix.mContent[(4*2)+2];
    rResult.mContent[(4*3)+3] = srcMatrix.mContent[(4*3)+3];

    // We use the tmp variable to allow in place transpose
    float tmp;
    tmp = srcMatrix.mContent[(4*0)+1];
    rResult.mContent[(4*0)+1] = srcMatrix.mContent[(4*1)+0];
    rResult.mContent[(4*1)+0] = tmp;

    tmp = srcMatrix.mContent[(4*0)+2];
    rResult.mContent[(4*0)+2] = srcMatrix.mContent[(4*2)+0];
    rResult.mContent[(4*2)+0] = tmp;

    tmp = srcMatrix.mContent[(4*0)+3];
    rResult.mContent[(4*0)+3] = srcMatrix.mContent[(4*3)+0];
    rResult.mContent[(4*3)+0] = tmp;

    tmp = srcMatrix.mContent[(4*1)+2];
    rResult.mContent[(4*1)+2] = srcMatrix.mContent[(4*2)+1];
    rResult.mContent[(4*2)+1] = tmp;

    tmp = srcMatrix.mContent[(4*1)+3];
    rResult.mContent[(4*1)+3] = srcMatrix.mContent[(4*3)+1];
    rResult.mContent[(4*3)+1] = tmp;

    tmp = srcMatrix.mContent[(4*2)+3];
    rResult.mContent[(4*2)+3] = srcMatrix.mContent[(4*3)+2];
    rResult.mContent[(4*3)+2] = tmp;
  }


  const Matrix operator*(const Matrix& lhs, const Matrix& rhs)
  {
    Matrix res;
    float* pRes = res.DirectAccess();

    pRes[4*0+0] = (((lhs.mContent[4*0+0] * rhs.mContent[4*0+0]) + (lhs.mContent[4*0+1] * rhs.mContent[4*1+0]) + (lhs.mContent[4*0+2] * rhs.mContent[4*2+0])) + (lhs.mContent[4*0+3] * rhs.mContent[4*3+0]));
    pRes[4*0+1] = (((lhs.mContent[4*0+0] * rhs.mContent[4*0+1]) + (lhs.mContent[4*0+1] * rhs.mContent[4*1+1]) + (lhs.mContent[4*0+2] * rhs.mContent[4*2+1])) + (lhs.mContent[4*0+3] * rhs.mContent[4*3+1]));
    pRes[4*0+2] = (((lhs.mContent[4*0+0] * rhs.mContent[4*0+2]) + (lhs.mContent[4*0+1] * rhs.mContent[4*1+2]) + (lhs.mContent[4*0+2] * rhs.mContent[4*2+2])) + (lhs.mContent[4*0+3] * rhs.mContent[4*3+2]));
    pRes[4*0+3] = (((lhs.mContent[4*0+0] * rhs.mContent[4*0+3]) + (lhs.mContent[4*0+1] * rhs.mContent[4*1+3]) + (lhs.mContent[4*0+2] * rhs.mContent[4*2+3])) + (lhs.mContent[4*0+3] * rhs.mContent[4*3+3]));
    pRes[4*1+0] = (((lhs.mContent[4*1+0] * rhs.mContent[4*0+0]) + (lhs.mContent[4*1+1] * rhs.mContent[4*1+0]) + (lhs.mContent[4*1+2] * rhs.mContent[4*2+0])) + (lhs.mContent[4*1+3] * rhs.mContent[4*3+0]));
    pRes[4*1+1] = (((lhs.mContent[4*1+0] * rhs.mContent[4*0+1]) + (lhs.mContent[4*1+1] * rhs.mContent[4*1+1]) + (lhs.mContent[4*1+2] * rhs.mContent[4*2+1])) + (lhs.mContent[4*1+3] * rhs.mContent[4*3+1]));
    pRes[4*1+2] = (((lhs.mContent[4*1+0] * rhs.mContent[4*0+2]) + (lhs.mContent[4*1+1] * rhs.mContent[4*1+2]) + (lhs.mContent[4*1+2] * rhs.mContent[4*2+2])) + (lhs.mContent[4*1+3] * rhs.mContent[4*3+2]));
    pRes[4*1+3] = (((lhs.mContent[4*1+0] * rhs.mContent[4*0+3]) + (lhs.mContent[4*1+1] * rhs.mContent[4*1+3]) + (lhs.mContent[4*1+2] * rhs.mContent[4*2+3])) + (lhs.mContent[4*1+3] * rhs.mContent[4*3+3]));
    pRes[4*2+0] = (((lhs.mContent[4*2+0] * rhs.mContent[4*0+0]) + (lhs.mContent[4*2+1] * rhs.mContent[4*1+0]) + (lhs.mContent[4*2+2] * rhs.mContent[4*2+0])) + (lhs.mContent[4*2+3] * rhs.mContent[4*3+0]));
    pRes[4*2+1] = (((lhs.mContent[4*2+0] * rhs.mContent[4*0+1]) + (lhs.mContent[4*2+1] * rhs.mContent[4*1+1]) + (lhs.mContent[4*2+2] * rhs.mContent[4*2+1])) + (lhs.mContent[4*2+3] * rhs.mContent[4*3+1]));
    pRes[4*2+2] = (((lhs.mContent[4*2+0] * rhs.mContent[4*0+2]) + (lhs.mContent[4*2+1] * rhs.mContent[4*1+2]) + (lhs.mContent[4*2+2] * rhs.mContent[4*2+2])) + (lhs.mContent[4*2+3] * rhs.mContent[4*3+2]));
    pRes[4*2+3] = (((lhs.mContent[4*2+0] * rhs.mContent[4*0+3]) + (lhs.mContent[4*2+1] * rhs.mContent[4*1+3]) + (lhs.mContent[4*2+2] * rhs.mContent[4*2+3])) + (lhs.mContent[4*2+3] * rhs.mContent[4*3+3]));
    pRes[4*3+0] = (((lhs.mContent[4*3+0] * rhs.mContent[4*0+0]) + (lhs.mContent[4*3+1] * rhs.mContent[4*1+0]) + (lhs.mContent[4*3+2] * rhs.mContent[4*2+0])) + (lhs.mContent[4*3+3] * rhs.mContent[4*3+0]));
    pRes[4*3+1] = (((lhs.mContent[4*3+0] * rhs.mContent[4*0+1]) + (lhs.mContent[4*3+1] * rhs.mContent[4*1+1]) + (lhs.mContent[4*3+2] * rhs.mContent[4*2+1])) + (lhs.mContent[4*3+3] * rhs.mContent[4*3+1]));
    pRes[4*3+2] = (((lhs.mContent[4*3+0] * rhs.mContent[4*0+2]) + (lhs.mContent[4*3+1] * rhs.mContent[4*1+2]) + (lhs.mContent[4*3+2] * rhs.mContent[4*2+2])) + (lhs.mContent[4*3+3] * rhs.mContent[4*3+2]));
    pRes[4*3+3] = (((lhs.mContent[4*3+0] * rhs.mContent[4*0+3]) + (lhs.mContent[4*3+1] * rhs.mContent[4*1+3]) + (lhs.mContent[4*3+2] * rhs.mContent[4*2+3])) + (lhs.mContent[4*3+3] * rhs.mContent[4*3+3]));
    return res;
  }

}
