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

#include "types.h"

namespace RayGene3D
{
  size_t TextureArrayLDR::Count(size_t mipmap) const
  {
    return std::max(1ull, size_t(extent_x) >> mipmap) * std::max(1ull, size_t(extent_y) >> mipmap);
  }

  void TextureArrayLDR::Initialize(size_t layer, glm::u8vec4 value = glm::zero<glm::u8vec4>())
  {
    auto count = 0ull; for (size_t i = 0; i < mipmap; ++i) { count += Count(i); }
    raws.at(layer) = Raw(count, value);
  }

  void TextureArrayLDR::Discard(size_t layer)
  {
    raws.at(layer) = {};
  }

  void TextureArrayLDR::Set(size_t layer, size_t mipmap, size_t index, const glm::u8vec4& value)
  {
    auto offset = 0ull; for (size_t i = 0; i < mipmap; ++i) { offset += Count(i); }
    raws.at(layer).SetElement<glm::u8vec4>(value, index + offset);
  }

  const glm::u8vec4& TextureArrayLDR::Get(size_t layer, size_t mipmap, size_t index) const
  {
    auto offset = 0ull; for (size_t i = 0; i < mipmap; ++i) { offset += Count(i); }
    return raws.at(layer).GetElement<glm::u8vec4>(index + offset);
  }

  std::pair<glm::u8vec4*, size_t> TextureArrayLDR::Access(size_t layer, size_t mipmap)
  {
    auto offset = 0ull; for (size_t i = 0; i < mipmap; ++i) { offset += Count(i); }
    return raws.at(layer).AccessElements<glm::u8vec4>(offset);
  }



  size_t TextureArrayHDR::Count(size_t mipmap) const
  {
    return std::max(1ull, size_t(extent_x) >> mipmap) * std::max(1ull, size_t(extent_y) >> mipmap);
  }

  void TextureArrayHDR::Initialize(size_t layer, glm::f32vec4 value = glm::zero<glm::f32vec4>())
  {
    auto count = 0ull; for (size_t i = 0; i < mipmap; ++i) { count += Count(i); }
    raws.at(layer) = Raw(count, value);
  }

  void TextureArrayHDR::Discard(size_t layer)
  {
    raws.at(layer) = {};
  }

  void TextureArrayHDR::Set(size_t layer, size_t mipmap, size_t index, const glm::f32vec4& value)
  {
    auto offset = 0ull; for (size_t i = 0; i < mipmap; ++i) { offset += Count(i); }
    raws.at(layer).SetElement<glm::f32vec4>(value, index + offset);
  }

  const glm::f32vec4& TextureArrayHDR::Get(size_t layer, size_t mipmap, size_t index) const
  {
    auto offset = 0ull; for (size_t i = 0; i < mipmap; ++i) { offset += Count(i); }
    return raws.at(layer).GetElement<glm::f32vec4>(index + offset);
  }

  std::pair<glm::f32vec4*, size_t> TextureArrayHDR::Access(size_t layer, size_t mipmap)
  {
    auto offset = 0ull; for (size_t i = 0; i < mipmap; ++i) { offset += Count(i); }
    return raws.at(layer).AccessElements<glm::f32vec4>(offset);
  }
}