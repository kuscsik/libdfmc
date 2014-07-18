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

#include <cassert>
#include <vector>
#include <dfmc/graphics/render3D/DataTypes.hpp>
#include <dfmc/graphics/procedural/Quad.hpp>

namespace dfmc {
namespace procedural
{
  namespace
  {
    const std::vector<VertexPositionNormalTexture> GenerateVertices(const int verticesX, const int verticesY, const Rect& dstRect, const float zPos, const TextureArea& textureArea, bool bForwardNormal)
    {
      const int numVertices = verticesX * verticesY;
      
      std::vector<VertexPositionNormalTexture> vertices(numVertices);

      const float xAdd = dstRect.Width() / (float)(verticesX-1);
      const float yAdd = -dstRect.Height() / (float)(verticesY-1);

      const float xStart = dstRect.Left();
      float yPos = dstRect.Bottom();

      Vector3 zNormal(0.0f, 0.0f, bForwardNormal ? 1.0f : -1.0f);

      const float uStart = textureArea.X1();
      const float uEnd = textureArea.X2();
      const float vStart = textureArea.Y1();
      const float vEnd = textureArea.Y2();
      float u;
      float v = vStart;
      float uAdd = (uEnd - uStart) / (verticesX-1);
      float vAdd = (vEnd - vStart) / (verticesY-1);

      int i = 0;
      float xPos;
      for (int y = 0; y < verticesY; ++y)
      {
        u = uStart;
        xPos = xStart;
        for (int x = 0; x < verticesX; ++x)
        {
          // FIX: ensure that both vEnd and uEnd are used (since we might have precision errors on the interpolated values)
          vertices[i].Position = Vector3(xPos, yPos, zPos);
          vertices[i].Normal = zNormal;
          vertices[i].TextureCoordinate = Vector2(u, v);

          xPos += xAdd;
          u += uAdd;
          ++i;
        }
        yPos += yAdd;
        v += vAdd;
      }
      return vertices;
    }

    const std::vector<int> GenerateTriangleListIndices(const int verticesX, const int verticesY, const WindingOrder::Enum windingOrder)
    {
      // *-*-*
      // |\|\|
      // *-*-*
      // |\|\|
      // *-*-*

      int numX = verticesX - 1;
      int numY = verticesY - 1;

      int numIndices = numX * numY * 6;
      std::vector<int> indices(numIndices);

      const int i0 = (windingOrder == WindingOrder::CW ? 0 : 1);
      const int i1 = (windingOrder == WindingOrder::CW ? 1 : 0);

      int i = 0;
      int yOffset = 0;
      for (int y = 0; y < numY; ++y)
      {
        for (int x = 0; x < numX; ++x)
        {
          indices[i + i0] = yOffset + (x + verticesX);
          indices[i + i1] = yOffset + x;
          indices[i + 2] = yOffset + (x + verticesX + 1);

          indices[i + i0 + 3] = yOffset + (x + verticesX + 1);
          indices[i + i1 + 3] = yOffset + x;
          indices[i + 5] = yOffset + x + 1;
          i += 6;
        }
        yOffset += verticesX;
      }

      return indices;
    }

