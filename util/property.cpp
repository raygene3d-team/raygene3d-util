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


#include "property.h"

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
  void Property::FromFMat3x4(const glm::f32mat3x4& mat)
  {
    for (uint32_t i = 0; i < 3; ++i)
    {
      for (uint32_t j = 0; j < 4; ++j)
      {
        this->GetArrayItem(i * 4 + j)->SetReal(mat[i][j]);
      }
    }
  }

  void Property::FromFVec4(const glm::f32vec4& vec)
  {
    for (uint32_t i = 0; i < 4; ++i)
    {
      this->GetArrayItem(i)->SetReal(vec[i]);
    }
  }

  void Property::FromFVec3(const glm::f32vec3& vec)
  {
    for (uint32_t i = 0; i < 3; ++i)
    {
      this->GetArrayItem(i)->SetReal(vec[i]);
    }
  }

  void Property::FromFVec2(const glm::f32vec2& vec)
  {
    for (uint32_t i = 0; i < 2; ++i)
    {
      this->GetArrayItem(i)->SetReal(vec[i]);
    }
  }

  void Property::FromFloat(float value)
  {
    this->SetReal(value);
  }

  void Property::FromUVec4(const glm::u32vec4& vec)
  {
    for (uint32_t i = 0; i < 4; ++i)
    {
      this->GetArrayItem(i)->SetUint(vec[i]);
    }
  }

  void Property::FromUVec3(const glm::u32vec3& vec)
  {
    for (uint32_t i = 0; i < 3; ++i)
    {
      this->GetArrayItem(i)->SetUint(vec[i]);
    }
  }

  void Property::FromUVec2(const glm::u32vec2& vec)
  {
    for (uint32_t i = 0; i < 2; ++i)
    {
      this->GetArrayItem(i)->SetUint(vec[i]);
    }
  }

  void Property::FromUInt(uint32_t value)
  {
    this->SetUint(value);
  }


  glm::f32mat3x4 Property::ToFMat3x4() const
  {
    glm::f32mat3x4 mat;
    for (uint32_t i = 0; i < 3; ++i)
    {
      for (uint32_t j = 0; j < 4; ++j)
      {
        mat[i][j] = this->GetArrayItem(i * 4 + j)->GetReal();
      }
    }
    return mat;
  }

  glm::f32vec4 Property::ToFVec4() const
  {
    glm::fvec4 vec;
    for (uint32_t i = 0; i < 4; ++i)
    {
      vec[i] = this->GetArrayItem(i)->GetReal();
    }

    return vec;
  }

  glm::f32vec3 Property::ToFVec3() const
  {
    glm::fvec4 vec;
    for (uint32_t i = 0; i < 3; ++i)
    {
      vec[i] = this->GetArrayItem(i)->GetReal();
    }

    return vec;
  }

  glm::f32vec2 Property::ToFVec2() const
  {
    glm::fvec4 vec;
    for (uint32_t i = 0; i < 2; ++i)
    {
      vec[i] = this->GetArrayItem(i)->GetReal();
    }

    return vec;
  }

  float Property::ToFloat() const
  {
    return this->GetReal();
  }

  glm::u32vec4 Property::ToUVec4() const
  {
    glm::u32vec4 vec;
    for (uint32_t i = 0; i < 4; ++i)
    {
      vec[i] = this->GetArrayItem(i)->GetUint();
    }

    return vec;
  }

  glm::u32vec3 Property::ToUVec3() const
  {
    glm::u32vec4 vec;
    for (uint32_t i = 0; i < 3; ++i)
    {
      vec[i] = this->GetArrayItem(i)->GetUint();
    }

    return vec;
  }

  glm::u32vec2 Property::ToUVec2() const
  {
    glm::u32vec4 vec;
    for (uint32_t i = 0; i < 2; ++i)
    {
      vec[i] = this->GetArrayItem(i)->GetUint();
    }

    return vec;
  }

  uint32_t Property::ToUInt() const
  {
    return this->GetUint();
  }


  nlohmann::json Property::ToJSON(const std::shared_ptr<Property>& property, std::map<std::shared_ptr<Property>, std::string>& binaries)
  {
    nlohmann::json json;

    switch (property->_value.index())
    {
    case 1:
    {
      json = std::get<1>(property->_value);
      break;
    }
    case 2:
    {
      json = std::get<2>(property->_value);
      break;
    }
    case 3:
    {
      json = std::get<3>(property->_value);
      break;
    }
    case 4:
    {
      json = std::get<4>(property->_value);
      break;
    }
    case 5:
    {
      json = std::get<5>(property->_value);
      break;
    }
    case 6:
    {
      for (const auto& [key, value] : std::get<6>(property->_value))
      {
        if (value)
        {
          json[key] = ToJSON(value, binaries);
        }
      }
      break;
    }
    case 7:
    {
      for (const auto& value : std::get<7>(property->_value))
      {
        if (value)
        {
          json.push_back(ToJSON(value, binaries));
        }
      }
      break;
    }
    case 8:
    {
      const auto& raw = std::get<8>(property->_value);
      const auto [bytes, size] = raw.GetBytes(0);

      digestpp::md5 hash_provider;
      const auto hash = hash_provider.absorb((uint8_t*)bytes, size).hexdigest();

      auto encode = std::string().assign(hash.length() + hash.length() / 2, '-');
      for (size_t i = 0; i < hash.length() / 2; ++i)
      {
        encode[3 * i + 1] = hash[2 * i + 0];
        encode[3 * i + 2] = hash[2 * i + 1];
      }

      json = encode;

      binaries[property] = encode;

      break;
    }
    }

    return json;
  }

  std::shared_ptr<Property> Property::FromJSON(const nlohmann::json& node, std::map<std::shared_ptr<Property>, std::string>& binaries)
  {
    std::shared_ptr<Property> property;

    switch (node.type())
    {
    case nlohmann::json::value_t::null:
    {
      property.reset(new Property(TYPE_UNDEFINED));
      break;
    }
    case nlohmann::json::value_t::object:
    {
      property.reset(new Property(TYPE_OBJECT));
      for (auto it = node.begin(); it != node.end(); ++it)
      {
        auto child = FromJSON(it.value(), binaries);
        if (child)
        {
          property->SetObjectItem(it.key(), child);
        }
      }
      break;
    }
    case nlohmann::json::value_t::array:
    {
      property.reset(new Property(TYPE_ARRAY));
      property->SetArraySize(static_cast<uint32_t>(node.size()));
      for (uint32_t i = 0; i < static_cast<uint32_t>(node.size()); ++i)
      {
        auto child = FromJSON(node[i], binaries);
        if (child)
        {
          property->SetArrayItem(i, child);
        }
      }
      break;
    }
    case nlohmann::json::value_t::string:
    {
      const auto value = std::string(node);
      if (value.length() == 48)
      {
        if (std::regex_match(value, std::regex("^(-[a-f0-9][a-f0-9]){16}$")))
        {
          property.reset(new Property(TYPE_RAW));
          binaries[property] = value;
        }
      }
      else
      {
        property.reset(new Property(TYPE_STRING));
        property->SetString(node);
      }
      break;
    }
    case nlohmann::json::value_t::boolean:
    {
      property.reset(new Property(TYPE_BOOL));
      property->SetBool(node);
      break;
    }
    case nlohmann::json::value_t::number_integer:
    {
      property.reset(new Property(TYPE_SINT));
      property->SetSint(node);
      break;
    }
    case nlohmann::json::value_t::number_unsigned:
    {
      property.reset(new Property(TYPE_UINT));
      property->SetUint(node);
      break;
    }
    case nlohmann::json::value_t::number_float:
    {
      property.reset(new Property(TYPE_REAL));
      property->SetReal(node);
      break;
    }
    case nlohmann::json::value_t::discarded:
    {
      break;
    }
    }

    return property;
  }

  std::shared_ptr<Property> ParseJSON(const nlohmann::json& node)
  {
    std::shared_ptr<Property> property;

    switch (node.type())
    {
    case nlohmann::json::value_t::null:
    {
      property.reset(new Property(Property::TYPE_UNDEFINED));
      break;
    }
    case nlohmann::json::value_t::object:
    {
      property.reset(new Property(Property::TYPE_OBJECT));
      for (auto it = node.begin(); it != node.end(); ++it)
      {
        const auto& child_node = it.value();
        const auto& child_name = it.key();
        const auto child_property = ParseJSON(child_node);
        if (child_property)
        {
          property->SetObjectItem(child_name, child_property);
        }
      }
      break;
    }
    case nlohmann::json::value_t::array:
    {
      property.reset(new Property(Property::TYPE_ARRAY));
      property->SetArraySize(static_cast<uint32_t>(node.size()));
      for (uint32_t i = 0; i < static_cast<uint32_t>(node.size()); ++i)
      {
        const auto& child_node = node[i];
        const auto& child_index = i;
        const auto child_property = ParseJSON(child_node);
        if (child_property)
        {
          property->SetArrayItem(child_index, child_property);
        }
      }
      break;
    }
    case nlohmann::json::value_t::string:
    {
      property.reset(new Property(Property::TYPE_STRING));
      property->SetString(node);
      break;
    }
    case nlohmann::json::value_t::boolean:
    {
      property.reset(new Property(Property::TYPE_BOOL));
      property->SetBool(node);
      break;
    }
    case nlohmann::json::value_t::number_integer:
    {
      property.reset(new Property(Property::TYPE_SINT));
      property->SetSint(node);
      break;
    }
    case nlohmann::json::value_t::number_unsigned:
    {
      property.reset(new Property(Property::TYPE_UINT));
      property->SetUint(node);
      break;
    }
    case nlohmann::json::value_t::number_float:
    {
      property.reset(new Property(Property::TYPE_REAL));
      property->SetReal(node);
      break;
    }
    case nlohmann::json::value_t::discarded:
    {
      break;
    }
    }

    return property;
  }




  std::shared_ptr<Property> CreateFMat3x4Property()
  {
    auto property = std::shared_ptr<Property>(new Property(Property::TYPE_ARRAY));
    property->SetArraySize(12);
    for (uint32_t i = 0; i < property->GetArraySize(); ++i)
    {
      auto temp = std::shared_ptr<Property>(new Property(Property::TYPE_REAL));
      temp->SetReal(0.0f);
      property->SetArrayItem(i, temp);
    }
    return property;
  }

  std::shared_ptr<Property> CreateFVec4Property()
  {
    auto property = std::shared_ptr<Property>(new Property(Property::TYPE_ARRAY));
    property->SetArraySize(4);

    for (uint32_t i = 0; i < property->GetArraySize(); ++i)
    {
      auto temp = std::shared_ptr<Property>(new Property(Property::TYPE_REAL));
      temp->SetReal(0.0f);
      property->SetArrayItem(i, temp);
    }

    return property;
  }

  std::shared_ptr<Property> CreateFVec3Property()
  {
    auto property = std::shared_ptr<Property>(new Property(Property::TYPE_ARRAY));
    property->SetArraySize(3);

    for (uint32_t i = 0; i < property->GetArraySize(); ++i)
    {
      auto temp = std::shared_ptr<Property>(new Property(Property::TYPE_REAL));
      temp->SetReal(0.0f);
      property->SetArrayItem(i, temp);
    }

    return property;
  }

  std::shared_ptr<Property> CreateFVec2Property()
  {
    auto property = std::shared_ptr<Property>(new Property(Property::TYPE_ARRAY));
    property->SetArraySize(2);

    for (uint32_t i = 0; i < property->GetArraySize(); ++i)
    {
      auto temp = std::shared_ptr<Property>(new Property(Property::TYPE_REAL));
      temp->SetReal(0.0f);
      property->SetArrayItem(i, temp);
    }

    return property;
  }

  std::shared_ptr<Property> CreateFloatProperty()
  {
    auto property = std::shared_ptr<Property>(new Property(Property::TYPE_REAL));
    property->SetReal(0.0f);
    return property;
  }

  std::shared_ptr<Property> CreateUVec4Property()
  {
    auto property = std::shared_ptr<Property>(new Property(Property::TYPE_ARRAY));
    property->SetArraySize(4);

    for (uint32_t i = 0; i < property->GetArraySize(); ++i)
    {
      auto temp = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
      temp->SetUint(0);
      property->SetArrayItem(i, temp);
    }

    return property;
  }

  std::shared_ptr<Property> CreateUVec3Property()
  {
    auto property = std::shared_ptr<Property>(new Property(Property::TYPE_ARRAY));
    property->SetArraySize(3);

    for (uint32_t i = 0; i < property->GetArraySize(); ++i)
    {
      auto temp = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
      temp->SetUint(0);
      property->SetArrayItem(i, temp);
    }

    return property;
  }

  std::shared_ptr<Property> CreateUVec2Property()
  {
    auto property = std::shared_ptr<Property>(new Property(Property::TYPE_ARRAY));
    property->SetArraySize(2);

    for (uint32_t i = 0; i < property->GetArraySize(); ++i)
    {
      auto temp = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
      temp->SetUint(0);
      property->SetArrayItem(i, temp);
    }

    return property;
  }

  std::shared_ptr<Property> CreateUIntProperty()
  {
    auto property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    property->SetUint(0);
    return property;
  }

  std::shared_ptr<Property> CreateBufferProperty(const std::pair<const void*, uint32_t>& bytes,
    uint32_t stride, uint32_t count)
  {
    const auto root_property = std::shared_ptr<Property>(new Property(Property::TYPE_OBJECT));

    const auto stride_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    stride_property->SetUint(stride);
    root_property->SetObjectItem("stride", stride_property);

    const auto count_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    count_property->SetUint(count);
    root_property->SetObjectItem("count", count_property);

    const auto bytes_property = std::shared_ptr<Property>(new Property(Property::TYPE_RAW));
    bytes_property->RawAllocate(bytes.second);
    bytes_property->SetRawBytes(bytes, 0);
    root_property->SetObjectItem("bytes", bytes_property);

    return root_property;
  }


  std::shared_ptr<Property> CreateTextureProperty(const std::pair<const void*, uint32_t>& texels,
    uint32_t extent_x, uint32_t extent_y, uint32_t extent_z, Format format, uint32_t mipmap)
  {
    const auto root_property = std::shared_ptr<Property>(new Property(Property::TYPE_OBJECT));

    const auto extent_x_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    extent_x_property->SetUint(extent_x);
    root_property->SetObjectItem("extent_x", extent_x_property);

    const auto extent_y_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    extent_y_property->SetUint(extent_y);
    root_property->SetObjectItem("extent_y", extent_y_property);

    const auto extent_z_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    extent_z_property->SetUint(extent_z);
    root_property->SetObjectItem("extent_z", extent_z_property);

    const auto format_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    format_property->SetUint(format);
    root_property->SetObjectItem("format", format_property);

    const auto mipmap_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    mipmap_property->SetUint(mipmap);
    root_property->SetObjectItem("mipmap", mipmap_property);

    const auto texels_property = std::shared_ptr<Property>(new Property(Property::TYPE_RAW));
    texels_property->RawAllocate(texels.second);
    texels_property->SetRawBytes(texels, 0);
    texels_property->SetObjectItem("texels", texels_property);

    return root_property;
  }


  std::shared_ptr<Property> CreateInstanceProperty(std::vector<Instance>& scene_instances)
  {
    const auto root_property = std::shared_ptr<Property>(new Property(Property::TYPE_ARRAY));
    //root_property->SetValue(Property::array());
    root_property->SetArraySize(static_cast<uint32_t>(scene_instances.size()));

    for (uint32_t i = 0; i < scene_instances.size(); ++i)
    {
      const auto& instance = scene_instances[i];

      const auto item_property = std::shared_ptr<Property>(new Property(Property::TYPE_OBJECT));
      //item_property->SetValue(Property::object());

      const auto transform_property = CreateFMat3x4Property();   transform_property->FromFMat3x4(instance.transform);     item_property->SetObjectItem("transform", transform_property);

      const auto prim_offset_property = CreateUIntProperty();    prim_offset_property->FromUInt(instance.prim_offset);    item_property->SetObjectItem("prim_offset", prim_offset_property);
      const auto prim_count_property = CreateUIntProperty();     prim_count_property->FromUInt(instance.prim_count);      item_property->SetObjectItem("prim_count", prim_count_property);
      const auto vert_offset_property = CreateUIntProperty();    vert_offset_property->FromUInt(instance.vert_offset);    item_property->SetObjectItem("vert_offset", vert_offset_property);
      const auto vert_count_property = CreateUIntProperty();     vert_count_property->FromUInt(instance.vert_count);      item_property->SetObjectItem("vert_count", vert_count_property);

      const auto emission_property = CreateFVec3Property();      emission_property->FromFVec3(instance.emission);         item_property->SetObjectItem("emission", emission_property);
      const auto intensity_property = CreateFloatProperty();     intensity_property->FromFloat(instance.intensity);       item_property->SetObjectItem("intensity", intensity_property);
      const auto diffuse_property = CreateFVec3Property();       diffuse_property->FromFVec3(instance.diffuse);           item_property->SetObjectItem("diffuse", diffuse_property);
      const auto shininess_property = CreateFloatProperty();     shininess_property->FromFloat(instance.shininess);       item_property->SetObjectItem("shininess", shininess_property);
      const auto specular_property = CreateFVec3Property();      specular_property->FromFVec3(instance.specular);         item_property->SetObjectItem("specular", specular_property);
      const auto alpha_property = CreateFloatProperty();         alpha_property->FromFloat(instance.alpha);               item_property->SetObjectItem("ior", alpha_property);

      const auto texture0_idx_property = CreateUIntProperty();   texture0_idx_property->FromUInt(instance.texture0_idx);  item_property->SetObjectItem("texture0_idx", texture0_idx_property);
      const auto texture1_idx_property = CreateUIntProperty();   texture1_idx_property->FromUInt(instance.texture1_idx);  item_property->SetObjectItem("texture1_idx", texture1_idx_property);
      const auto texture2_idx_property = CreateUIntProperty();   texture2_idx_property->FromUInt(instance.texture2_idx);  item_property->SetObjectItem("texture2_idx", texture2_idx_property);
      const auto texture3_idx_property = CreateUIntProperty();   texture3_idx_property->FromUInt(instance.texture3_idx);  item_property->SetObjectItem("texture3_idx", texture3_idx_property);

      const auto debug_color_property = CreateFVec3Property();   debug_color_property->FromFVec3(instance.debug_color);   item_property->SetObjectItem("debug_color", debug_color_property);
      const auto geometry_idx_property = CreateUIntProperty();   geometry_idx_property->FromUInt(instance.geometry_idx);  item_property->SetObjectItem("geometry_idx", geometry_idx_property);

      root_property->SetArrayItem(i, item_property);
    }

    return root_property;
  }


  //std::shared_ptr<Property> ImportEXR(const std::string& path, const std::string& name, float exposure, uint32_t mipmaps)
  //{
  //  int32_t src_tex_x = 0;
  //  int32_t src_tex_y = 0;
  //  int32_t src_tex_n = 4;
  //  float* src_tex_data = nullptr;
  //  BLAST_ASSERT(0 == LoadEXR(&src_tex_data, &src_tex_x, &src_tex_y, (name).c_str(), nullptr));

  //  int32_t dst_tex_x = src_tex_x;
  //  int32_t dst_tex_y = src_tex_y;
  //  int32_t dst_tex_n = 4;
  //  float* dst_tex_data = new float[dst_tex_x * dst_tex_y * dst_tex_n];
  //  for (uint32_t j = 0; j < src_tex_x * src_tex_y; ++j)
  //  {
  //    const auto r = src_tex_n > 0 ? src_tex_data[j * src_tex_n + 0] : 0; //0xFF;
  //    const auto g = src_tex_n > 1 ? src_tex_data[j * src_tex_n + 1] : r; //0xFF;
  //    const auto b = src_tex_n > 2 ? src_tex_data[j * src_tex_n + 2] : r; //0xFF;
  //    const auto a = src_tex_n > 3 ? src_tex_data[j * src_tex_n + 3] : r; //0xFF;
  //    dst_tex_data[j * dst_tex_n + 0] = r * exposure;
  //    dst_tex_data[j * dst_tex_n + 1] = g * exposure;
  //    dst_tex_data[j * dst_tex_n + 2] = b * exposure;
  //    dst_tex_data[j * dst_tex_n + 3] = a * exposure;
  //  }
  //  delete[] src_tex_data;

  //  src_tex_data = dst_tex_data;
  //  src_tex_x = dst_tex_x;
  //  src_tex_y = dst_tex_y;
  //  src_tex_n = dst_tex_n;

  //  const auto get_pot_fn = [](int32_t value)
  //  {
  //    int32_t power = 0;
  //    while ((1 << power) < value) ++power;
  //    return power;
  //  };

  //  const auto pow_tex_x = get_pot_fn(src_tex_x);
  //  const auto pow_tex_y = get_pot_fn(src_tex_y);
  //  const auto pow_delta = std::abs(pow_tex_x - pow_tex_y);

  //  //const uint32_t tex_x = (1 << (pow_tex_x > pow_tex_y ? mipmap_count + pow_delta : mipmap_count)) - 1;
  //  //const uint32_t tex_y = (1 << (pow_tex_y > pow_tex_x ? mipmap_count + pow_delta : mipmap_count)) - 1;
  //  //const uint32_t tex_n = 4;

  //  const auto texel_pow_x = pow_tex_x > pow_tex_y ? mipmaps + pow_delta : mipmaps;
  //  const auto texel_pow_y = pow_tex_y > pow_tex_x ? mipmaps + pow_delta : mipmaps;
  //  const auto texel_count = uint32_t(((1 << texel_pow_x) * (1 << texel_pow_y) - 1) / 3);
  //  const auto texel_stride = uint32_t(sizeof(glm::f32vec4));
  //  float* texel_data = new float[texel_count * 4];

  //  dst_tex_x = 1 << (texel_pow_x - 1);
  //  dst_tex_y = 1 << (texel_pow_y - 1);
  //  dst_tex_n = src_tex_n;
  //  dst_tex_data = texel_data;
  //  stbir_resize_float(src_tex_data, src_tex_x, src_tex_y, 0, dst_tex_data, dst_tex_x, dst_tex_y, 0, dst_tex_n);
  //  delete[] src_tex_data;

  //  //const auto size_x_property = std::shared_ptr<Property>(new Property());
  //  //size_x_property->SetValue(uint32_t(dst_tex_x));

  //  //const auto size_y_property = std::shared_ptr<Property>(new Property());
  //  //size_y_property->SetValue(uint32_t(dst_tex_y));

  //  //const auto mipmaps_property = std::shared_ptr<Property>(new Property());
  //  //mipmaps_property->SetValue(uint32_t(mipmaps));

  //  src_tex_data = dst_tex_data;
  //  src_tex_x = dst_tex_x;
  //  src_tex_y = dst_tex_y;
  //  src_tex_n = dst_tex_n;

  //  for (uint32_t i = 1; i < mipmaps; ++i)
  //  {
  //    dst_tex_x = src_tex_x >> 1;
  //    dst_tex_y = src_tex_y >> 1;
  //    dst_tex_n = src_tex_n;
  //    dst_tex_data += src_tex_x * src_tex_y * src_tex_n;
  //    stbir_resize_float(src_tex_data, src_tex_x, src_tex_y, 0, dst_tex_data, dst_tex_x, dst_tex_y, 0, dst_tex_n);

  //    src_tex_data = dst_tex_data;
  //    src_tex_x = dst_tex_x;
  //    src_tex_y = dst_tex_y;
  //    src_tex_n = dst_tex_n;
  //  }

  //  const auto texels_property = std::shared_ptr<Property>(new Property(Property::TYPE_RAW));
  //  {
  //    texels_property->RawAllocate(texel_count * texel_stride);
  //    texels_property->SetRawBytes({ texel_data, texel_count * texel_stride }, 0);
  //  }
  //  delete[] texel_data;

  //  const auto texture_property = std::shared_ptr<Property>(new Property(Property::TYPE_ARRAY));
  //  //texture_property->SetValue(Property::array());
  //  texture_property->SetArraySize(1);
  //  texture_property->SetArrayItem(0, texels_property);

  //  return texture_property;
  //}


  void SaveProperty(const std::string& directory, const std::string& name, const std::shared_ptr<Property>& root)
  {
    std::map<std::shared_ptr<Property>, std::string> binaries;
    auto json = Property::ToJSON(root, binaries);
    {
      std::string file_name = directory + name + std::string(".json");
      std::ofstream file_stream(file_name, std::ios::out);
      file_stream << std::setw(4) << json << std::endl;
      file_stream.close();
    }

    for (auto& [key, value] : binaries)
    {
      std::string file_name = std::string("cache/") + name + value;
      std::ofstream file_stream(file_name, std::ios::out | std::ios::binary);

      const auto [byte, size] = key->GetRawBytes(0);
      file_stream.write(reinterpret_cast<const char*>(byte), size);
      file_stream.close();
    }
  }


  std::shared_ptr<Property> LoadProperty(const std::string& directory, const std::string& name)
  {
    nlohmann::json json;
    {
      std::string file_name = directory + name + std::string(".json");
      std::ifstream file_stream(file_name, std::ios::in);
      file_stream >> std::setw(4) >> json;
      file_stream.close();
    }

    std::map<std::shared_ptr<Property>, std::string> binaries;
    const auto root = Property::FromJSON(json, binaries);

    for (auto& [key, value] : binaries)
    {
      std::string file_name = std::string("cache/") + name + value;
      std::ifstream file_stream(file_name, std::ios::in | std::ios::binary);

      file_stream.seekg(0, std::ios::end);
      const size_t size = file_stream.tellg();
      file_stream.seekg(0, std::ios::beg);

      auto data = new char[size];
      file_stream.read(data, size);
      file_stream.close();

      key->RawAllocate(uint32_t(size));
      key->SetRawBytes({ data, uint32_t(size) }, 0);

      delete[] data;
    }

    return root;
  }

  void ExportTextureLDR(const std::string& path, const std::shared_ptr<Property>& root)
  {
    const auto extent_x = root->GetObjectItem("extent_x")->GetUint();
    const auto extent_y = root->GetObjectItem("extent_y")->GetUint();
    const auto extent_z = root->GetObjectItem("extent_z")->GetUint();
    const auto format = root->GetObjectItem("format")->GetUint();
    const auto mipmap = root->GetObjectItem("mipmap")->GetUint();
    const auto texels = root->GetObjectItem("texels")->GetRawBytes(0);

    const auto extension = ExtractExtension(path);

    if (std::strcmp(extension.c_str(), "png") == 0)
    {
      BLAST_ASSERT(0 != stbi_write_png(path.c_str(), extent_x, extent_y, 3, texels.first, 4 * extent_x));
    }
    else if (std::strcmp(extension.c_str(), "jpg") == 0)
    {
      BLAST_ASSERT(0 != stbi_write_jpg(path.c_str(), extent_x, extent_y, 3, texels.first, 80));
    }
  }

  Image<glm::u8vec4> LoadImageLDR(const std::string& path)
  {
    auto extent_x = 0;
    auto extent_y = 0;
    auto channels = 0;
    auto data = stbi_load(path.c_str(), &extent_x, &extent_y, &channels, STBI_default);

    auto result = Image<glm::u8vec4>(extent_x, extent_y);
    for (int32_t i = 0; i < extent_y; ++i)
    {
      for (int32_t j = 0; j < extent_x; ++j)
      {
        const auto idx = i * extent_x + j;
        const auto r = channels > 0 ? data[idx * channels + 0] : 0; //0xFF;
        const auto g = channels > 1 ? data[idx * channels + 1] : r; //0xFF;
        const auto b = channels > 2 ? data[idx * channels + 2] : r; //0xFF;
        const auto a = channels > 3 ? data[idx * channels + 3] : r; //0xFF;
        result.SetTexel(i, j, glm::u8vec4{ r, g, b, a });
      }
    }
    stbi_image_free(data);

    return result;
  }

  Image<glm::u8vec4> ResizeImageLDR(const Image<glm::u8vec4>& src_image, uint32_t dst_extent_x, uint32_t dst_extent_y)
  {
    const auto dst_channels = 4;
    const auto dst_image = Image<glm::u8vec4>(dst_extent_x, dst_extent_y);
    auto dst_data = reinterpret_cast<uint8_t*>(dst_image.AccessTexels().first);

    const auto src_extent_x = src_image.GetExtentX();
    const auto src_extent_y = src_image.GetExtentY();
    const auto src_data = reinterpret_cast<const uint8_t*>(src_image.AccessTexels().first);

    stbir_resize_uint8(src_data, src_extent_x, src_extent_y, 0, dst_data, dst_extent_x, dst_extent_y, 0, dst_channels);

    return dst_image;
  }

  std::shared_ptr<Property> ImportTextureLDR(const std::string& path, uint32_t mipmap)
  {
    const auto src_image = LoadImageLDR(path);

    //src_extent_x = dst_extent_x;
    //src_extent_y = dst_extent_y;
    //src_channels = dst_channels;
    //src_data = dst_data;

    const auto mipmap_count_fn = [](int32_t value)
    { 
      int32_t power = 0;
      while ((value >> power) > 0) ++power;
      return power;
    };

    const auto mipmap_x = mipmap_count_fn(src_image.GetExtentX());
    const auto mipmap_y = mipmap_count_fn(src_image.GetExtentY());
    const auto extent_x = 1 << (int32_t(mipmap) - (mipmap_x > mipmap_y ? 0 : mipmap_y - mipmap_x));
    const auto extent_y = 1 << (int32_t(mipmap) - (mipmap_y > mipmap_x ? 0 : mipmap_x - mipmap_y));

    const auto channels = 4;
    const auto size = (extent_x * extent_y - 1) / 3 * channels;
    const auto data = new uint8_t[size];

    dst_extent_x = extent_x;
    dst_extent_y = extent_y;
    dst_channels = channels;
    dst_data = data;

    stbir_resize_uint8(src_data, src_extent_x, src_extent_y, 0, dst_data, dst_extent_x, dst_extent_y, 0, dst_channels);
    delete[] src_data;

    src_extent_x = dst_extent_x;
    src_extent_y = dst_extent_y;
    src_channels = dst_channels;
    src_data = dst_data;

    for (uint32_t i = 1; i < mipmap; ++i)
    {
      dst_extent_x = std::min(1, src_extent_x / 2);
      dst_extent_y = std::min(1, src_extent_y / 2);
      dst_channels = src_channels;
      dst_data += src_extent_x * src_extent_y * src_channels;
      stbir_resize_uint8(src_data, src_extent_x, src_extent_y, 0, dst_data, dst_extent_x, dst_extent_y, 0, dst_channels);

      src_extent_x = dst_extent_x;
      src_extent_y = dst_extent_y;
      src_channels = dst_channels;
      src_data = dst_data;
    }

    const auto root = CreateTextureProperty({ data, size }, extent_x, extent_y, 1, FORMAT_R8G8B8A8_UNORM, mipmap);
    
    delete[] data;

    return root;
  }


  void ExportTextureHDR(const std::string& path, const std::shared_ptr<Property>& root)
  {}

  std::shared_ptr<Property> ImportTextureHDR(const std::string& path, uint32_t mipmap)
  {
    int32_t src_extent_x = 0;
    int32_t src_extent_y = 0;
    int32_t src_channels = 0;
    float* src_data = stbi_loadf(path.c_str(), &src_extent_x, &src_extent_y, &src_channels, STBI_default);

    int32_t dst_extent_x = src_extent_x;
    int32_t dst_extent_y = src_extent_y;
    int32_t dst_channels = 4;
    float* dst_data = new float[dst_extent_x * dst_extent_y * dst_channels];

    for (int32_t i = 0; i < src_extent_x * src_extent_y; ++i)
    {
      const float r = src_channels > 0 ? src_data[i * src_channels + 0] : 0;
      const float g = src_channels > 1 ? src_data[i * src_channels + 1] : r;
      const float b = src_channels > 2 ? src_data[i * src_channels + 2] : r;
      const float a = src_channels > 3 ? src_data[i * src_channels + 3] : r;
      dst_data[i * src_channels + 0] = r;
      dst_data[i * src_channels + 1] = g;
      dst_data[i * src_channels + 2] = b;
      dst_data[i * src_channels + 3] = a;
    }
    stbi_image_free(src_data);

    src_extent_x = dst_extent_x;
    src_extent_y = dst_extent_y;
    src_channels = dst_channels;
    src_data = dst_data;

    const auto mipmap_count_fn = [](int32_t value)
      {
        int32_t power = 0;
        while ((value >> power) > 0) ++power;
        return power;
      };

    const auto mipmap_x = mipmap_count_fn(src_extent_x);
    const auto mipmap_y = mipmap_count_fn(src_extent_y);
    const auto extent_x = 1 << (int32_t(mipmap) - (mipmap_x > mipmap_y ? 0 : mipmap_y - mipmap_x));
    const auto extent_y = 1 << (int32_t(mipmap) - (mipmap_y > mipmap_x ? 0 : mipmap_x - mipmap_y));
    //const auto mipmap_x = mipmap;
    //const auto mipmap_y = mipmap;
    //const auto extent_x = 1 << mipmap_x;
    //const auto extent_y = 1 << mipmap_y;
    const auto channels = 4;
    const auto size = (extent_x * extent_y - 1) / 3 * channels;
    const auto data = new float[size];

    dst_extent_x = extent_x;
    dst_extent_y = extent_y;
    dst_channels = channels;
    dst_data = data;

    stbir_resize_float(src_data, src_extent_x, src_extent_y, 0, dst_data, dst_extent_x, dst_extent_y, 0, dst_channels);
    delete[] src_data;

    src_extent_x = dst_extent_x;
    src_extent_y = dst_extent_y;
    src_channels = dst_channels;
    src_data = dst_data;

    for (uint32_t i = 1; i < mipmap; ++i)
    {
      dst_extent_x = std::min(1, src_extent_x / 2);
      dst_extent_y = std::min(1, src_extent_y / 2);
      dst_channels = src_channels;
      dst_data += src_extent_x * src_extent_y * dst_channels;
      stbir_resize_float(src_data, src_extent_x, src_extent_y, 0, dst_data, dst_extent_x, dst_extent_y, 0, dst_channels);

      src_extent_x = dst_extent_x;
      src_extent_y = dst_extent_y;
      src_channels = dst_channels;
      src_data = dst_data;
    }

    const auto root = CreateTextureProperty({ data, size }, extent_x, extent_y, 1, FORMAT_R32G32B32A32_FLOAT, mipmap);

    delete[] data;

    return root;
  }

  //void ExportBuffer(const std::string& path, const std::shared_ptr<Property>& root)
  //{}

  //std::shared_ptr<Property> ImportBuffer(const std::string& path, uint32_t stride)
  //{}


  //void SaveToPNG(const std::string& file_path, std::pair<const void*, uint32_t> bytes, uint32_t width, uint32_t height)
  //{
  //  const auto src_tex_data = stbi_write_png(file_path.c_str(), width, height, 3, bytes.first, 4 * width);
  //}


  //std::tuple<std::pair<const void*, uint32_t>, int32_t, int32_t> LoadTextureFromFile(const std::string& path_name, bool gamma)
  //{
  //  int32_t src_tex_x = 0;
  //  int32_t src_tex_y = 0;
  //  int32_t src_tex_n = 0;
  //  unsigned char* src_tex_data = stbi_load(path_name.c_str(), &src_tex_x, &src_tex_y, &src_tex_n, STBI_default);

  //  if (gamma)
  //  {
  //    const auto gamma_value = 2.2f;
  //    for (uint32_t i = 0; i < src_tex_x * src_tex_y; ++i)
  //    {
  //      if (src_tex_n > 0) src_tex_data[i * src_tex_n + 0] = uint8_t(255.0f * std::pow(src_tex_data[i * src_tex_n + 0] / 255.0f, gamma_value));
  //      if (src_tex_n > 1) src_tex_data[i * src_tex_n + 1] = uint8_t(255.0f * std::pow(src_tex_data[i * src_tex_n + 1] / 255.0f, gamma_value));
  //      if (src_tex_n > 2) src_tex_data[i * src_tex_n + 2] = uint8_t(255.0f * std::pow(src_tex_data[i * src_tex_n + 2] / 255.0f, gamma_value));
  //    }
  //  }

  //  int32_t dst_tex_x = src_tex_x;
  //  int32_t dst_tex_y = src_tex_y;
  //  int32_t dst_tex_n = 4;

  //  const auto dst_tex_size = dst_tex_x * dst_tex_y * dst_tex_n;
  //  auto* dst_tex_data = new unsigned char[dst_tex_size];
  //  for (uint32_t j = 0; j < src_tex_x * src_tex_y; ++j)
  //  {
  //    const uint8_t r = src_tex_n > 0 ? src_tex_data[j * src_tex_n + 0] : 0; //0xFF;
  //    const uint8_t g = src_tex_n > 1 ? src_tex_data[j * src_tex_n + 1] : r; //0xFF;
  //    const uint8_t b = src_tex_n > 2 ? src_tex_data[j * src_tex_n + 2] : r; //0xFF;
  //    const uint8_t a = src_tex_n > 3 ? src_tex_data[j * src_tex_n + 3] : r; //0xFF;
  //    dst_tex_data[j * dst_tex_n + 0] = r;
  //    dst_tex_data[j * dst_tex_n + 1] = g;
  //    dst_tex_data[j * dst_tex_n + 2] = b;
  //    dst_tex_data[j * dst_tex_n + 3] = a;

  //  }
  //  stbi_image_free(src_tex_data);

  //  src_tex_data = dst_tex_data;
  //  src_tex_x = dst_tex_x;
  //  src_tex_y = dst_tex_y;
  //  src_tex_n = dst_tex_n;

  //  const auto tex_x = src_tex_x;
  //  const auto tex_y = src_tex_y;

  //  return { { dst_tex_data, dst_tex_size }, tex_x, tex_y };
  //}

  //std::shared_ptr<Property> CreatePropertyFromTexture(std::pair<const void*, uint32_t> bytes, int32_t tex_x, int32_t tex_y, uint32_t mipmaps)
  //{
  //  const auto mipmap_count_fn = [](uint32_t value)
  //  {
  //    uint32_t power = 0;
  //    while ((value >> power) > 0) ++power;
  //    return power;
  //  };
  //  mipmaps = mipmaps > 0 ? mipmaps : std::min(mipmap_count_fn(tex_x), mipmap_count_fn(tex_y));

  //  //const uint32_t tex_x = (1 << mipmaps) - 1;
  //  //const uint32_t tex_y = (1 << mipmaps) - 1;
  //  //const uint32_t tex_n = 4;

  //  const auto texel_count = uint32_t(((1 << mipmaps) * (1 << mipmaps) - 1) / 3);
  //  const auto texel_stride = uint32_t(sizeof(glm::u8vec4));
  //  unsigned char* texel_data = new unsigned char[texel_count * 4];

  //  auto dst_tex_x = 1 << (mipmaps - 1);
  //  auto dst_tex_y = 1 << (mipmaps - 1);
  //  auto dst_tex_n = 4;
  //  auto dst_tex_data = texel_data;

  //  stbir_resize_uint8(reinterpret_cast<const unsigned char*>(bytes.first), tex_x, tex_y, 0, dst_tex_data, dst_tex_x, dst_tex_y, 0, 4);

  //  auto src_tex_x = dst_tex_x;
  //  auto src_tex_y = dst_tex_y;
  //  auto src_tex_n = dst_tex_n;
  //  auto src_tex_data = dst_tex_data;

  //  for (uint32_t i = 1; i < mipmaps; ++i)
  //  {
  //    dst_tex_x = 1 << (mipmaps - 1 - i);
  //    dst_tex_y = 1 << (mipmaps - 1 - i);
  //    dst_tex_n = src_tex_n;
  //    dst_tex_data += src_tex_x * src_tex_y * src_tex_n;
  //    stbir_resize_uint8(src_tex_data, src_tex_x, src_tex_y, 0, dst_tex_data, dst_tex_x, dst_tex_y, 0, dst_tex_n);

  //    src_tex_data = dst_tex_data;
  //    src_tex_x = dst_tex_x;
  //    src_tex_y = dst_tex_y;
  //    src_tex_n = dst_tex_n;
  //  }


  //  const auto texels_property = std::shared_ptr<Property>(new Property(Property::TYPE_RAW));
  //  {
  //    texels_property->RawAllocate(texel_count * texel_stride);
  //    texels_property->SetRawBytes({ texel_data, texel_count * texel_stride }, 0);
  //  }
  //  delete[] texel_data;

  //  return texels_property;
  //}


  //std::shared_ptr<Property> CreatePropertyFromTextures(const std::vector<Texture>& textures, uint32_t mipmaps)
  //{
  //  auto textures_property = std::shared_ptr<Property>(new Property(Property::TYPE_ARRAY));

  //  if (textures.empty())
  //  {
  //    textures_property->SetArraySize(uint32_t(1));

  //    const auto texel_value = glm::u8vec4(255, 255, 255, 255);
  //    const auto texel_size = uint32_t(sizeof(texel_value));

  //    const auto texels_property = std::shared_ptr<Property>(new Property(Property::TYPE_RAW));
  //    texels_property->RawAllocate(texel_size);
  //    texels_property->SetRawBytes({ &texel_value, texel_size }, 0);
  //    textures_property->SetArrayItem(0, texels_property);
  //  }
  //  else
  //  {
  //    textures_property->SetArraySize(uint32_t(textures.size()));
  //    for (uint32_t i = 0; i < textures_property->GetArraySize(); ++i)
  //    {
  //      const Texture& texture = textures[i];

  //      const auto tex_x = int32_t(texture.extent_x);
  //      const auto tex_y = int32_t(texture.extent_y);
  //      const auto tex_data = reinterpret_cast<const void*>(texture.texels.data());
  //      const auto tex_size = uint32_t(texture.texels.size() * sizeof(glm::u8vec4));

  //      const auto mipmaps_property = CreatePropertyFromTexture(std::pair(tex_data, tex_size), tex_x, tex_y, mipmaps);

  //      textures_property->SetArrayItem(i, mipmaps_property);
  //    }
  //  }
  //  return textures_property;
  //}
}