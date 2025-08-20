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
  //void TextureArrayLDR::Resize(size_t layers)
  //{
  //  raws.resize(layers);
  //}

  size_t TextureArrayLDR::Size() const
  {
    return raws.size();
  }

  void TextureArrayLDR::Create(size_t layer, glm::u8vec4 value)
  {
    raws.at(layer) = std::move(Raw(size_t(size_x) * size_t(size_y), value));
  }

  void TextureArrayLDR::Create(size_t layer, std::pair<const glm::u8vec4*, size_t> texels)
  {
    raws.at(layer) = std::move(Raw(texels));
  }

  void TextureArrayLDR::Delete(size_t layer)
  {
    raws.at(layer) = {};
  }

  bool TextureArrayLDR::Empty(size_t layer) const
  {
    return raws.at(layer).AccessBytes().second != 0;
  }

  size_t TextureArrayLDR::Count(size_t layer) const
  {
    return raws.at(layer).AccessBytes().second / sizeof(glm::u8vec4);;
  }

  void TextureArrayLDR::Set(size_t layer, size_t index, const glm::u8vec4& value)
  {
    raws.at(layer).SetItem<glm::u8vec4>(value, index);
  }

  const glm::u8vec4& TextureArrayLDR::Get(size_t layer, size_t index) const
  {
    return raws.at(layer).GetItem<glm::u8vec4>(index);
  }

  std::pair<uint8_t*, size_t> TextureArrayLDR::Access(size_t layer)
  {
    return raws.at(layer).AccessBytes();
  }

  void TextureArrayLDR::Load(size_t layer, const char* name)
  {
    auto src_size_x = 0;
    auto src_size_y = 0;
    auto src_stride = 0;
    auto src_texels = stbi_load(name, &src_size_x, &src_size_y, &src_stride, STBI_default);

    auto dst_size_x = size_x;
    auto dst_size_y = size_y;
    auto dst_stride = 4;
    auto dst_texels = raws.at(layer).AccessBytes().first;

    if (format == Format::FORMAT_R8G8B8A8_SRGB)
    {
      stbir_resize_uint8_srgb(src_texels, src_size_x, src_size_y, 0, dst_texels, dst_size_x, dst_size_y, 0, dst_stride, 3, 0);
    }
    else
    {
      stbir_resize_uint8(src_texels, src_size_x, src_size_y, 0, dst_texels, dst_size_x, dst_size_y, 0, dst_stride);
    }

    stbi_image_free(src_texels);
   }

  void TextureArrayLDR::Save(size_t layer, const char* name)
  {
    auto src_size_x = 0;
    auto src_size_y = 0;
    auto src_stride = 0;
    //auto src_data = stbi_save(name, &src_extent_x, &src_extent_y, &src_channels, STBI_default);
  }

  SPtrProperty TextureArrayLDR::Export() const
  {
    auto x = size_x;
    auto y = size_y;
    auto z = uint32_t{ 1u };
    auto mipmap = 1 + floor(log2(std::max(x, y)));
    auto layers = raws.size();

    auto count = 0ull;
    while (x > 1 && y > 1)
    {
      count += x * y * z;
      x = std::max(1u, x >> 1);
      y = std::max(1u, y >> 1);
      z = std::max(1u, z >> 1);
    }

    auto raw = Raw(count * layers, glm::zero<glm::u8vec4>());

    for (auto i = 0ull; i < layers; ++i)
    {
      raw.SetBytes(raws.at(i).GetBytes(), i * count);

      auto src_size_x = size_x;
      auto src_size_y = size_y;
      auto src_stride = 4;
      auto src_texels = raw.AccessBytes().first;

      for (auto j = 0ull; j < mipmap; ++j)
      {
        auto dst_size_x = src_size_x > 1 ? src_size_x >> 1 : 1;
        auto dst_size_y = src_size_y > 1 ? src_size_y >> 1 : 1;
        auto dst_stride = 4;
        auto dst_texels = src_texels + src_stride * src_size_x * src_size_y;

        if (format == Format::FORMAT_R8G8B8A8_SRGB)
        {
          stbir_resize_uint8_srgb(src_texels, src_size_x, src_size_y, 0, dst_texels, dst_size_x, dst_size_y, 0, dst_stride, 3, 0);
        }
        else
        {
          stbir_resize_uint8(src_texels, src_size_y, src_size_y, 0, dst_texels, dst_size_x, dst_size_y, 0, dst_stride);
        }

        src_size_x = dst_size_x;
        src_size_y = dst_size_y;
        src_texels = dst_texels;
      }
    }

    const auto root_property = std::shared_ptr<Property>(new Property(Property::TYPE_OBJECT));
    {

      const auto format_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
      format_property->SetUint(format);
      root_property->SetObjectItem("format", format_property);

      const auto size_x_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
      size_x_property->SetUint(size_x);
      root_property->SetObjectItem("size_x", size_x_property);

      const auto size_y_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
      size_y_property->SetUint(size_y);
      root_property->SetObjectItem("size_y", size_y_property);

      const auto mipmap_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
      mipmap_property->SetUint(mipmap);
      root_property->SetObjectItem("mipmap", mipmap_property);

      const auto layers_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
      layers_property->SetUint(layers);
      root_property->SetObjectItem("layers", layers_property);

      const auto raw_property = std::shared_ptr<Property>(new Property(Property::TYPE_RAW));
      raw_property->SetRaw(std::move(raw));
      root_property->SetObjectItem("raw", raw_property);
    }

    return root_property;
  }

  void TextureArrayLDR::Import(SPtrProperty property)
  {

  }


  //void TextureArrayHDR::Resize(size_t layers)
  //{
  //  raws.resize(layers);
  //}

  size_t TextureArrayHDR::Size() const
  {
    return raws.size();
  }

  void TextureArrayHDR::Create(size_t layer, glm::f32vec4 value)
  {
    raws.at(layer) = std::move(Raw(size_t(size_x) * size_t(size_y), value));
  }

  void TextureArrayHDR::Create(size_t layer, std::pair<const glm::f32vec4*, size_t> texels)
  {
    raws.at(layer) = std::move(Raw(texels));
  }

  void TextureArrayHDR::Delete(size_t layer)
  {
    raws.at(layer) = {};
  }

  bool TextureArrayHDR::Empty(size_t layer) const
  {
    return raws.at(layer).AccessBytes().second != 0;
  }

  size_t TextureArrayHDR::Count(size_t layer) const
  {
    return raws.at(layer).AccessBytes().second / sizeof(glm::f32vec4);
  }

  void TextureArrayHDR::Set(size_t layer, size_t index, const glm::f32vec4& value)
  {
    raws.at(layer).SetItem<glm::f32vec4>(value, index);
  }

  const glm::f32vec4& TextureArrayHDR::Get(size_t layer, size_t index) const
  {
    return raws.at(layer).GetItem<glm::f32vec4>(index);
  }

  std::pair<uint8_t*, size_t> TextureArrayHDR::Access(size_t layer)
  {
    return raws.at(layer).AccessBytes();
  }

  void TextureArrayHDR::Load(size_t layer, const char* name)
  {
    auto src_size_x = 0;
    auto src_size_y = 0;
    auto src_stride = 4;
    float* src_texels = nullptr; // stbi_loadf(path.c_str(), &extent_x, &extent_y, &channels, STBI_default);
    LoadEXR(&src_texels, &src_size_x, &src_size_y, name, nullptr);

    auto dst_size_x = size_x;
    auto dst_size_y = size_y;
    auto dst_stride = 4;
    auto dst_texels = reinterpret_cast<float*>(raws.at(layer).AccessBytes().first);
    stbir_resize_float(src_texels, src_size_x, src_size_y, 0, dst_texels, dst_size_x, dst_size_y, 0, dst_stride);

    free (src_texels);
  }

  void TextureArrayHDR::Save(size_t layer, const char* name)
  {

  }

  SPtrProperty TextureArrayHDR::Export() const
  {
    auto x = size_x;
    auto y = size_y;
    auto count = 0ull;
    auto mipmap = 0ull;
    auto layers = raws.size();

    while (x > 1 && y > 1)
    {
      ++mipmap;
      count += x * y;
      x = x > 1 ? x >> 1 : 1;
      y = y > 1 ? y >> 1 : 1;
    }

    auto raw = Raw(count * layers, glm::zero<glm::f32vec4>());

    for (auto i = 0ull; i < layers; ++i)
    {
      raw.SetBytes(raws.at(i).GetBytes(), i * count);

      auto src_size_x = size_x;
      auto src_size_y = size_y;
      auto src_stride = 4;
      auto src_texels = reinterpret_cast<float*>(raw.AccessBytes().first);

      for (auto j = 0ull; j < mipmap; ++j)
      {
        auto dst_size_x = src_size_x > 1 ? src_size_x >> 1 : 1;
        auto dst_size_y = src_size_y > 1 ? src_size_y >> 1 : 1;
        auto dst_stride = 4;
        auto dst_texels = src_texels + src_stride * src_size_x * src_size_y;

        stbir_resize_float(src_texels, src_size_y, src_size_y, 0, dst_texels, dst_size_x, dst_size_y, 0, 4);

        src_size_x = dst_size_x;
        src_size_y = dst_size_y;
        src_texels = dst_texels;
      }
    }

    const auto root_property = std::shared_ptr<Property>(new Property(Property::TYPE_OBJECT));
    {

      const auto format_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
      format_property->SetUint(format);
      root_property->SetObjectItem("format", format_property);

      const auto size_x_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
      size_x_property->SetUint(size_x);
      root_property->SetObjectItem("size_x", size_x_property);

      const auto size_y_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
      size_y_property->SetUint(size_y);
      root_property->SetObjectItem("size_y", size_y_property);

      const auto mipmap_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
      mipmap_property->SetUint(mipmap);
      root_property->SetObjectItem("mipmap", mipmap_property);

      const auto layers_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
      layers_property->SetUint(layers);
      root_property->SetObjectItem("layers", layers_property);

      const auto raw_property = std::shared_ptr<Property>(new Property(Property::TYPE_RAW));
      raw_property->SetRaw(std::move(raw));
      root_property->SetObjectItem("raw", raw_property);
    }

    return root_property;
  }

  void TextureArrayHDR::Import(SPtrProperty property)
  {

  }
}