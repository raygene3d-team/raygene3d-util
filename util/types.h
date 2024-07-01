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
#include "../../raygene3d-wrap/base.h"

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
#include <glm/gtx/polar_coordinates.hpp>
#include <glm/gtc/round.hpp>

namespace RayGene3D
{
  //struct Vertex
  //{
  //  glm::f32vec3 pos{ 0.0f, 0.0f, 0.0f };
  //  float u{ 0.0f };
  //  glm::f32vec3 nrm{ 0.0f, 0.0f, 0.0f };
  //  float v{ 0.0f };
  //  glm::f32vec3 tgn{ 0.0f, 0.0f, 0.0f };
  //  float sign{ 0.0f };
  //};

  struct Vertex
  {
    glm::f32vec3 pos{ 0.0f, 0.0f, 0.0f };
    glm::u8vec4 col{ 0u, 0u, 0u, 0u };
    glm::f32vec3 nrm{ 0.0f, 0.0f, 0.0f };
    uint32_t msk{ uint32_t(-1) };
    glm::f32vec3 tng{ 0.0f, 0.0f, 0.0f };
    float sgn{ 0.0f };
    glm::f32vec2 tc0{ 0.0f, 0.0f };
    glm::f32vec2 tc1{ 0.0f, 0.0f };
  };

  //struct Vertex0
  //{
  //  glm::f32vec3 pos{ 0.0f, 0.0f, 0.0f };
  //  glm::u8vec4 col{ 0u, 0u, 0u, 0u };
  //};

  //struct Vertex1
  //{
  //  glm::f32vec3 nrm{ 0.0f, 0.0f, 0.0f };
  //  uint32_t msk{ 0u };
  //};

  //struct Vertex2
  //{
  //  glm::f32vec3 tng{ 0.0f, 0.0f, 0.0f };
  //  float sgn{ 0.0f };
  //};

  //struct Vertex3
  //{
  //  glm::f32vec2 tc0{ 0.0f, 0.0f };
  //  glm::f32vec2 tc1{ 0.0f, 0.0f };
  //};

  struct Triangle
  {
    glm::u32vec3 idx{ uint32_t(-1), uint32_t(-1) , uint32_t(-1) };
  };

  struct Instance
  {
    glm::f32mat3x4 transform;

    uint32_t prim_offset{ 0 };
    uint32_t prim_count{ 0 };
    uint32_t vert_offset{ 0 };
    uint32_t vert_count{ 0 };

    glm::f32vec3 emission{ 0.0f, 0.0f, 0.0f }; // emission color
    float intensity{ 0.0f }; // emission intensity 
    glm::f32vec3 diffuse{ 1.0f, 1.0f, 1.0f }; // diffuse color
    float shininess{ 0.0f }; // specular coherency
    glm::f32vec3 specular{ 0.0f, 0.0f, 0.0f }; // specular color
    float alpha{ 1.0f }; // transparency or ior

    uint32_t texture0_idx{ uint32_t(-1) };
    uint32_t texture1_idx{ uint32_t(-1) };
    uint32_t texture2_idx{ uint32_t(-1) };
    uint32_t texture3_idx{ uint32_t(-1) };

    glm::f32vec3 debug_color{ 0.0f, 0.0f, 0.0f };
    uint32_t geometry_idx{ uint32_t(-1) };

    glm::f32vec3 bb_min{ FLT_MAX, FLT_MAX, FLT_MAX };
    uint32_t bb_min_padding{ 0 };
    glm::f32vec3 bb_max{-FLT_MAX,-FLT_MAX,-FLT_MAX };
    uint32_t bb_max_padding{ 0 };

    glm::u32vec4 padding[5];
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










  struct ReflectionProbeLevel
  {
    uint32_t level{ 0 };
    uint32_t size{ 0 };
    uint32_t dummy[62];
  };

  class Raw
  {
  protected:
    std::pair<void*, uint32_t> _bytes{ nullptr, 0 };

  public:
    void Allocate(uint32_t size)
    {
      if (_bytes.first == nullptr && _bytes.second == 0 && size != 0u)
      {
        _bytes.first = new uint8_t[size];
        _bytes.second = size;
      }      
    }

