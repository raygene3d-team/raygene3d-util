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

    uint32_t layer_0{ uint32_t(-1) }; // texture_0
    uint32_t layer_1{ uint32_t(-1) }; // texture_1
    uint32_t layer_2{ uint32_t(-1) }; // texture_2
    uint32_t layer_3{ uint32_t(-1) }; // texture_3

    uint32_t offset_0{ 0u }; // vert_offset
    uint32_t count_0{ 0u }; // vert_count
    uint32_t offset_1{ 0u }; // prim_offset
    uint32_t count_1{ 0u }; // prim_count
    uint32_t offset_2{ 0u }; // bone_offset
    uint32_t count_2{ 0u }; // bone_count
    uint32_t offset_3{ 0u }; // mlet_offset
    uint32_t count_3{ 0u }; // mlet_count

    glm::f32vec3 aabb_min{ FLT_MAX, FLT_MAX, FLT_MAX };
    uint32_t geom_idx{ uint32_t(-1) };
    glm::f32vec3 aabb_max{-FLT_MAX,-FLT_MAX,-FLT_MAX };
    uint32_t brdf_idx{ uint32_t(-1) };

    glm::f32vec4 param_0;
    glm::f32vec4 param_1;
    glm::f32vec4 param_2;
    glm::f32vec4 param_3;

    glm::u32vec4 padding_0;
    glm::u32vec4 padding_1;
    glm::u32vec4 padding_2;
    glm::u32vec4 padding_3;
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


  //template<typename T = uint8_t>
  class Raw
  {
  protected:
    std::pair<uint8_t*, size_t> _bytes{ nullptr, 0 };

  public:
    void Allocate(size_t size)
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

    void SetBytes(std::pair<const uint8_t*, size_t> bytes, size_t offset = 0u) const
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

    std::pair<const uint8_t*, size_t> GetBytes(size_t offset = 0u) const
    {
      if (offset > _bytes.second)
      {
        throw std::runtime_error("get bytes failed");
      }

      return { _bytes.first + offset, _bytes.second - offset };
    }

    template<typename T> void SetElements(std::pair<const T*, size_t> elements, size_t offset = 0u)
    {
      if (offset * sizeof(T) > _bytes.second)
      {
        throw std::runtime_error("set elements failed");
      }

      const auto element_data = reinterpret_cast<T*>(_bytes.first);
      const auto element_size = elements.second * sizeof(T);

      std::memcpy(element_data + offset, elements.first, element_size);
    }

    template<typename T> std::pair<const T*, size_t> GetElements(size_t offset = 0u) const
    {
      if (offset * sizeof(T) > _bytes.second)
      {
        throw std::runtime_error("get elements failed");
      }

      const auto element_data = reinterpret_cast<const T*>(_bytes.first);
      const auto element_size = _bytes.second - sizeof(T) * offset;

      return { element_data + offset, element_size / sizeof(T) };
    }

    template<typename T> void SetElement(const T& element, size_t index)
    {
      if (index * sizeof(T) > _bytes.second)
      {
        throw std::runtime_error("set element failed");
      }

      reinterpret_cast<T*>(_bytes.first)[index] = element;
    }

    template<typename T> const T& GetElement(size_t index) const
    {
      if (index * sizeof(T) > _bytes.second)
      {
        throw std::runtime_error("get element failed");
      }

      return reinterpret_cast<T*>(_bytes.first)[index];
    }

    template<typename T> void SetElement(T&& element, size_t index)
    {
      if (index * sizeof(T) > _bytes.second)
      {
        throw std::runtime_error("set element failed");
      }

      reinterpret_cast<T*>(_bytes.first)[index] = std::move(element);
    }

    template<typename T> T&& GetElement(size_t index)
    {
      if (index * sizeof(T) > _bytes.second)
      {
        throw std::runtime_error("get element failed");
      }

      return std::move(reinterpret_cast<T*>(_bytes.first)[index]);
    }

    std::pair<uint8_t*, size_t> AccessBytes(size_t offset = 0) const
    {
      return { _bytes.first + offset, _bytes.second - offset };
    }

    template<typename T> std::pair<T*, size_t> AccessElements(size_t offset = 0) const
    {
      return { reinterpret_cast<T*>(_bytes.first) + offset, _bytes.second / sizeof(T) - offset };
    }

    //void CommitBytes(std::pair<uint8_t*, uint32_t>&& bytes) { _bytes = bytes; }
    //std::pair<uint8_t*, uint32_t>&& RetrieveBytes() { return std::move(_bytes); }

  public:
    Raw(size_t size = 0) { Allocate(size); }
    Raw(const std::pair<const uint8_t*, size_t>& bytes) { Allocate(bytes.second); SetBytes(bytes); }
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


  class TextureLDR
  {
    Raw raw;
    uint32_t extent_x;
    uint32_t extent_y;
    size_t mipmap;

  public:
    void Load(const std::string& name);
    void Save(const std::string& name);
    void Assemble(std::function<glm::u8vec4(uint32_t, uint32_t)> texels_fn);

  public:
    void SetRaw(Raw&& raw) { this->raw = std::move(raw); }
    Raw GetRaw() { return std::move(this->raw); }

  public:
    TextureLDR(uint32_t extent_x, uint32_t extent_y, size_t mipmap = 1)
      : extent_x(extent_x)
      , extent_y(extent_y)
      , mipmap(mipmap)
    {
      raw.Allocate(sizeof(glm::u8vec4) * extent_x * extent_y);
    }
    ~TextureLDR() {}
  };

  struct TextureHDR
  {
    Raw raw;
    uint32_t extent_x;
    uint32_t extent_y;
    size_t mipmap;

  public:
    void Load(const std::string& name, size_t mipmap = 0) const;
    void Save(const std::string& name, size_t mipmap = 0) const;
    void Fill(std::function<glm::f32vec4(uint32_t, uint32_t)>fill_fn, size_t mipmap = 0) const;
    void Update();

  public:
    void Set(const glm::f32vec4& value, uint32_t x, uint32_t y, size_t mipmap = 0) const
    { 
      return raw.SetElement<glm::f32vec4>(value, size_t(y) * extent_x + x);
    }
    const glm::f32vec4& Get(uint32_t x, uint32_t y, size_t mipmap = 0) const
    { 
      return raw.GetElement<glm::f32vec4>(size_t(y) * extent_x + x);
    }
    std::pair<uint8_t*, size_t> Access(size_t mipmap = 0) const
    { 
      return raw.AccessBytes();
    }

  public:
    TextureHDR(uint32_t extent_x, uint32_t extent_y, size_t mipmap = 1)
      : extent_x(extent_x)
      , extent_y(extent_y)
      , mipmap(mipmap)
    {
      raw.Allocate(sizeof(glm::f32vec4) * extent_x * extent_y);
    }
    ~TextureHDR() {}
  };


  struct ItemBuffer
  {
    Raw raw;
    size_t stride;

  public:
    void Load(const std::string& path);
    void Save(const std::string& path);
    template<typename T> void Fill(std::function<T(size_t)> fill_fn);
    template<typename T> void Set(const T& value, size_t index)
    { 
      return raw.SetElement<T>(value, index);
    }
    template<typename T> const T& Get(size_t index) const 
    { 
      return raw.GetElement<T>(index);
    }
    std::pair<uint8_t*, size_t> Access() const
    { 
      return raw.AccessBytes();
    }

  public:
    ItemBuffer(size_t stride)
      : stride(stride)
    {
    }
    ~ItemBuffer() {}
  };
}