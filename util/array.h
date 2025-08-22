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
  class TextureArrayLDR
  {
  private:
    Format _format{ Format::FORMAT_UNKNOWN };
    uint32_t _size_x{ 0u };
    uint32_t _size_y{ 0u };
    size_t _levels{ 0u };
    size_t _layers{ 0u };
    size_t _stride{ 0u };

  private:
    Raw _raw;

  public:
    size_t Stride() const { return _stride; }
    size_t Length() const { return _layers; }
    std::pair<uint8_t*, size_t> Bytes(size_t offset = 0) const { return _raw.AccessBytes(offset); }
    std::pair<glm::u8vec4*, size_t> Items(size_t offset = 0) const { return _raw.AccessItems<glm::u8vec4>(offset); }
    
  public:
    uint32_t constexpr SizeX(size_t level = 0) const { return std::max(1u, _size_x >> level); }
    uint32_t constexpr SizeY(size_t level = 0) const { return std::max(1u, _size_y >> level); }
    size_t constexpr Offset(size_t layer, size_t level) const
    {
      auto offset = _stride * layer;
      for (auto i = 0; i < level; ++i) { offset += size_t(SizeX(i) * SizeY(i)); }
      return offset;
    }
    void Set(size_t layer, size_t level, std::pair<const glm::u8vec4*, size_t> items, size_t offset = 0) const
    { 
      _raw.SetItems<glm::u8vec4>(items, Offset(layer, level));
    }
    std::pair<const glm::u8vec4*, size_t> Get(size_t layer, size_t level, size_t offset = 0) const
    {
      return _raw.GetItems<glm::u8vec4>(Offset(layer, level));
    }
    void Load(const char* name, size_t layer, size_t lavel = 0) const;
    void Save(const char* name, size_t layer, size_t lavel = 0) const;

  //public:
  //  struct Mipmap
  //  {
  //    uint32_t size_x, size_y;
  //    glm::u8vec4& operator[](size_t index) {}
  //  };
  //  struct Slice
  //  {
  //    std::vector<Mipmap> mipmaps;
  //    const Mipmap& operator[](size_t index) { return mipmaps[index]; }
  //  };
  //  std::vector<Slice> slices;
  //  const Slice& operator[](size_t index) { return slices[index]; }


  public:
    SPtrProperty Export() const;
    void Import(SPtrProperty property);

  public:
    TextureArrayLDR(Format format, uint32_t size_x, uint32_t size_y, size_t layers, size_t levels = 1)
      : _format(format)
      , _size_x(size_x)
      , _size_y(size_y)
      , _levels(levels)
      , _layers(layers)
      , _stride(Offset(1, 0))
      , _raw(_stride * _layers, glm::zero<glm::u8vec4>())
    {}

  public:
    TextureArrayLDR(const TextureArrayLDR& raw) = delete;
    TextureArrayLDR& operator=(const TextureArrayLDR& raw) = delete;
    TextureArrayLDR(TextureArrayLDR&& array) noexcept 
    {
      std::swap(_raw, array._raw);
      std::swap(_format, array._format);
      std::swap(_size_x, array._size_x);
      std::swap(_size_y, array._size_y);
      std::swap(_levels, array._levels);
      std::swap(_layers, array._layers);
      std::swap(_stride, array._stride);
    }
    TextureArrayLDR& operator=(TextureArrayLDR&& array) noexcept
    { 
      std::swap(_raw, array._raw);
      std::swap(_format, array._format);
      std::swap(_size_x, array._size_x);
      std::swap(_size_y, array._size_y);
      std::swap(_levels, array._levels);
      std::swap(_layers, array._layers);
      std::swap(_stride, array._stride);
      return *this;
    }
    ~TextureArrayLDR() {}
  };

  class TextureArrayHDR
  {
  private:
    Format _format{ Format::FORMAT_UNKNOWN };
    uint32_t _size_x{ 0u };
    uint32_t _size_y{ 0u };
    size_t _levels{ 0u };
    size_t _layers{ 0u };
    size_t _stride{ 0u };

  private:
    Raw _raw;

  public:
    size_t Stride() const { return _stride; }
    size_t Length() const { return _layers; }
    std::pair<uint8_t*, size_t> Bytes(size_t offset = 0) const { return _raw.AccessBytes(offset); }
    std::pair<glm::f32vec4*, size_t> Items(size_t offset = 0) const { return _raw.AccessItems<glm::f32vec4>(offset); }

  public:
    uint32_t constexpr SizeX(size_t level = 0) const { return std::max(1u, _size_x >> level); }
    uint32_t constexpr SizeY(size_t level = 0) const { return std::max(1u, _size_y >> level); }
    size_t constexpr Offset(size_t layer, size_t level) const
    {
      auto offset = _stride * layer;
      for (auto i = 0; i < level; ++i) { offset += size_t(SizeX(i) * SizeY(i)); }
      return offset;
    }
    void Set(size_t layer, size_t level, std::pair<const glm::f32vec4*, size_t> items, size_t offset = 0) const
    {
      _raw.SetItems<glm::f32vec4>(items, Offset(layer, level) + offset);
    }
    std::pair<const glm::f32vec4*, size_t> Get(size_t layer, size_t level, size_t offset = 0) const
    {
      return _raw.GetItems<glm::f32vec4>(Offset(layer, level) + offset);
    }
    void Load(const char* name, size_t layer, size_t lavel = 0) const;
    void Save(const char* name, size_t layer, size_t lavel = 0) const;

  public:
    SPtrProperty Export() const;
    void Import(SPtrProperty property);

  public:
    TextureArrayHDR(Format format, uint32_t size_x, uint32_t size_y, size_t layers, size_t levels = 1)
      : _format(format)
      , _size_x(size_x)
      , _size_y(size_y)
      , _levels(levels)
      , _layers(layers)
      , _stride(Offset(1, 0))
      , _raw(_stride * _layers, glm::zero<glm::f32vec4>())
    {
    }

  public:
    TextureArrayHDR(const TextureArrayHDR& raw) = delete;
    TextureArrayHDR& operator=(const TextureArrayLDR& raw) = delete;
    TextureArrayHDR(TextureArrayHDR&& array) noexcept
    {
      std::swap(_raw, array._raw);
      std::swap(_format, array._format);
      std::swap(_size_x, array._size_x);
      std::swap(_size_y, array._size_y);
      std::swap(_levels, array._levels);
      std::swap(_layers, array._layers);
      std::swap(_stride, array._stride);
    }
    TextureArrayHDR& operator=(TextureArrayHDR&& array) noexcept
    {
      std::swap(_raw, array._raw);
      std::swap(_format, array._format);
      std::swap(_size_x, array._size_x);
      std::swap(_size_y, array._size_y);
      std::swap(_levels, array._levels);
      std::swap(_layers, array._layers);
      std::swap(_stride, array._stride);
      return *this;
    }
    ~TextureArrayHDR() {}
  };
}