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

  //std::shared_ptr<Property> CreateBufferProperty(const std::pair<const void*, uint32_t>& bytes,
  //  uint32_t stride, uint32_t count)
  //{
  //  const auto root_property = std::shared_ptr<Property>(new Property(Property::TYPE_OBJECT));

  //  const auto stride_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
  //  stride_property->SetUint(stride);
  //  root_property->SetObjectItem("stride", stride_property);

  //  const auto count_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
  //  count_property->SetUint(count);
  //  root_property->SetObjectItem("count", count_property);

  //  const auto bytes_property = std::shared_ptr<Property>(new Property(Property::TYPE_RAW));
  //  bytes_property->RawAllocate(bytes.second);
  //  bytes_property->SetRawBytes(bytes, 0);
  //  root_property->SetObjectItem("bytes", bytes_property);

  //  return root_property;
  //}


  std::shared_ptr<Property> CreateTextureProperty(std::pair<Raw*, uint32_t> raws,
    Format format, uint32_t size_x, uint32_t size_y, uint32_t size_z, uint32_t mipmap, uint32_t layers)
  {
    const auto root_property = std::shared_ptr<Property>(new Property(Property::TYPE_OBJECT));

    const auto format_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    format_property->SetUint(size_x);
    root_property->SetObjectItem("format", format_property);

    const auto size_x_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    size_x_property->SetUint(size_x);
    root_property->SetObjectItem("size_x", size_x_property);

    const auto size_y_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    size_y_property->SetUint(size_y);
    root_property->SetObjectItem("size_y", size_y_property);

    const auto size_z_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    size_z_property->SetUint(size_z);
    root_property->SetObjectItem("size_z", size_z_property);

    const auto mipmap_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    mipmap_property->SetUint(mipmap);
    root_property->SetObjectItem("mipmap", mipmap_property);

    const auto layers_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    layers_property->SetUint(layers);
    root_property->SetObjectItem("layers", layers_property);

    const auto raws_property = std::shared_ptr<Property>(new Property(Property::TYPE_ARRAY));
    raws_property->SetArraySize(raws.second);
    root_property->SetObjectItem("raws", raws_property);

    for (auto i = 0u; i < raws.second; ++i)
    {
      const auto raw_property = std::shared_ptr<Property>(new Property(Property::TYPE_RAW));
      raw_property->SetRaw(std::move(raws.first[i]));
      raws_property->SetArrayItem(i, raw_property);
    }

    return root_property;
  }

  std::shared_ptr<Property> CreateBufferProperty(Raw&& raw, uint32_t stride, uint32_t count)
  {
    const auto root_property = std::shared_ptr<Property>(new Property(Property::TYPE_OBJECT));

    const auto stride_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    stride_property->SetUint(stride);
    root_property->SetObjectItem("stride", stride_property);

    const auto count_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    count_property->SetUint(count);
    root_property->SetObjectItem("count", count_property);

    const auto raw_property = std::shared_ptr<Property>(new Property(Property::TYPE_RAW));
    raw_property->SetRaw(std::move(raw));
    root_property->SetObjectItem("raw", raw_property);

    return root_property;
  }


  //std::shared_ptr<Property> CreateInstanceProperty(std::vector<Instance>& scene_instances)
  //{
  //  const auto root_property = std::shared_ptr<Property>(new Property(Property::TYPE_ARRAY));
  //  //root_property->SetValue(Property::array());
  //  root_property->SetArraySize(static_cast<uint32_t>(scene_instances.size()));

  //  for (uint32_t i = 0; i < scene_instances.size(); ++i)
  //  {
  //    const auto& instance = scene_instances[i];

  //    const auto item_property = std::shared_ptr<Property>(new Property(Property::TYPE_OBJECT));
  //    //item_property->SetValue(Property::object());

  //    const auto transform_property = CreateFMat3x4Property();   transform_property->FromFMat3x4(instance.transform);     item_property->SetObjectItem("transform", transform_property);

  //    const auto prim_offset_property = CreateUIntProperty();    prim_offset_property->FromUInt(instance.prim_offset);    item_property->SetObjectItem("prim_offset", prim_offset_property);
  //    const auto prim_count_property = CreateUIntProperty();     prim_count_property->FromUInt(instance.prim_count);      item_property->SetObjectItem("prim_count", prim_count_property);
  //    const auto vert_offset_property = CreateUIntProperty();    vert_offset_property->FromUInt(instance.vert_offset);    item_property->SetObjectItem("vert_offset", vert_offset_property);
  //    const auto vert_count_property = CreateUIntProperty();     vert_count_property->FromUInt(instance.vert_count);      item_property->SetObjectItem("vert_count", vert_count_property);

  //    const auto brdf_param0_property = CreateFVec4Property();   brdf_param0_property->FromFVec4(instance.brdf_param0);   item_property->SetObjectItem("brdf_param0", brdf_param0_property);
  //    const auto brdf_param1_property = CreateFVec4Property();   brdf_param1_property->FromFVec4(instance.brdf_param1);   item_property->SetObjectItem("brdf_param1", brdf_param1_property);
  //    const auto brdf_param2_property = CreateFVec4Property();   brdf_param2_property->FromFVec4(instance.brdf_param2);   item_property->SetObjectItem("brdf_param2", brdf_param2_property);
  //    const auto brdf_param3_property = CreateFVec4Property();   brdf_param3_property->FromFVec4(instance.brdf_param3);   item_property->SetObjectItem("brdf_param3", brdf_param3_property);

  //    const auto texture0_idx_property = CreateUIntProperty();   texture0_idx_property->FromUInt(instance.texture0_idx);  item_property->SetObjectItem("texture0_idx", texture0_idx_property);
  //    const auto texture1_idx_property = CreateUIntProperty();   texture1_idx_property->FromUInt(instance.texture1_idx);  item_property->SetObjectItem("texture1_idx", texture1_idx_property);
  //    const auto texture2_idx_property = CreateUIntProperty();   texture2_idx_property->FromUInt(instance.texture2_idx);  item_property->SetObjectItem("texture2_idx", texture2_idx_property);
  //    const auto texture3_idx_property = CreateUIntProperty();   texture3_idx_property->FromUInt(instance.texture3_idx);  item_property->SetObjectItem("texture3_idx", texture3_idx_property);
  //    const auto texture4_idx_property = CreateUIntProperty();   texture4_idx_property->FromUInt(instance.texture4_idx);  item_property->SetObjectItem("texture4_idx", texture4_idx_property);
  //    const auto texture5_idx_property = CreateUIntProperty();   texture5_idx_property->FromUInt(instance.texture5_idx);  item_property->SetObjectItem("texture5_idx", texture5_idx_property);
  //    const auto texture6_idx_property = CreateUIntProperty();   texture6_idx_property->FromUInt(instance.texture6_idx);  item_property->SetObjectItem("texture6_idx", texture6_idx_property);
  //    const auto texture7_idx_property = CreateUIntProperty();   texture7_idx_property->FromUInt(instance.texture7_idx);  item_property->SetObjectItem("texture7_idx", texture7_idx_property);

  //    const auto aabb_min_property = CreateFVec3Property();      aabb_min_property->FromFVec3(instance.aabb_min);         item_property->SetObjectItem("aabb_min", aabb_min_property);
  //    const auto geom_idx_property = CreateFVec4Property();      geom_idx_property->FromUInt(instance.geom_idx);          item_property->SetObjectItem("geom_idx", geom_idx_property);
  //    const auto aabb_max_property = CreateFVec3Property();      aabb_max_property->FromFVec3(instance.aabb_max);         item_property->SetObjectItem("aabb_max", aabb_max_property);
  //    const auto brdf_idx_property = CreateFVec4Property();      brdf_idx_property->FromUInt(instance.brdf_idx);          item_property->SetObjectItem("brdf_idx", brdf_idx_property);

  //    const auto buffer0_idx_property = CreateUIntProperty();    buffer0_idx_property->FromUInt(instance.buffer0_idx);    item_property->SetObjectItem("buffer0_idx", buffer0_idx_property);
  //    const auto buffer1_idx_property = CreateUIntProperty();    buffer1_idx_property->FromUInt(instance.buffer1_idx);    item_property->SetObjectItem("buffer1_idx", buffer1_idx_property);
  //    const auto buffer2_idx_property = CreateUIntProperty();    buffer2_idx_property->FromUInt(instance.buffer2_idx);    item_property->SetObjectItem("buffer2_idx", buffer2_idx_property);
  //    const auto buffer3_idx_property = CreateUIntProperty();    buffer3_idx_property->FromUInt(instance.buffer3_idx);    item_property->SetObjectItem("buffer3_idx", buffer3_idx_property);
  //    const auto buffer4_idx_property = CreateUIntProperty();    buffer4_idx_property->FromUInt(instance.buffer4_idx);    item_property->SetObjectItem("buffer4_idx", buffer4_idx_property);
  //    const auto buffer5_idx_property = CreateUIntProperty();    buffer5_idx_property->FromUInt(instance.buffer5_idx);    item_property->SetObjectItem("buffer5_idx", buffer5_idx_property);
  //    const auto buffer6_idx_property = CreateUIntProperty();    buffer6_idx_property->FromUInt(instance.buffer6_idx);    item_property->SetObjectItem("buffer6_idx", buffer6_idx_property);
  //    const auto buffer7_idx_property = CreateUIntProperty();    buffer7_idx_property->FromUInt(instance.buffer7_idx);    item_property->SetObjectItem("buffer7_idx", buffer7_idx_property);

  //    root_property->SetArrayItem(i, item_property);
  //  }

  //  return root_property;
  //}


  //std::shared_ptr<Property> CreateStructureBufferProperty(const StructureBuffer& buffer)
  //{

  //}

  //std::shared_ptr<Property> CreateTextureArrayLDRProperty(const TextureArrayLDR& array, size_t mipmap)
  //{ }

  //std::shared_ptr<Property> CreateTextureArrayHDRProperty(const TextureArrayHDR& array, size_t mipmap)
  //{ }


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

      auto data = new uint8_t[size];
      file_stream.read(reinterpret_cast<char*>(data), size);
      file_stream.close();

      key->AllocateRaw(uint32_t(size));
      key->SetRawBytes({ data, uint32_t(size) }, 0);

      delete[] data;
    }

    return root;
  }


  //std::tuple<Raw, uint32_t, uint32_t> LoadTextureLDR(const std::string& path)
  //{
  //  

  //  return { std::move(raw), uint32_t(extent_x), uint32_t(extent_y) };
  //}

  //std::tuple<Raw, uint32_t, uint32_t> ResizeTextureLDR(uint32_t extent_x, uint32_t extent_y,
  //  const std::tuple<Raw, uint32_t, uint32_t>& texture)
  //{
  //  

  //  return { std::move(raw), extent_x, extent_y };
  //}

  //std::tuple<std::vector<Raw>, uint32_t, uint32_t> MipmapTextureLDR(uint32_t mipmap, const std::tuple<Raw, uint32_t, uint32_t>& texture)
  //{
  //  auto& raw = std::get<0>(texture);
  //  auto extent_x = std::get<1>(texture);
  //  auto extent_y = std::get<2>(texture);

  //  auto src_extent_x = extent_x;
  //  auto src_extent_y = extent_y;
  //  auto src_data = reinterpret_cast<uint8_t*>(raw.AccessBytes().first);

  //  const auto mipmap_count_fn = [](uint32_t value)
  //  {
  //    uint32_t power = 0;
  //    while ((value >> power) > 0) ++power;
  //    return power;
  //  };

  //  const auto mipmap_x = mipmap_count_fn(extent_x);
  //  const auto mipmap_y = mipmap_count_fn(extent_y);
  //  extent_x = 1u << int32_t(mipmap_x) - 1;
  //  extent_y = 1u << int32_t(mipmap_y) - 1;
  //  mipmap = std::min(std::max(mipmap_x, mipmap_y), mipmap);
  //  
  //  auto raws = std::vector<Raw>(mipmap);
  //  for (auto i = 0; i < mipmap; ++i)
  //  {
  //    const auto x = std::max(1u, extent_x >> i);
  //    const auto y = std::max(1u, extent_y >> i);
  //    raws[i] = Raw(x * y * uint32_t(sizeof(glm::u8vec4)));
  //  }
  //  
  //  auto dst_extent_x = extent_x;
  //  auto dst_extent_y = extent_y;
  //  auto dst_data = reinterpret_cast<uint8_t*>(raws[0].AccessBytes().first);
  //  
  //  stbir_resize_uint8(src_data, src_extent_x, src_extent_y, 0, dst_data, dst_extent_x, dst_extent_y, 0, 4);

  //  for (auto i = 1; i < mipmap; ++i)
  //  {
  //    src_extent_x = dst_extent_x;
  //    src_extent_y = dst_extent_y;
  //    src_data = dst_data;

  //    dst_extent_x = std::max(1u, extent_x >> i);
  //    dst_extent_y = std::max(1u, extent_y >> i);
  //    dst_data = reinterpret_cast<uint8_t*>(raws[i].AccessBytes().first);

  //    stbir_resize_uint8(src_data, src_extent_x, src_extent_y, 0, dst_data, dst_extent_x, dst_extent_y, 0, 4);
  //  }

  //  return std::make_tuple(std::move(raws), extent_x, extent_y);
  //}

  //void SaveTextureLDR(const std::string& path, const std::tuple<Raw, uint32_t, uint32_t>& texture)
  //{}

  ////std::tuple<Raw, uint32_t, uint32_t> PopulateTextureLDR(uint32_t extent_x, uint32_t extent_y,
  ////  ColorFuncTextureLDR color_fn)
  ////{
  ////  auto raw = Raw(uint32_t(sizeof(glm::u8vec4)) * extent_x * extent_y);
  ////  for (auto i = 0u; i < uint32_t(extent_x * extent_y); ++i)
  ////  {
  ////    raw.SetItem<glm::u8vec4>(color_fn(i), i);
  ////  }

  ////  return { std::move(raw), uint32_t(extent_x), uint32_t(extent_y) };
  ////}

  //std::tuple<Raw, uint32_t, uint32_t> PopulateTextureLDR(uint32_t extent_x, uint32_t extent_y,
  //  std::function<glm::u8vec4(uint32_t)> color_fn)
  //{
  //  auto raw = Raw(sizeof(glm::u8vec4) * extent_x * extent_y);
  //  for (auto i = 0u; i < extent_x * extent_y; ++i)
  //  {
  //    raw.SetItem<glm::u8vec4>(color_fn(i), i);
  //  }

  //  return { std::move(raw), uint32_t(extent_x), uint32_t(extent_y) };
  //}

  //std::tuple<Raw, uint32_t, uint32_t> CombineTextureLDR(
  //  const std::tuple<Raw, uint32_t, uint32_t>& r_texture, uint32_t r_channel,
  //  const std::tuple<Raw, uint32_t, uint32_t>& g_texture, uint32_t g_channel,
  //  const std::tuple<Raw, uint32_t, uint32_t>& b_texture, uint32_t b_channel,
  //  const std::tuple<Raw, uint32_t, uint32_t>& a_texture, uint32_t a_channel)
  //{
  //  BLAST_ASSERT(std::get<1>(r_texture) == std::get<1>(g_texture) == std::get<1>(b_texture) == std::get<1>(a_texture));
  //  BLAST_ASSERT(std::get<2>(r_texture) == std::get<2>(g_texture) == std::get<2>(b_texture) == std::get<2>(a_texture));
  //  
  //  auto extent_x = std::get<1>(r_texture);
  //  auto extent_y = std::get<2>(r_texture);

  //  const auto [r_texels, r_count] = std::get<0>(r_texture).GetElements<glm::u8vec4>();
  //  const auto [g_texels, g_count] = std::get<0>(g_texture).GetElements<glm::u8vec4>();
  //  const auto [b_texels, b_count] = std::get<0>(b_texture).GetElements<glm::u8vec4>();
  //  const auto [a_texels, a_count] = std::get<0>(a_texture).GetElements<glm::u8vec4>();

  //  auto raw = Raw(sizeof(glm::u8vec4) * extent_x * extent_y);
  //  for (auto i = 0u; i < extent_x * extent_y; ++i)
  //  {
  //    const auto r = r_channel < 4 ? r_texels[i][r_channel] : 0u;
  //    const auto g = g_channel < 4 ? g_texels[i][g_channel] : 0u;
  //    const auto b = b_channel < 4 ? b_texels[i][b_channel] : 0u;
  //    const auto a = a_channel < 4 ? a_texels[i][a_channel] : 0u;
  //    raw.SetItem<glm::u8vec4>({ r, g, b, a }, i);
  //  }

  //  return { std::move(raw), extent_x, extent_y };
  //}

  //std::tuple<Raw, uint32_t, uint32_t> LoadTextureHDR(const std::string& path)
  //{
  //  auto extent_x = 0;
  //  auto extent_y = 0;
  //  auto channels = 4;
  //  float* texels = nullptr; // stbi_loadf(path.c_str(), &extent_x, &extent_y, &channels, STBI_default);

  //  LoadEXR(&texels, &extent_x, &extent_y, path.c_str(), nullptr);

  //  const auto stride = uint32_t(sizeof(glm::f32vec4));
  //  const auto count = uint32_t(extent_x * extent_y);
  //  auto raw = Raw(stride * count);

  //  for (auto i = 0u; i < uint32_t(extent_x * extent_y); ++i)
  //  {
  //    const auto r = channels > 0 ? texels[i * channels + 0] : 0; //0xFF;
  //    const auto g = channels > 1 ? texels[i * channels + 1] : r; //0xFF;
  //    const auto b = channels > 2 ? texels[i * channels + 2] : r; //0xFF;
  //    const auto a = channels > 3 ? texels[i * channels + 3] : r; //0xFF;
  //    raw.SetItem<glm::f32vec4>({ r, g, b, a }, i);
  //  }
  //  delete[] texels;

  //  return { std::move(raw), uint32_t(extent_x), uint32_t(extent_y) };
  //}

  //std::tuple<Raw, uint32_t, uint32_t> ResizeTextureHDR(uint32_t extent_x, uint32_t extent_y,
  //  const std::tuple<Raw, uint32_t, uint32_t>& texture)
  //{
  //  auto src_extent_x = std::get<1>(texture);
  //  auto src_extent_y = std::get<2>(texture);
  //  auto src_data = reinterpret_cast<float*>(std::get<0>(texture).AccessBytes().first);

  //  auto raw = Raw(sizeof(glm::f32vec4) * extent_x * extent_y);

  //  auto dst_extent_x = extent_x;
  //  auto dst_extent_y = extent_y;
  //  auto dst_data = reinterpret_cast<float*>(raw.AccessBytes().first);

  //  stbir_resize_float(src_data, src_extent_x, src_extent_y, 0, dst_data, dst_extent_x, dst_extent_y, 0, 4);

  //  return { std::move(raw), extent_x, extent_y };
  //}

  //std::tuple<std::vector<Raw>, uint32_t, uint32_t> MipmapTextureHDR(uint32_t mipmap,
  //  const std::tuple<Raw, uint32_t, uint32_t>& texture)
  //{
  //  auto& raw = std::get<0>(texture);
  //  auto extent_x = std::get<1>(texture);
  //  auto extent_y = std::get<2>(texture);

  //  auto src_extent_x = extent_x;
  //  auto src_extent_y = extent_y;
  //  auto src_data = reinterpret_cast<float*>(raw.AccessBytes().first);

  //  const auto mipmap_count_fn = [](uint32_t value)
  //    {
  //      uint32_t power = 0;
  //      while ((value >> power) > 0) ++power;
  //      return power;
  //    };

  //  const auto mipmap_x = mipmap_count_fn(extent_x);
  //  const auto mipmap_y = mipmap_count_fn(extent_y);
  //  extent_x = 1u << int32_t(mipmap_x) - 1;
  //  extent_y = 1u << int32_t(mipmap_y) - 1;
  //  mipmap = std::min(std::max(mipmap_x, mipmap_y), mipmap);

  //  auto raws = std::vector<Raw>(mipmap);
  //  for (auto i = 0; i < mipmap; ++i)
  //  {
  //    const auto x = std::max(1u, extent_x >> i);
  //    const auto y = std::max(1u, extent_y >> i);
  //    raws[i] = Raw(x * y * uint32_t(sizeof(glm::f32vec4)));
  //  }

  //  auto dst_extent_x = extent_x;
  //  auto dst_extent_y = extent_y;
  //  auto dst_data = reinterpret_cast<float*>(raws[0].AccessBytes().first);

  //  stbir_resize_float(src_data, src_extent_x, src_extent_y, 0, dst_data, dst_extent_x, dst_extent_y, 0, 4);

  //  for (auto i = 1; i < mipmap; ++i)
  //  {
  //    src_extent_x = dst_extent_x;
  //    src_extent_y = dst_extent_y;
  //    src_data = dst_data;

  //    dst_extent_x = std::max(1u, extent_x >> i);
  //    dst_extent_y = std::max(1u, extent_y >> i);
  //    dst_data = reinterpret_cast<float*>(raws[i].AccessBytes().first);

  //    stbir_resize_float(src_data, src_extent_x, src_extent_y, 0, dst_data, dst_extent_x, dst_extent_y, 0, 4);
  //  }

  //  return std::make_tuple(std::move(raws), extent_x, extent_y);
  //}

  //std::tuple<Raw, uint32_t, uint32_t> ResizeTextureHDR(const std::tuple<Raw, uint32_t, uint32_t>& texture, uint32_t mipmap, bool symmetric)
  //{
  //  const auto mipmap_count_fn = [](int32_t value)
  //  {
  //    int32_t power = 0;
  //    while ((value >> power) > 0) ++power;
  //    return power;
  //  };

  //  auto& texels = std::get<0>(texture);
  //  auto extent_x = std::get<1>(texture);
  //  auto extent_y = std::get<2>(texture);

  //  auto src_extent_x = extent_x;
  //  auto src_extent_y = extent_y;
  //  auto src_data = reinterpret_cast<float*>(texels.AccessBytes().first);

  //  auto mipmap_x = mipmap_count_fn(extent_x);
  //  auto mipmap_y = mipmap_count_fn(extent_y);
  //  extent_x = 1u << (symmetric ? int32_t(mipmap) - 1 : mipmap_x > mipmap_y ? int32_t(mipmap) - 1 : std::max(0, int32_t(mipmap) - 1 - (mipmap_y - mipmap_x)));
  //  extent_y = 1u << (symmetric ? int32_t(mipmap) - 1 : mipmap_y > mipmap_x ? int32_t(mipmap) - 1 : std::max(0, int32_t(mipmap) - 1 - (mipmap_x - mipmap_y)));

  //  const auto texel_count_fn = [](uint32_t extent_x, uint32_t extent_y)
  //  {
  //      auto count = 1u;
  //      while (extent_x > 1u || extent_y > 1u)
  //      {
  //        count += extent_x * extent_y;
  //        extent_x = std::max(1u, extent_x >> 1u);
  //        extent_y = std::max(1u, extent_y >> 1u);
  //      }

  //      return count;
  //  };

  //  const auto stride = uint32_t(sizeof(glm::f32vec4));
  //  const auto count = texel_count_fn(extent_x, extent_y);
  //  auto raw = Raw(stride * count);

  //  auto dst_extent_x = extent_x;
  //  auto dst_extent_y = extent_y;
  //  auto dst_data = reinterpret_cast<float*>(raw.AccessBytes().first);

  //  stbir_resize_float(src_data, src_extent_x, src_extent_y, 0, dst_data, dst_extent_x, dst_extent_y, 0, 4);

  //  for (auto i = 1; i < mipmap; ++i)
  //  {
  //    src_extent_x = dst_extent_x;
  //    src_extent_y = dst_extent_y;
  //    src_data = dst_data;

  //    dst_extent_x = std::max(1u, extent_x >> i);
  //    dst_extent_y = std::max(1u, extent_y >> i);
  //    dst_data = src_data + src_extent_x * src_extent_y * 4;

  //    stbir_resize_float(src_data, src_extent_x, src_extent_y, 0, dst_data, dst_extent_x, dst_extent_y, 0, 4);
  //  }

  //  return { std::move(raw), uint32_t(extent_x), uint32_t(extent_y) };
  //}

  //void SaveTextureHDR(const std::string& path, const std::tuple<Raw, uint32_t, uint32_t>& texture)
  //{
  //  const auto bytes = std::get<0>(texture).GetBytes();
  //  const auto extent_x = std::get<1>(texture);
  //  const auto extent_y = std::get<2>(texture);
  //  
  //  SaveEXR(reinterpret_cast<const float*>(bytes.first), extent_x, extent_y, 4, false, path.c_str(), nullptr);
  //}

  //std::tuple<Raw, uint32_t, uint32_t> CombineTextureHDR(
  //  const std::tuple<Raw, uint32_t, uint32_t>& r_texture, uint32_t r_channel,
  //  const std::tuple<Raw, uint32_t, uint32_t>& g_texture, uint32_t g_channel,
  //  const std::tuple<Raw, uint32_t, uint32_t>& b_texture, uint32_t b_channel,
  //  const std::tuple<Raw, uint32_t, uint32_t>& a_texture, uint32_t a_channel)
  //{
  //  BLAST_ASSERT(std::get<1>(r_texture) == std::get<1>(g_texture) == std::get<1>(b_texture) == std::get<1>(a_texture));
  //  BLAST_ASSERT(std::get<2>(r_texture) == std::get<2>(g_texture) == std::get<2>(b_texture) == std::get<2>(a_texture));

  //  auto extent_x = std::get<1>(r_texture);
  //  auto extent_y = std::get<2>(r_texture);

  //  const auto [r_texels, r_count] = std::get<0>(r_texture).GetElements<glm::f32vec4>();
  //  const auto [g_texels, g_count] = std::get<0>(g_texture).GetElements<glm::f32vec4>();
  //  const auto [b_texels, b_count] = std::get<0>(b_texture).GetElements<glm::f32vec4>();
  //  const auto [a_texels, a_count] = std::get<0>(a_texture).GetElements<glm::f32vec4>();

  //  auto raw = Raw(sizeof(glm::f32vec4) * extent_x * extent_y);
  //  for (auto i = 0u; i < extent_x * extent_y; ++i)
  //  {
  //    const auto r = r_channel < 4 ? r_texels[i][r_channel] : 0.0f;
  //    const auto g = g_channel < 4 ? g_texels[i][g_channel] : 0.0f;
  //    const auto b = b_channel < 4 ? b_texels[i][b_channel] : 0.0f;
  //    const auto a = a_channel < 4 ? a_texels[i][a_channel] : 0.0f;
  //    raw.SetItem<glm::f32vec4>({ r, g, b, a }, i);
  //  }

  //  return { std::move(raw), extent_x, extent_y };
  //}

  //Raw LoadBuffer(const std::string& path)
  //{}

  //void SaveBuffer(const std::string& path, const Raw& raw)
  //{}

  //void ExportBuffer(const std::string& path, const std::shared_ptr<Property>& root)
  //{}

  //std::shared_ptr<Property> ImportBuffer(const std::string& path, uint32_t stride)
  //{}
}