/*================================================================================
RayGene3D Framework
--------------------------------------------------------------------------------
RayGene3D is licensed under MIT License
================================================================================
The MIT License
--------------------------------------------------------------------------------
Copyright (c) 2021

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
================================================================================*/


#pragma once
#include "../raygene3d-core/base.h"

#define GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/component_wise.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/round.hpp>

namespace RayGene3D
{
  struct Vertex
  {
    glm::f32vec3 pos{ 0.0f, 0.0f, 0.0f };
    float u{ 0.0f };
    glm::f32vec3 nrm{ 0.0f, 0.0f, 0.0f };
    float v{ 0.0f };
    glm::f32vec3 tgn{ 0.0f, 0.0f, 0.0f };
    float sign{ 0.0f };
  };

  struct Triangle
  {
    glm::u32vec3 idx{ uint32_t(-1), uint32_t(-1) , uint32_t(-1) };
  };

  struct Instance
  {
    glm::f32mat3x4 transform;

    glm::f32vec3 emission{ 0.0f, 0.0f, 0.0f }; // emission color
    float intensity{ 0.0f }; // emission intensity 
    glm::f32vec3 diffuse{ 0.0f, 0.0f, 0.0f }; // diffuse color
    float metallic{ 0.0f }; // metallic ratio (energy distribution between specular and diffuse) 
    glm::f32vec3 specular{ 0.0f, 0.0f, 0.0f }; // specular color
    float shininess{ 0.0f }; // roughness value (specular reflection coherency)
    glm::f32vec3 transmittance{ 0.0f, 0.0f, 0.0f }; // transmission color
    float ior{ 1.0f }; // refraction index (energy distribution upon transmission)

    uint32_t texture0_idx{ uint32_t(-1) };
    uint32_t texture1_idx{ uint32_t(-1) };
    uint32_t texture2_idx{ uint32_t(-1) };
    uint32_t texture3_idx{ uint32_t(-1) };

    glm::f32vec3 debug_color{ 0.0f, 0.0f, 0.0f };
    uint32_t geometry_idx{ uint32_t(-1) };


    uint32_t prim_offset{ 0 };
    uint32_t prim_count{ 0 };
    uint32_t vert_offset{ 0 };
    uint32_t vert_count{ 0 };

    glm::u32vec4 padding[6];
  };

  struct Screen
  {
    uint32_t extent_x{ 0 };
    uint32_t extent_y{ 0 };
    uint32_t rnd_base{ 0 };
    uint32_t rnd_seed{ 0 };
  };

  struct Frustum
  {
    glm::f32mat4x4 view{ 1.0f };
    glm::f32mat4x4 proj{ 1.0f };
    glm::f32mat4x4 view_inv{ 1.0f };
    glm::f32mat4x4 proj_inv{ 1.0f };
  };

  struct Box
  {
    glm::f32vec3 min{ FLT_MAX, FLT_MAX, FLT_MAX };
    uint32_t offset{ uint32_t(-1) };
    glm::f32vec3 max{ -FLT_MAX,-FLT_MAX,-FLT_MAX };
    uint32_t count{ 0 };
  };


  struct Texture
  {
    std::vector<glm::u8vec4> texels;
    uint32_t extent_x{ 0 };
    uint32_t extent_y{ 0 };
  };


  class Raw
  {
  protected:
    std::pair<uint8_t*, uint32_t> _bytes{ nullptr, 0 };

  public:
    void Allocate(uint32_t size)
    {
      if (_bytes.first != nullptr || _bytes.second != 0)
      {
        throw std::runtime_error("allocation failed");
      }

      _bytes.first = new uint8_t[size];
      _bytes.second = size;
    }

    void Free()
    {
      if (_bytes.first == nullptr || _bytes.second == 0)
      {
        throw std::runtime_error("freeing failed");
      }

      delete[] _bytes.first;
      _bytes = { nullptr, 0 };
    }

    void SetBytes(std::pair<const void*, uint32_t> bytes, uint32_t offset)
    {
      if (offset > _bytes.second)
      {
        throw std::runtime_error("set bytes failed");
      }

      if (bytes.first != nullptr && bytes.second + offset <= _bytes.second)
      {
        std::memcpy(_bytes.first + offset, bytes.first, bytes.second);
      }
    }

    std::pair<const void*, uint32_t> GetBytes(uint32_t offset) const
    {
      if (offset > _bytes.second)
      {
        throw std::runtime_error("get bytes failed");
      }

      return { _bytes.first + offset, _bytes.second - offset };
    }

  public:
    Raw() {}
    ~Raw() { Free(); }
  };
}

