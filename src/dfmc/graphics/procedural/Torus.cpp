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

#include <algorithm>
#include <vector>
#include <dfmc/graphics/render3D/DataTypes.hpp>
#include <dfmc/base/math/Math.hpp>
#include <dfmc/base/math/Vector2.hpp>
#include <dfmc/base/math/Vector3.hpp>
#include <dfmc/graphics/render3D/util/SimpleModel.hpp>
#include <dfmc/graphics/procedural/Torus.hpp>
#include <math.h>

namespace dfmc {
namespace procedural
{
  namespace 
  {
    static const std::vector<VertexPositionNormalTexture> GenerateVertices(int sides, int rings, float radius, float ringRadius, bool bInsideOut)
    {
      int numVerticesPerRow = sides + 1;
      int numVerticesPerColumn = rings + 1;

      int numVertices = numVerticesPerRow * numVerticesPerColumn;

      std::vector<VertexPositionNormalTexture> vertices(numVertices);

      float theta = 0.0f;
      float phi = 0.0f;

      float verticalAngularStride = (Math::PI * 2.0f) / rings;
      float horizontalAngularStride = (Math::PI * 2.0f) / sides;

      float ringsAdd = 1.0f / rings;
      float sidesAdd = 1.0f / sides;

      float mod = bInsideOut ? -1.0f : 1.0f;
      int vertexIndex = 0;
      for (int verticalIt = 0; verticalIt < numVerticesPerColumn; ++verticalIt)
      {
        theta = verticalAngularStride * verticalIt;

        for (int horizontalIt = 0; horizontalIt < numVerticesPerRow; ++horizontalIt)
        {
          phi = horizontalAngularStride * horizontalIt;

          // position
          float z = ringRadius * Math::Sin(phi);
          {
            float x = Math::Cos(theta)*(radius + ringRadius*Math::Cos(phi));
            float y = Math::Sin(theta)*(radius + ringRadius*Math::Cos(phi));

            vertices[vertexIndex].Position = Vector3(x, z, y);
          }
          // normal
          {
            float x = Math::Cos(theta) * (ringRadius * Math::Cos(phi));
            float y = Math::Sin(theta) * (ringRadius * Math::Cos(phi));

            Vector3 pos = Vector3(x * mod, z * mod, y * mod);
            pos.Normalize();
            vertices[vertexIndex].Normal = pos;
          }
          vertices[vertexIndex].TextureCoordinate = Vector2(-verticalIt * ringsAdd * 2 * mod, -horizontalIt * sidesAdd + 0.5f);
          ++vertexIndex;
        }
      }
      return vertices;
    }




    static const std::vector<int> GenerateIndices(int sides, int rings)
    {
      int numIndices = sides * rings * 6;
      std::vector<int> indices(numIndices);
      int numVerticesPerRow = sides + 1;
      //int numVerticesPerColumn = rings + 1;

      int index = 0;
      for (int verticalIt = 0; verticalIt < rings; ++verticalIt)
      {
        for (int horizontalIt = 0; horizontalIt < sides; ++horizontalIt)
        {
          int lt = ((horizontalIt + 0) + (verticalIt + 1) * (numVerticesPerRow));
          int rt = ((horizontalIt + 1) + (verticalIt + 1) * (numVerticesPerRow));

          int lb = ((horizontalIt + 0) + (verticalIt + 0) * (numVerticesPerRow));
          int rb = ((horizontalIt + 1) + (verticalIt + 0) * (numVerticesPerRow));

          indices[index] = rt;
          ++index;
          indices[index] = lt;
          ++index;
          indices[index] = lb;
          ++index;

          indices[index] = rb;
          ++index;
          indices[index] = rt;
          ++index;
          indices[index] = lb;
          ++index;
        }
      }
      return indices;
    }
  }

  SimpleModel Torus::Generate(const int sides, const int rings, const float radius, const float ringRadius, const bool bInsideOut)
  {
    const std::vector<VertexPositionNormalTexture> vertices = GenerateVertices(sides, rings, radius, ringRadius, bInsideOut);
    const std::vector<int> indices = GenerateIndices(sides, rings);

    // Util.GenerateNormals(vertices, indices);

    return SimpleModel(vertices, indices, PrimitiveType::TriangleList);
  }

}}
