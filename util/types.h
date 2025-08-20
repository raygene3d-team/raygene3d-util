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
#include <glm/gtc/round.hpp>
#include <glm/gtc/packing.hpp>
#include <glm/gtx/component_wise.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/polar_coordinates.hpp>


namespace RayGene3D
{
  //struct Raw;

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



  //struct Mesh
  //{
  //  Raw vtx_array;
  //  uint32_t vtx_count;
  //  Raw idx_array;
  //  uint32_t idx_count;
  //};



  //struct Mesh
  //{
  //  uint32_t buffer0;
  //  uint32_t buffer1;
  //  uint32_t buffer2;
  //  uint32_t buffer3;
  //  uint32_t buffer4;
  //  uint32_t buffer5;
  //  uint32_t buffer6;
  //  uint32_t buffer7;

  //  uint32_t texture0;
  //  uint32_t texture1;
  //  uint32_t texture2;
  //  uint32_t texture3;
  //  uint32_t texture4;
  //  uint32_t texture5;
  //  uint32_t texture6;
  //  uint32_t texture7;

  //  glm::f32vec4 parameter0;
  //  glm::f32vec4 parameter1;
  //  glm::f32vec4 parameter2;
  //  glm::f32vec4 parameter3;
  //  glm::f32vec4 parameter4;
  //  glm::f32vec4 parameter5;
  //  glm::f32vec4 parameter6;
  //  glm::f32vec4 parameter7;

  //  glm::f32vec3 bb_min;
  //  uint32_t geom_idx;
  //  glm::f32vec3 bb_max;
  //  uint32_t brdf_idx;
  //};

  //struct Scene
  //{
  //  std::vector<Mesh> meshes;
  //  std::vector<Buffer> buffers;
  //  std::vector<Texture> textures;
  //};




  struct Instance
  {
    glm::f32mat3x4 transform;

    uint32_t am_layer{ uint32_t(-1) }; // AM
    uint32_t snao_layer{ uint32_t(-1) }; // SNAO
    uint32_t et_layer{ uint32_t(-1) }; // ET
    uint32_t mask_layer{ uint32_t(-1) };

    uint32_t vert_offset{ 0u }; // vert_offset
    uint32_t vert_count{ 0u };  // vert_count
    uint32_t trng_offset{ 0u }; // prim_offset
    uint32_t trng_count{ 0u };  // prim_count
    uint32_t mlet_offset{ 0u }; // mlet_offset
    uint32_t mlet_count{ 0u };  // mlet_count
    uint32_t bone_offset{ 0u };
    uint32_t bone_count{ 0u };

    glm::f32vec3 aabb_min{ FLT_MAX, FLT_MAX, FLT_MAX };
    uint32_t index{ uint32_t(-1) };
    glm::f32vec3 aabb_max{-FLT_MAX,-FLT_MAX,-FLT_MAX };
    uint32_t flags{ 0 };

    glm::f32vec4 fparam_0{ 0.0f, 0.0f, 0.0f, 0.0f };
    glm::f32vec4 fparam_1{ 0.0f, 0.0f, 0.0f, 0.0f };
    glm::f32vec4 fparam_2{ 0.0f, 0.0f, 0.0f, 0.0f };
    glm::f32vec4 fparam_3{ 0.0f, 0.0f, 0.0f, 0.0f };

    glm::u32vec4 uparam_0{ 0u, 0u, 0u, 0u };
    glm::u32vec4 uparam_1{ 0u, 0u, 0u, 0u };
    glm::u32vec4 uparam_2{ 0u, 0u, 0u, 0u };
    glm::u32vec4 uparam_3{ 0u, 0u, 0u, 0u };
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
    glm::f32vec3 max{-FLT_MAX,-FLT_MAX,-FLT_MAX };
    uint32_t count{ 0 };
  };










  struct ReflectionProbeLevel
  {
    uint32_t level{ 0 };
    uint32_t size{ 0 };
    uint32_t dummy[62];
  };


