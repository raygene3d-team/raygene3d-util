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
#include "property.h"


namespace RayGene3D
{
  struct TextureArrayLDR
  {
    std::vector<Raw> raws;
    Format format{ Format::FORMAT_UNKNOWN };
    uint32_t size_x{ 0u };
    uint32_t size_y{ 0u };

  public:
    size_t Size() const;
    void Create(size_t layer, glm::u8vec4 value = glm::zero<glm::u8vec4>());
    void Create(size_t layer, std::pair<const glm::u8vec4*, size_t> texels);
    void Delete(size_t layer);

  public:
    bool Empty(size_t layer) const;
    size_t Count(size_t layer) const;
    void Set(size_t layer, size_t index, const glm::u8vec4& value);
    const glm::u8vec4& Get(size_t layer, size_t index) const;
    std::pair<uint8_t*, size_t> Access(size_t layer);

  public:
    std::vector<Raw>::iterator begin() { return raws.begin(); }
    std::vector<Raw>::iterator end() { return raws.end(); }
    std::vector<Raw>::const_iterator cbegin() const { return raws.cbegin(); }
    std::vector<Raw>::const_iterator cend() const { return raws.cend(); }
    Raw&& operator[](size_t layer) { return std::move(raws.at(layer)); }

  public:
    void Load(size_t layer, const char* name);
    void Save(size_t layer, const char* name);

  public:
    SPtrProperty Export() const;
    void Import(SPtrProperty property);

  public:
    TextureArrayLDR(Format format, uint32_t size_x, uint32_t size_y, size_t layers)
      : format(format)
      , size_x(size_x)
      , size_y(size_y)
      , raws(layers)
    {}
    TextureArrayLDR(Format format, uint32_t size_x, uint32_t size_y, std::initializer_list<std::pair<const glm::u8vec4*, size_t>> initializers)
      : format(format)
      , size_x(size_x)
      , size_y(size_y)
      , raws(initializers.begin(), initializers.end())
    {}

  public:
    TextureArrayLDR(const TextureArrayLDR& raw) = delete;
    TextureArrayLDR& operator=(const TextureArrayLDR& raw) = delete;
    TextureArrayLDR(TextureArrayLDR&& array) noexcept 
    {
      std::swap(raws, array.raws);
      std::swap(format, array.format);
      std::swap(size_x, array.size_x);
      std::swap(size_y, array.size_y);
    }
    TextureArrayLDR& operator=(TextureArrayLDR&& array) noexcept
    { 
      std::swap(raws, array.raws);
      std::swap(format, array.format);
      std::swap(size_x, array.size_x);
      std::swap(size_y, array.size_y);
      return *this;
    }
    ~TextureArrayLDR() {}
  };

  struct TextureArrayHDR
  {
    std::vector<Raw> raws;
    Format format{ Format::FORMAT_UNKNOWN };
    uint32_t size_x{ 0u };
    uint32_t size_y{ 0u };   

  public:
    size_t Size() const;
    void Create(size_t layer, glm::f32vec4 value = glm::zero<glm::f32vec4>());
    void Create(size_t layer, std::pair<const glm::f32vec4*, size_t> texels);
    void Delete(size_t layer);

  public:
    bool Empty(size_t layer) const;
    size_t Count(size_t layer) const;
    void Set(size_t layer, size_t index, const glm::f32vec4& value);
    const glm::f32vec4& Get(size_t layer, size_t index) const;
    std::pair<uint8_t*, size_t> Access(size_t layer);
    
  public:
    std::vector<Raw>::iterator begin() { return raws.begin(); }
    std::vector<Raw>::iterator end() { return raws.end(); }
    std::vector<Raw>::const_iterator cbegin() const { return raws.cbegin(); }
    std::vector<Raw>::const_iterator cend() const { return raws.cend(); }
    Raw&& operator[](size_t layer) { return std::move(raws.at(layer)); }

  public:
    void Load(size_t layer, const char* name);
    void Save(size_t layer, const char* name);

  public:
    SPtrProperty Export() const;
    void Import(SPtrProperty property);

  public:
    TextureArrayHDR(Format format, uint32_t size_x, uint32_t size_y, size_t layers)
      : format(format)
      , size_x(size_x)
      , size_y(size_y)
      , raws(layers)
    {}
    TextureArrayHDR(Format format, uint32_t size_x, uint32_t size_y, std::initializer_list<std::pair<const glm::f32vec4*, size_t>> initializers)
      : format(format)
      , size_x(size_x)
      , size_y(size_y)
      , raws(initializers.begin(), initializers.end())
    {}

  public:
    TextureArrayHDR(const TextureArrayHDR& raw) = delete;
    TextureArrayHDR& operator=(const TextureArrayHDR& raw) = delete;
    TextureArrayHDR(TextureArrayHDR&& array) noexcept
    {
      std::swap(raws, array.raws);
      std::swap(format, array.format);
      std::swap(size_x, array.size_x);
      std::swap(size_y, array.size_y);
    }
    TextureArrayHDR& operator=(TextureArrayHDR&& array) noexcept
    {
      std::swap(raws, array.raws);
      std::swap(format, array.format);
      std::swap(size_x, array.size_x);
      std::swap(size_y, array.size_y);
      return *this;
    }
    ~TextureArrayHDR() {}
  };
}