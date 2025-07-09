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
  TextureArrayLDR::TextureArrayLDR(uint32_t extent_x, uint32_t extent_y, size_t mipmap, size_t layers)
  {
    BLAST_ASSERT(extent_x > 0 && extent_y > 0 && mipmap > 0 && layers > 0);

    size_t count = 0;
    for (size_t i = 0; i < mipmap; ++i)
    {
      const auto x = std::max(1u, extent_x >> i);
      const auto y = std::max(1u, extent_y >> i);
      count += size_t(x * y);
    }

    raw.Allocate(count * layers * sizeof(glm::u8vec4));
  }

  void TextureArrayLDR::Fill(size_t layer, std::function<glm::u8vec4(size_t index)> fill_fn)
  {
    BLAST_ASSERT(layer > 0 && layer < layers && fill_fn != nullptr);

    size_t count = 0;
    for (size_t i = 0; i < mipmap; ++i)
    {
      const auto x = std::max(1u, extent_x >> i);
      const auto y = std::max(1u, extent_y >> i);
      count += size_t(x * y);
    }

    for (size_t i = 0; i < size_t(extent_x * extent_y); ++i)
    {
      raw.SetElement<glm::u8vec4>(fill_fn(i), count * layer + i);
    }
  }

  void TextureArrayLDR::Copy(size_t layer, std::pair<const glm::u8vec4*, size_t> texels)
  {
    BLAST_ASSERT(layer > 0 && layer < layers && texels.first != nullptr && texels.second == extent_x * extent_y);

    size_t count = 0;
    for (size_t i = 0; i < mipmap; ++i)
    {
      const auto x = std::max(1u, extent_x >> i);
      const auto y = std::max(1u, extent_y >> i);
      count += size_t(x * y);
    }

    raw.SetElements<glm::u8vec4>(texels, count * layer);
  }




  TextureArrayHDR::TextureArrayHDR(uint32_t extent_x, uint32_t extent_y, size_t mipmap, size_t layers)
  {
    BLAST_ASSERT(extent_x > 0 && extent_y > 0 && mipmap > 0 && layers > 0);

    size_t count = 0;
    for (size_t i = 0; i < mipmap; ++i)
    {
      const auto x = std::max(1u, extent_x >> i);
      const auto y = std::max(1u, extent_y >> i);
      count += size_t(x * y);
    }

    raw.Allocate(count * layers * sizeof(glm::f32vec4));
  }

  void TextureArrayHDR::Fill(size_t layer, std::function<glm::f32vec4(size_t index)> fill_fn)
  {
    BLAST_ASSERT(layer > 0 && layer < layers && fill_fn != nullptr);

    size_t count = 0;
    for (size_t i = 0; i < mipmap; ++i)
    {
      const auto x = std::max(1u, extent_x >> i);
      const auto y = std::max(1u, extent_y >> i);
      count += size_t(x * y);
    }

    for (size_t i = 0; i < size_t(extent_x * extent_y); ++i)
    {
      raw.SetElement<glm::f32vec4>(fill_fn(i), count * layer + i);
    }
  }

  void TextureArrayHDR::Copy(size_t layer, std::pair<const glm::f32vec4*, size_t> texels)
  {
    BLAST_ASSERT(layer > 0 && layer < layers && texels.first != nullptr && texels.second == extent_x * extent_y);

    size_t count = 0;
    for (size_t i = 0; i < mipmap; ++i)
    {
      const auto x = std::max(1u, extent_x >> i);
      const auto y = std::max(1u, extent_y >> i);
      count += size_t(x * y);
    }

    raw.SetElements<glm::f32vec4>(texels, count * layer);
  }



  StructureBuffer::StructureBuffer(size_t stride, size_t count)
  {
    BLAST_ASSERT(stride > 0 && count > 0);

    raw.Allocate(stride * count);
  }

  template<typename T> void StructureBuffer::Fill(size_t offset, size_t count, std::function<T(size_t index)> fill_fn)
  {
    BLAST_ASSERT(offset >= 0 && fill_fn != nullptr);

    for (size_t i = 0; i < count; ++i)
    {
      raw.SetElement<T>(fill_fn(i), offset + i);
    }
  }

  template<typename T> void StructureBuffer::Copy(size_t offset, std::pair<const T*, size_t> structures)
  {
    BLAST_ASSERT(offset >= 0 && structures.first != nullptr && structures.second > 0);

    raw.SetElements<T>(structures, offset);
  }
}