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
    size_t layers{ 0u };

  public:
    size_t Count() const;
    void Initialize(size_t layer, glm::u8vec4 value = glm::zero<glm::u8vec4>());
    void Discard(size_t layer);

  public:
    void Set(size_t layer, size_t index, const glm::u8vec4& value);
    const glm::u8vec4& Get(size_t layer, size_t index) const;
    std::pair<uint8_t*, size_t> Access(size_t layer);

  public:
    std::vector<Raw>::iterator begin() { return raws.begin(); }
    std::vector<Raw>::iterator end() { return raws.end(); }
    std::vector<Raw>::const_iterator cbegin() const { return raws.cbegin(); }
    std::vector<Raw>::const_iterator cend() const { return raws.cend(); }
    void Add(size_t layer, Raw&& raw) { raws.at(layer) = std::move(raw); }
    void Remove(size_t layer) { raws.at(layer) = {}; }

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
      , layers(layers)
    {
      raws.resize(layers);
    }
    ~TextureArrayLDR() {}
  };

  struct TextureArrayHDR
  {
    std::vector<Raw> raws;
    Format format{ Format::FORMAT_UNKNOWN };
    uint32_t size_x{ 0u };
    uint32_t size_y{ 0u };
    size_t layers{ 0u };   

  public:
    size_t Count() const;
    void Initialize(size_t layer, glm::f32vec4 value = glm::zero<glm::f32vec4>());
    void Discard(size_t layer);

  public:
    void Set(size_t layer, size_t index, const glm::f32vec4& value);
    const glm::f32vec4& Get(size_t layer, size_t index) const;
    std::pair<uint8_t*, size_t> Access(size_t layer, size_t mipmap);
    
  public:
    std::vector<Raw>::iterator begin() { return raws.begin(); }
    std::vector<Raw>::iterator end() { return raws.end(); }
    std::vector<Raw>::const_iterator cbegin() const { return raws.cbegin(); }
    std::vector<Raw>::const_iterator cend() const { return raws.cend(); }
    void Add(size_t layer, Raw&& raw) { raws.at(layer) = std::move(raw); }
    void Remove(size_t layer) { raws.at(layer) = {}; }

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
      , layers(layers)
    {
      raws.resize(layers);
    }
    ~TextureArrayHDR() {}
  };
}