    const std::vector<int> GenerateTriangleStripIndices(const int verticesX, const int verticesY, const WindingOrder::Enum windingOrder)
    {
      // Generate a quad mesh with the desired vertices (CW).
      //          A  |B  |C  |D  |E* |F* |G  |H  |I  |J  |K* |L* |M  |N  |O  |P
      //          ---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---
      // 0-1-2    0  |0-1|1  |1-2|  2|  2|   |   |   |   |   |   |   |   |   |
      // |\|\|    |\ | \|||\ | \||  ||  ||   |   |   |   |   |   |   |   |   |
      // 3-4-5 -> 3-4|  4|4-5|  5|  5|  5|4-5|4  |3-4|3  |3  |   |   |   |   |
      // |\|\|       |   |   |   |   |  || \|||\ | \|||\ ||  |   |   |   |   |
      // 6-7-8       |   |   |   |   |  8|  8|7-8|  7|6-7|6  |6  |6  |6-7|7  |7-8
      // |\|\|       |   |   |   |   |   |   |   |   |   ||  ||  ||\ | \|||\ | \|
      // 9-A-B       |   |   |   |   |   |   |   |   |   |9  |9  |9-A|  A|A-B|  B
      //                       
      // *= Degenerated triangle 
      //
      // Triangle indices (CW)
      // - Top         A: 3,0,4 cw|B: 0,4,1 ccw|C: 4,1,5 cw|D: 1,5,2 ccw
      // - Degenerated E: 5,2,5 cw|F: 2,5,8 ccw|                         (always two)
      // - Middle      G: 5,8,4 cw|H: 8,4,7 ccw|I: 4,7,3 cw|J: 7,3,6 ccw
      // - Degenerated K: 3,6,9 cw|L: 6,9,6 ccw|                         (always two)
      // - Bottom      M: 9,6,A cw|N: 6,A,7 ccw|O: A,7,B cw|P: 7,B,8 ccw

      // Generate a quad mesh with the desired vertices (CCW).
      //          A  |B  |C  |D  |E* |F* |G  |H  |I  |J  |K* |L* |M  |N  |O  |P
      //          ---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---
      // 0-1-2    0-1|  1|1-2|  2|  2|   |   |   |   |   |   |   |   |   |   |
      // |/|/|    |/ | /|||/ | /||  ||   |   |   |   |   |   |   |   |   |   |
      // 3-4-5 -> 3  |3-4|4  |4-5|  5|  5|  5|4-5|  4|3-4|3  |3  |   |   |   |
      // |/|/|       |   |   |   |  ||  || /|||/ | /|||/ ||  ||  |   |   |   |
      // 6-7-8       |   |   |   |  8|  8|7-8|7  |6-7|6  |6  |6  |6-7|  7|7-8|  8
      // |/|/|       |   |   |   |   |   |   |   |   |   |   ||  ||/ | /|||/ | /|
      // 9-A-B       |   |   |   |   |   |   |   |   |   |   |9  |9  |9-A|A  |A_B
      //                       
      // *= degenerated triangle 
      //
      // Triangle indices (CW)
      // - Top         A: 0,3,1 ccw|B: 3,1,4 cw|C: 1,4,2 ccw|D: 4,2,5 cw
      // - Degenerated E: 2,5,8 ccw|F: 5,8,5 cw|                         (always two)
      // - Middle      G: 8,5,7 ccw|H: 5,7,4 cw|I: 7,4,6 ccw|J: 4,6,3 cw
      // - Degenerated K: 6,3,6 ccw|L: 3,6,9 cw|                         (always two)
      // - Bottom      M: 6,9,7 ccw|N: 9,7,A cw|O: 7,A,8 ccw|P: A,8,B cw

      const int segmentsX = verticesX - 1;
      const int segmentsY = verticesY - 1;
      const int indexCount = 2 + (segmentsX * segmentsY * 2) + (verticesY - 2) * 2;

      //
      assert(verticesX >= 0);
      assert(segmentsY >= 0);
      assert(indexCount >= 0);
      std::vector<int> indices(indexCount);

      // Generate the indices for a long triangle strips relying on two degenerated triangles for y-line switching.
      const int yOffset = verticesX;

      int dstIndex = 0;
      int offset = 0;

      const int i0 = (windingOrder == WindingOrder::CW ? 0 : 1);
      const int i1 = (windingOrder == WindingOrder::CW ? 1 : 0);


      indices[dstIndex + i0] = yOffset;
      indices[dstIndex + i1] = 0;
      dstIndex += 2;

      for (int y = 0; y < segmentsY; ++y)
      {
        if ((y & 1) == 0)
        {
          for (int x = 0; x < segmentsX; ++x)
          {
            indices[dstIndex + i0] = (offset + yOffset + x + 1);
            indices[dstIndex + i1] = (offset + x + 1);
            dstIndex += 2;
          }
          // Add two degenerated triangles for y-line switching if there are more rows
          if ((y + 1) < segmentsY)
          {
            indices[dstIndex + i0] = (offset + yOffset + segmentsX);
            indices[dstIndex + i1] = (offset + yOffset + segmentsX) + yOffset;
            dstIndex += 2;
          }
        }
        else
        {
          for (int x = segmentsX-1; x >= 0; --x)
          {
            indices[dstIndex + i0] = (offset) + x ;
            indices[dstIndex + i1] = (offset + yOffset + x);
            dstIndex += 2;
          }
          // Add two degenerated triangles for y-line switching if there are more rows
          if ((y + 1) < segmentsY)
          {
            indices[dstIndex + i0] = (offset + 2 * yOffset);
            indices[dstIndex + i1] = (offset + yOffset);
            dstIndex += 2;
          }
        }
        offset += yOffset;
      }
      return indices;
    }
  }



  const SimpleModel Quad::Generate(const int verticesX, const int verticesY, const Rect& dstRect, const float zPos, const TextureArea& textureArea, const bool bForwardNormal, const WindingOrder::Enum windingOrder)
  {
    const std::vector<VertexPositionNormalTexture> vertices = GenerateVertices(verticesX, verticesY, dstRect, zPos, textureArea, bForwardNormal);
    const std::vector<int> indices = GenerateTriangleListIndices(verticesX, verticesY, windingOrder);
    return SimpleModel(vertices, indices, PrimitiveType::TriangleList);
  }


  const SimpleModel Quad::Generate(const int verticesX, const int verticesY, const int width, const int height, const Vector3& center, const TextureArea& textureArea, const bool bForwardNormal, const WindingOrder::Enum windingOrder)
  {
    const float x = center.X - (width / 2.0f);
    const float y = center.Y - (height / 2.0f);
    const Rect dstRect(x, y, x + width, y + height, true);
    return Generate(verticesX, verticesY, dstRect, center.Z, textureArea, bForwardNormal, windingOrder);
  }


  const SimpleModel Quad::GenerateStrip(const int verticesX, const int verticesY, const Rect& dstRect, const float zPos, const TextureArea& textureArea, const bool bForwardNormal, const WindingOrder::Enum windingOrder)
  {
    const std::vector<VertexPositionNormalTexture> vertices = GenerateVertices(verticesX, verticesY, dstRect, zPos, textureArea, bForwardNormal);
    const std::vector<int> indices = GenerateTriangleStripIndices(verticesX, verticesY, windingOrder);
    return SimpleModel(vertices, indices, PrimitiveType::TriangleStrip);
  }


  const SimpleModel Quad::GenerateStrip(const int verticesX, const int verticesY, const int width, const int height, const Vector3& center, const TextureArea& textureArea, const bool bForwardNormal, const WindingOrder::Enum windingOrder)
  {
    const float x = center.X - (width / 2.0f);
    const float y = center.Y - (height / 2.0f);
    const Rect dstBox(x, y, x + width, y + height, true);
    return GenerateStrip(verticesX, verticesY, dstBox, center.Z, textureArea, bForwardNormal, windingOrder);
  }
}}