  typedef std::pair<uint8_t*, size_t> ByteData;
  typedef std::pair<const uint8_t*, size_t> CByteData;

  class Raw
  {
  protected:
    ByteData _bytes{ nullptr, 0 };

  public:
    void Allocate(size_t size)
    {
      if (_bytes.first == nullptr && _bytes.second == 0 && size > 0u)
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

    //uint8_t* Data() const { return _bytes.first; }
    //size_t Size() const { return _bytes.second; }

    void SetBytes(CByteData bytes, size_t offset = 0u) const
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

    CByteData GetBytes(size_t offset = 0u) const
    {
      if (offset > _bytes.second)
      {
        throw std::runtime_error("get bytes failed");
      }

      return { _bytes.first + offset, _bytes.second - offset };
    }

    ByteData AccessBytes(size_t offset = 0) const
    {
      return { _bytes.first + offset, _bytes.second - offset };
    }


    template<typename T> void SetItems(std::pair<const T*, size_t> items, size_t offset = 0u)
    {
      if (offset * sizeof(T) > _bytes.second)
      {
        throw std::runtime_error("set items failed");
      }

      const auto item_data = reinterpret_cast<T*>(_bytes.first);
      const auto item_size = items.second * sizeof(T);

      std::memcpy(item_data + offset, items.first, item_size);
    }

    template<typename T> std::pair<const T*, size_t> GetItems(size_t offset = 0u) const
    {
      if (offset * sizeof(T) > _bytes.second)
      {
        throw std::runtime_error("get items failed");
      }

      const auto item_data = reinterpret_cast<const T*>(_bytes.first);
      const auto item_size = _bytes.second - sizeof(T) * offset;

      return { item_data + offset, item_size / sizeof(T) };
    }

    template<typename T> void SetItem(const T& item, size_t index)
    {
      if (index * sizeof(T) > _bytes.second)
      {
        throw std::runtime_error("set item failed");
      }

      reinterpret_cast<T*>(_bytes.first)[index] = item;
    }

    template<typename T> const T& GetItem(size_t index) const
    {
      if (index * sizeof(T) > _bytes.second)
      {
        throw std::runtime_error("get item failed");
      }

      return reinterpret_cast<T*>(_bytes.first)[index];
    }

    template<typename T> std::pair<T*, size_t> AccessItems(size_t offset = 0) const
    {
      return { reinterpret_cast<T*>(_bytes.first) + offset, _bytes.second / sizeof(T) - offset };
    }

    //template<typename T> T& operator[](size_t index) 
    //{
    //  return reinterpret_cast<T*>(_bytes.first)[index];
    //}

  public:
    Raw(size_t size = 0) { Allocate(size); }
    Raw(CByteData bytes) { Allocate(bytes.second); SetBytes(bytes); }
    template<typename T> Raw(size_t count, T value = {}) { Allocate(count * sizeof(T)); for (size_t i = 0; i < count; ++i) { SetItem(value, i); }}
    template<typename T> Raw(const std::pair<const T*, size_t>& items) { Allocate(items.second * sizeof(T)); SetItems(items); }

  public:
    Raw(const Raw& raw) = delete;
    Raw& operator=(const Raw& raw) = delete;
    Raw(Raw&& raw) noexcept { std::swap(raw._bytes, _bytes); }
    Raw& operator=(Raw&& raw) noexcept { std::swap(raw._bytes, _bytes); return *this; }
    ~Raw() { Free(); }
  };

  struct Meshlet
  {
    //uint32_t vert_offset : 24;
    //uint32_t vert_count : 8;
    //uint32_t trng_offset : 24;
    //uint32_t trng_count : 8;

    uint32_t vrt_offset;
    uint32_t vrt_count;
    uint32_t trg_offset;
    uint32_t trg_count;
  };

  struct Bone
  {
    glm::f32mat4x4 transform;
  };
}