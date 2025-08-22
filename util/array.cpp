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

#include "array.h"


#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb/stb_image_resize.h>

#define TINYEXR_IMPLEMENTATION
#include <tinyexr/tinyexr.h>

namespace RayGene3D
{
  void TextureArrayLDR::Load(const char* name, size_t layer, size_t level) const
  {
    auto src_size_x = 0;
    auto src_size_y = 0;
    auto src_stride = 0;
    auto src_texels = stbi_load(name, &src_size_x, &src_size_y, &src_stride, STBI_default);

    auto dst_size_x = SizeX(level);
    auto dst_size_y = SizeY(level);
    auto dst_stride = 4;
    auto dst_texels = reinterpret_cast<uint8_t*>(Items(Offset(layer, level)).first);

    if (_format == Format::FORMAT_R8G8B8A8_SRGB)
    {
      stbir_resize_uint8_srgb(src_texels, src_size_x, src_size_y, 0, dst_texels, dst_size_x, dst_size_y, 0, dst_stride, 3, 0);
    }
    else
    {
      stbir_resize_uint8(src_texels, src_size_x, src_size_y, 0, dst_texels, dst_size_x, dst_size_y, 0, dst_stride);
    }

    stbi_image_free(src_texels);
   }

  void TextureArrayLDR::Save(const char* name, size_t layer, size_t lavel) const
  {
    auto src_size_x = 0;
    auto src_size_y = 0;
    auto src_stride = 0;
    //auto src_data = stbi_save(name, &src_extent_x, &src_extent_y, &src_channels, STBI_default);
  }

  SPtrProperty TextureArrayLDR::Export() const
  {
    //auto x = _size_x;
    //auto y = _size_y;
    //auto z = uint32_t{ 1u };

    //auto count = 0ull;
    //while (x > 1 && y > 1)
    //{
    //  count += size_t(x * y * z);
    //  x = std::max(1u, x >> 1);
    //  y = std::max(1u, y >> 1);
    //  z = std::max(1u, z >> 1);
    //}

    //auto raw = Raw(count * _layers, glm::zero<glm::u8vec4>());

    //for (auto i = 0ull; i < _layers; ++i)
    //{
    //  raw.SetBytes(raws.at(i).GetBytes(), i * count);

    //  auto src_size_x = _size_x;
    //  auto src_size_y = _size_y;
    //  auto src_stride = 4;
    //  auto src_texels = raw.AccessBytes().first;

    //  for (auto j = 0ull; j < _levels; ++j)
    //  {
    //    auto dst_size_x = src_size_x > 1 ? src_size_x >> 1 : 1;
    //    auto dst_size_y = src_size_y > 1 ? src_size_y >> 1 : 1;
    //    auto dst_stride = 4;
    //    auto dst_texels = src_texels + src_stride * src_size_x * src_size_y;

    //    if (_format == Format::FORMAT_R8G8B8A8_SRGB)
    //    {
    //      stbir_resize_uint8_srgb(src_texels, src_size_x, src_size_y, 0, dst_texels, dst_size_x, dst_size_y, 0, dst_stride, 3, 0);
    //    }
    //    else
    //    {
    //      stbir_resize_uint8(src_texels, src_size_y, src_size_y, 0, dst_texels, dst_size_x, dst_size_y, 0, dst_stride);
    //    }

    //    src_size_x = dst_size_x;
    //    src_size_y = dst_size_y;
    //    src_texels = dst_texels;
    //  }
    //}

    return SPtrProperty(new Property({
        { "format", SPtrProperty(new Property(uint32_t(_format))) },
        { "size_x", SPtrProperty(new Property(uint32_t(_size_x))) },
        { "size_y", SPtrProperty(new Property(uint32_t(_size_y))) },
        { "levels", SPtrProperty(new Property(uint32_t(_levels))) },
        { "layers", SPtrProperty(new Property(uint32_t(_layers))) },
        { "raw", SPtrProperty(new Property(_raw.AccessBytes())) }
     }));
  }

  void TextureArrayLDR::Import(SPtrProperty property)
  {

  }



  void TextureArrayHDR::Load(const char* name, size_t layer, size_t level) const
  {
    auto src_size_x = 0;
    auto src_size_y = 0;
    auto src_stride = 4;
    float* src_texels = nullptr; // stbi_loadf(path.c_str(), &extent_x, &extent_y, &channels, STBI_default);
    LoadEXR(&src_texels, &src_size_x, &src_size_y, name, nullptr);

    auto dst_size_x = SizeX(level);
    auto dst_size_y = SizeY(level);
    auto dst_stride = 4;
    auto dst_texels = reinterpret_cast<float*>(Items(Offset(layer, level)).first);
    stbir_resize_float(src_texels, src_size_x, src_size_y, 0, dst_texels, dst_size_x, dst_size_y, 0, dst_stride);

    free (src_texels);
  }

  void TextureArrayHDR::Save(const char* name, size_t layer, size_t level) const
  {

  }

  SPtrProperty TextureArrayHDR::Export() const
  {
    //auto x = size_x;
    //auto y = size_y;
    //auto count = 0ull;
    //auto mipmap = 0ull;
    //auto layers = raws.size();

    //while (x > 1 && y > 1)
    //{
    //  ++mipmap;
    //  count += x * y;
    //  x = x > 1 ? x >> 1 : 1;
    //  y = y > 1 ? y >> 1 : 1;
    //}

    //auto raw = Raw(count * layers, glm::zero<glm::f32vec4>());

    //for (auto i = 0ull; i < layers; ++i)
    //{
    //  raw.SetBytes(raws.at(i).GetBytes(), i * count);

    //  auto src_size_x = size_x;
    //  auto src_size_y = size_y;
    //  auto src_stride = 4;
    //  auto src_texels = reinterpret_cast<float*>(raw.AccessBytes().first);

    //  for (auto j = 0ull; j < mipmap; ++j)
    //  {
    //    auto dst_size_x = src_size_x > 1 ? src_size_x >> 1 : 1;
    //    auto dst_size_y = src_size_y > 1 ? src_size_y >> 1 : 1;
    //    auto dst_stride = 4;
    //    auto dst_texels = src_texels + src_stride * src_size_x * src_size_y;

    //    stbir_resize_float(src_texels, src_size_y, src_size_y, 0, dst_texels, dst_size_x, dst_size_y, 0, 4);

    //    src_size_x = dst_size_x;
    //    src_size_y = dst_size_y;
    //    src_texels = dst_texels;
    //  }
    //}

    return SPtrProperty(new Property({
        { "format", SPtrProperty(new Property(uint32_t(_format))) },
        { "size_x", SPtrProperty(new Property(uint32_t(_size_x))) },
        { "size_y", SPtrProperty(new Property(uint32_t(_size_y))) },
        { "levels", SPtrProperty(new Property(uint32_t(_levels))) },
        { "layers", SPtrProperty(new Property(uint32_t(_layers))) },
        { "raw", SPtrProperty(new Property(_raw.AccessBytes())) }
      }));
  }

  void TextureArrayHDR::Import(SPtrProperty property)
  {

  }
}