    void Free()
    {
      if (_bytes.first != nullptr && _bytes.second != 0)
      {
        delete[] _bytes.first;
        _bytes = { nullptr, 0 };
      }
    }

    void SetBytes(std::pair<const void*, uint32_t> bytes, uint32_t offset = 0u) const
    {
      if (offset > _bytes.second)
      {
        throw std::runtime_error("set bytes failed");
      }

      if (bytes.first != nullptr && bytes.second + offset <= _bytes.second)
      {
        std::memcpy(reinterpret_cast<uint8_t*>(_bytes.first) + offset, bytes.first, bytes.second);
      }
    }
 
    std::pair<const void*, uint32_t> GetBytes(uint32_t offset = 0u) const
    {
      if (offset > _bytes.second)
      {
        throw std::runtime_error("get bytes failed");
      }

      return { reinterpret_cast<uint8_t*>(_bytes.first) + offset, _bytes.second - offset };
    }

    template<typename T> void SetElements(std::pair<const T*, uint32_t> elements, uint32_t offset = 0u)
    {
      if (offset * uint32_t(sizeof(T)) > _bytes.second)
      {
        throw std::runtime_error("set elements failed");
      }

      const auto element_data = reinterpret_cast<T*>(_bytes.first);
      const auto element_size = elements.second * uint32_t(sizeof(T));

      std::memcpy(element_data + offset, elements.first, element_size);
    }

    template<typename T> std::pair<const T*, uint32_t> GetElements(uint32_t offset = 0u)
    {
      if (offset * uint32_t(sizeof(T)) > _bytes.second)
      {
        throw std::runtime_error("get elements failed");
      }

      const auto element_data = reinterpret_cast<const T*>(_bytes.first);
      const auto element_size = _bytes.second - uint32_t(sizeof(T)) * offset;

      return { element_data + offset, element_size / uint32_t(sizeof(T)) };
    }

    template<typename T> void SetElement(const T& element, uint32_t index)
    {
      if (index * uint32_t(sizeof(T)) > _bytes.second)
      {
        throw std::runtime_error("set element failed");
      }

      reinterpret_cast<T*>(_bytes.first)[index] = element;
    }

    template<typename T> const T& GetElement(uint32_t index)
    {
      if (index * uint32_t(sizeof(T)) > _bytes.second)
      {
        throw std::runtime_error("get element failed");
      }

      return reinterpret_cast<T*>(_bytes.first)[index];
    }

    template<typename T> void SetElement(T&& element, uint32_t index)
    {
      if (index * uint32_t(sizeof(T)) > _bytes.second)
      {
        throw std::runtime_error("set element failed");
      }

      reinterpret_cast<T*>(_bytes.first)[index] = element;
    }

    template<typename T> T&& GetElement(uint32_t index)
    {
      if (index * uint32_t(sizeof(T)) > _bytes.second)
      {
        throw std::runtime_error("get element failed");
      }

      return reinterpret_cast<T*>(_bytes.first)[index];
    }

    std::pair<void*, uint32_t> AccessBytes() const
    {
      return _bytes;
    }

    //void CommitBytes(std::pair<uint8_t*, uint32_t>&& bytes) { _bytes = bytes; }
    //std::pair<uint8_t*, uint32_t>&& RetrieveBytes() { return std::move(_bytes); }

  public:
    Raw(uint32_t size = 0) { Allocate(size); }
    Raw(const std::pair<const void*, uint32_t>& bytes) { Allocate(bytes.second); SetBytes(bytes); }
    //Raw(std::pair<void*, uint32_t>&& bytes) noexcept { std::swap(bytes, _bytes); }
    ~Raw() { Free(); }
    Raw(const Raw& raw) = delete;
    Raw& operator=(const Raw& raw) = delete;
    Raw(Raw&& raw) noexcept
    { 
      std::swap(raw._bytes, _bytes);
    }
    Raw& operator=(Raw&& raw) noexcept
    { 
      std::swap(raw._bytes, _bytes); 
      return *this;
    }
  };


  struct Texture
  {
    Raw texels;
    uint32_t extent_x{ 0 };
    uint32_t extent_y{ 0 };
  };

  struct Buffer
  {
    Raw bytes;
    uint32_t stride{ 0 };
    uint32_t offset{ 0 };
  };
}

