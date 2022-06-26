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

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>

#define TINYGLTF_IMPLEMENTATION
//#define TINYGLTF_NO_STB_IMAGE
//#define TINYGLTF_NO_STB_IMAGE_WRITE
#include <tinygltf/tiny_gltf.h>

#define TINYEXR_IMPLEMENTATION
#include <tinyexr/tinyexr.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>
#include <stb/stb_image_resize.h>


#include <mikktspace/mikktspace.h>

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

  std::shared_ptr<Property> ParseJSON(const nlohmann::json& node, const std::shared_ptr<Property>& parent_property)
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
        const auto child_property = ParseJSON(child_node, property);
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
        const auto child_property = ParseJSON(child_node, property);
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

  std::shared_ptr<Property> CreateBufferProperty(const void* data, uint32_t stride, uint32_t count)
  {
    const auto root_property = std::shared_ptr<Property>(new Property(Property::TYPE_RAW));
    root_property->RawAllocate(stride * count);
    root_property->SetRawBytes({ data, stride * count }, 0);

    return root_property;
  }


  std::shared_ptr<Property> CreateTextureProperty(const void* data, uint32_t stride, uint32_t size_x, uint32_t size_y, uint32_t mipmaps)
  {
    const auto root_property = std::shared_ptr<Property>(new Property(Property::TYPE_OBJECT));

    const auto stride_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    stride_property->SetUint(mipmaps);
    root_property->SetObjectItem("stride", stride_property);

    const auto size_x_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    size_x_property->SetUint(uint32_t(1 << (mipmaps - 1)));
    root_property->SetObjectItem("size_x", size_x_property);

    const auto size_y_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    size_y_property->SetUint(uint32_t(1 << (mipmaps - 1)));
    root_property->SetObjectItem("size_y", size_y_property);

    const auto mipmaps_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    mipmaps_property->SetUint(mipmaps);
    root_property->SetObjectItem("mipmaps", mipmaps_property);

    const auto data_property = std::shared_ptr<Property>(new Property(Property::TYPE_RAW));
    data_property->RawAllocate(stride * size_x * size_y);
    data_property->SetRawBytes({ data, stride * size_x * size_y }, 0);
    root_property->SetObjectItem("bytes", data_property);

    return root_property;
  }


  void ConvertSceneGLTF(const tinygltf::Model& gltf_model,
    std::vector<std::vector<Vertex>>& vertices_arrays, std::vector<std::vector<Triangle>>& triangles_arrays, std::vector<Instance>& instances_array, float position_scale,
    std::vector<Texture>& textures_0, std::vector<Texture>& textures_1, std::vector<Texture>& textures_2, std::vector<Texture>& textures_3)
  {
    vertices_arrays.clear();
    triangles_arrays.clear();
    instances_array.clear();

    const auto tex_reindex_fn = [](std::vector<uint32_t>& tex_ids, uint32_t tex_id)
    {
      if (tex_id == -1)
      {
        return uint32_t(-1);
      }

      const auto tex_iter = std::find_if(tex_ids.cbegin(), tex_ids.cend(), [&tex_id](const auto& index) { return tex_id == index; });
      const auto tex_index = tex_iter == tex_ids.cend() ? uint32_t(tex_ids.size()) : uint32_t(tex_iter - tex_ids.cbegin());
      if (tex_index == tex_ids.size())
      {
        tex_ids.push_back(tex_id);
      }
      return tex_index;
    };

    textures_0.clear(); // base + alpha
    textures_1.clear(); // emission + occlusion
    textures_2.clear(); // metallic + roughness
    textures_3.clear(); // normal or derivatives

    const auto access_buffer_fn = [&gltf_model](const tinygltf::Accessor& accessor)
    {
      const auto& gltf_view = gltf_model.bufferViews[accessor.bufferView];
      const auto length = gltf_view.byteLength;
      const auto offset = gltf_view.byteOffset;
      const auto stride = gltf_view.byteStride;

      auto& image = gltf_model.images[0];
      //image.pixel_type

      const auto& gltf_buffer = gltf_model.buffers[gltf_view.buffer];
      const auto data = &gltf_buffer.data[gltf_view.byteOffset];

      return std::pair{ data, uint32_t(stride) };
    };


    const auto create_vertex_fn = [&gltf_model](uint32_t index, float scale,
      std::pair<const uint8_t*, uint32_t> position_data,
      std::pair<const uint8_t*, uint32_t> normal_data,
      std::pair<const uint8_t*, uint32_t> texcoord_data)
    {
      Vertex vertex;

      const auto position = reinterpret_cast<const float*>(position_data.first + position_data.second * index);
      vertex.pos = glm::fvec3{ position[0], position[1], position[2] };
      vertex.pos = vertex.pos * scale;

      const auto normal = reinterpret_cast<const float*>(normal_data.first + normal_data.second * index);
      vertex.nrm = glm::fvec3{ normal[0], normal[1], normal[2] };
      vertex.nrm = glm::normalize(vertex.nrm);

      const auto texcoord = reinterpret_cast<const float*>(texcoord_data.first + texcoord_data.second * index);
      vertex.u = texcoord[0];
      vertex.v = texcoord[1];

      return vertex;
    };

    uint32_t vertices_offset = 0;
    uint32_t triangles_offset = 0;

    std::vector<uint32_t> texture_0_indices;
    std::vector<uint32_t> texture_1_indices;
    std::vector<uint32_t> texture_2_indices;
    std::vector<uint32_t> texture_3_indices;

    const auto gltf_scene = gltf_model.scenes[0];


    for (uint32_t i = 0; i < uint32_t(gltf_scene.nodes.size()); ++i)
    {
      const auto& gltf_node = gltf_model.nodes[gltf_scene.nodes[i]];

      const auto& gltf_mesh = gltf_model.meshes[gltf_node.mesh];

      uint32_t offset = 0;
      for (uint32_t j = 0; j < uint32_t(gltf_mesh.primitives.size()); ++j)
      {
        std::vector<Vertex> vertices;
        std::vector<Triangle> triangles;

        const auto& gltf_primitive = gltf_mesh.primitives[j];
        BLAST_ASSERT(gltf_primitive.mode == TINYGLTF_MODE_TRIANGLES);

        const auto& gltf_material = gltf_model.materials[gltf_primitive.material];

        const auto& gltf_positions = gltf_model.accessors[gltf_primitive.attributes.at("POSITION")];
        BLAST_ASSERT(gltf_positions.type == TINYGLTF_TYPE_VEC3 && gltf_positions.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
        const auto position_data = access_buffer_fn(gltf_positions);

        const auto& gltf_normals = gltf_model.accessors[gltf_primitive.attributes.at("NORMAL")];
        BLAST_ASSERT(gltf_normals.type == TINYGLTF_TYPE_VEC3 && gltf_normals.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
        const auto normal_data = access_buffer_fn(gltf_normals);

        const auto& gltf_texcoords = gltf_model.accessors[gltf_primitive.attributes.at("TEXCOORD_0")];
        BLAST_ASSERT(gltf_texcoords.type == TINYGLTF_TYPE_VEC2 && gltf_texcoords.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
        const auto texcoord_data = access_buffer_fn(gltf_texcoords);

        


        auto degenerated_geom_prim_count = 0;
        auto degenerated_wrap_prim_count = 0;

        const auto& hash_vertex_fn = [](const Vertex& vertex)
        {
          const auto uref = reinterpret_cast<const uint32_t*>(&vertex);
          const auto hash0 = std::hash<glm::u32vec4>()(glm::f32vec4{ uref[0], uref[1], uref[2], uref[3] });
          const auto hash1 = std::hash<glm::u32vec4>()(glm::f32vec4{ uref[4], uref[5], uref[6], uref[7] });
          const auto hash2 = std::hash<glm::u32vec4>()(glm::f32vec4{ uref[8], uref[9], uref[10], uref[11] });
          return ((hash0 ^ (hash1 << 1)) >> 1) ^ (hash2 << 1);
          //return (hash0 ^ (hash1 << 1));
        };
        auto compare_vertex_fn = [](const Vertex& l, const Vertex& r)
        {
          return (memcmp(&l, &r, sizeof(Vertex)) == 0);
        };
        std::unordered_map<Vertex, uint32_t, decltype(hash_vertex_fn), decltype(compare_vertex_fn)> vertex_map(8, hash_vertex_fn, compare_vertex_fn);

        const auto& remap_vertex_fn = [&vertex_map](std::vector<Vertex>& vertices, const Vertex& vertex)
        {
          const auto result = vertex_map.emplace(vertex, uint32_t(vertices.size()));
          if (result.second)
          {
            vertices.push_back({ vertex.pos, vertex.u, vertex.nrm, vertex.v });
          }
          return result.first->second;
        };

        const auto& gltf_indices = gltf_model.accessors[gltf_primitive.indices];
        BLAST_ASSERT(gltf_indices.type == TINYGLTF_TYPE_SCALAR);

        const auto& indices_view = gltf_model.bufferViews[gltf_indices.bufferView];
        const auto indices_length = indices_view.byteLength;
        const auto indices_offset = indices_view.byteOffset;
        const auto indices_stride = indices_view.byteStride;

        const auto& indices_buffer = gltf_model.buffers[indices_view.buffer];
        

        if (gltf_indices.componentType == TINYGLTF_COMPONENT_TYPE_INT || gltf_indices.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
        {
          const auto indices_data = reinterpret_cast<const uint32_t*>(&indices_buffer.data[gltf_indices.byteOffset]);

          for (uint32_t k = 0; k < gltf_indices.count / 3; ++k)
          {
            const auto vtx0 = create_vertex_fn(indices_data[k * 3 + 0], position_scale, position_data, normal_data, texcoord_data);
            const auto vtx1 = create_vertex_fn(indices_data[k * 3 + 1], position_scale, position_data, normal_data, texcoord_data);
            const auto vtx2 = create_vertex_fn(indices_data[k * 3 + 2], position_scale, position_data, normal_data, texcoord_data);

            const auto dp_10 = vtx1.pos - vtx0.pos;
            const auto dp_20 = vtx2.pos - vtx0.pos;
            const auto ng = glm::cross(dp_10, dp_20);
            if (glm::length(ng) == 0.0f)
            {
              ++degenerated_geom_prim_count;
              continue;
            }

            auto has_textures = false;
            //has_textures = obj_materials[obj_mesh.material_ids[j]].diffuse_texname.empty() ? has_textures : true;
            //has_textures = obj_materials[obj_mesh.material_ids[j]].alpha_texname.empty() ? has_textures : true;
            //has_textures = obj_materials[obj_mesh.material_ids[j]].specular_texname.empty() ? has_textures : true;
            //has_textures = obj_materials[obj_mesh.material_ids[j]].bump_texname.empty() ? has_textures : true;

            if (has_textures)
            {
              const auto duv_10 = glm::fvec2(vtx1.u, vtx1.v) - glm::fvec2(vtx0.u, vtx0.v);
              const auto duv_20 = glm::fvec2(vtx2.u, vtx2.v) - glm::fvec2(vtx0.u, vtx0.v);
              const auto det = glm::determinant(glm::fmat2x2(duv_10, duv_20));
              if (det == 0.0f)
              {
                ++degenerated_wrap_prim_count;
                continue;
              }
            }

            const auto idx0 = remap_vertex_fn(vertices, vtx0);
            const auto idx1 = remap_vertex_fn(vertices, vtx1);
            const auto idx2 = remap_vertex_fn(vertices, vtx2);

            triangles.push_back({ glm::uvec3(idx0, idx1, idx2) });
          }
        }
        else if (gltf_indices.componentType == TINYGLTF_COMPONENT_TYPE_SHORT || gltf_indices.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
        {
          const auto indices_data = reinterpret_cast<const uint16_t*>(&indices_buffer.data[gltf_indices.byteOffset]);
          
          for (uint32_t k = 0; k < gltf_indices.count / 3; ++k)
          {
            const auto vtx0 = create_vertex_fn(indices_data[k * 3 + 0], position_scale, position_data, normal_data, texcoord_data);
            const auto vtx1 = create_vertex_fn(indices_data[k * 3 + 1], position_scale, position_data, normal_data, texcoord_data);
            const auto vtx2 = create_vertex_fn(indices_data[k * 3 + 2], position_scale, position_data, normal_data, texcoord_data);

            const auto dp_10 = vtx1.pos - vtx0.pos;
            const auto dp_20 = vtx2.pos - vtx0.pos;
            const auto ng = glm::cross(dp_10, dp_20);
            if (glm::length(ng) == 0.0f)
            {
              ++degenerated_geom_prim_count;
              continue;
            }


            auto has_textures = false;
            //has_textures = obj_materials[obj_mesh.material_ids[j]].diffuse_texname.empty() ? has_textures : true;
            //has_textures = obj_materials[obj_mesh.material_ids[j]].alpha_texname.empty() ? has_textures : true;
            //has_textures = obj_materials[obj_mesh.material_ids[j]].specular_texname.empty() ? has_textures : true;
            //has_textures = obj_materials[obj_mesh.material_ids[j]].bump_texname.empty() ? has_textures : true;

            if (has_textures)
            {
              const auto duv_10 = glm::fvec2(vtx1.u, vtx1.v) - glm::fvec2(vtx0.u, vtx0.v);
              const auto duv_20 = glm::fvec2(vtx2.u, vtx2.v) - glm::fvec2(vtx0.u, vtx0.v);
              const auto det = glm::determinant(glm::fmat2x2(duv_10, duv_20));
              if (det == 0.0f)
              {
                ++degenerated_wrap_prim_count;
                continue;
              }
            }

            const auto idx0 = remap_vertex_fn(vertices, vtx0);
            const auto idx1 = remap_vertex_fn(vertices, vtx1);
            const auto idx2 = remap_vertex_fn(vertices, vtx2);

            triangles.push_back({ glm::uvec3(idx0, idx1, idx2) });
          }
        }
        else if (gltf_indices.componentType == TINYGLTF_COMPONENT_TYPE_BYTE || gltf_indices.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE)
        {
          const auto indices_data = reinterpret_cast<const uint8_t*>(&indices_buffer.data[gltf_indices.byteOffset]);

          for (uint32_t k = 0; k < gltf_indices.count / 3; ++k)
          {
            const auto vtx0 = create_vertex_fn(indices_data[k * 3 + 0], position_scale, position_data, normal_data, texcoord_data);
            const auto vtx1 = create_vertex_fn(indices_data[k * 3 + 1], position_scale, position_data, normal_data, texcoord_data);
            const auto vtx2 = create_vertex_fn(indices_data[k * 3 + 2], position_scale, position_data, normal_data, texcoord_data);

            const auto idx0 = remap_vertex_fn(vertices, vtx0);
            const auto idx1 = remap_vertex_fn(vertices, vtx1);
            const auto idx2 = remap_vertex_fn(vertices, vtx2);

            triangles.push_back({ glm::uvec3(idx0, idx1, idx2) });

          }
        }

        BLAST_LOG("Instance %d: Degenerated geom/wrap prims: %d/%d", j, degenerated_geom_prim_count, degenerated_wrap_prim_count);


        {
          struct SMikkTSpaceUserData
          {
            std::vector<Triangle>& triangles;
            std::vector<Vertex>& vertices;
          };
          SMikkTSpaceUserData data{ triangles, vertices };


          SMikkTSpaceInterface input = { 0 };
          input.m_getNumFaces = [](const SMikkTSpaceContext* ctx)
          {
            const auto data = reinterpret_cast<const SMikkTSpaceUserData*>(ctx->m_pUserData);
            return int32_t(data->triangles.size());
          };

          input.m_getNumVerticesOfFace = [](const SMikkTSpaceContext* ctx, const int iFace)
          {
            const auto data = reinterpret_cast<const SMikkTSpaceUserData*>(ctx->m_pUserData);
            return 3;
          };

          //input.m_getPosition = &GetPositionCb;
          //input.m_getNormal = &GetNormalCb;
          //input.m_getTexCoord = &GetTexCoordCb;
          //input.m_setTSpaceBasic = &SetTspaceBasicCb;
          //input.m_setTSpace = NULL;


          input.m_getPosition = [](const SMikkTSpaceContext* ctx, float fvPosOut[], int iFace, int iVert)
          {
            const auto data = reinterpret_cast<const SMikkTSpaceUserData*>(ctx->m_pUserData);
            const auto& pos = data->vertices[data->triangles[iFace].idx[iVert]].pos;
            fvPosOut[0] = pos.x;
            fvPosOut[1] = pos.y;
            fvPosOut[2] = pos.z;
          };

          input.m_getNormal = [](const SMikkTSpaceContext* ctx, float fvNormOut[], int iFace, int iVert)
          {
            const auto data = reinterpret_cast<const SMikkTSpaceUserData*>(ctx->m_pUserData);
            const auto& nrm = data->vertices[data->triangles[iFace].idx[iVert]].nrm;
            fvNormOut[0] = nrm.x;
            fvNormOut[1] = nrm.y;
            fvNormOut[2] = nrm.z;
          };

          input.m_getTexCoord = [](const SMikkTSpaceContext* ctx, float fvTexcOut[], int iFace, int iVert)
          {
            const auto data = reinterpret_cast<const SMikkTSpaceUserData*>(ctx->m_pUserData);
            const auto& u = data->vertices[data->triangles[iFace].idx[iVert]].u;
            const auto& v = data->vertices[data->triangles[iFace].idx[iVert]].v;
            fvTexcOut[0] = u;
            fvTexcOut[1] = v;
          };

          input.m_setTSpaceBasic = [](const SMikkTSpaceContext* ctx, const float fvTangent[], float fSign, int iFace, int iVert)
          {
            auto data = reinterpret_cast<SMikkTSpaceUserData*>(ctx->m_pUserData);
            auto& tgs = data->vertices[data->triangles[iFace].idx[iVert]].tgn;
            tgs.x = fvTangent[0];
            tgs.y = fvTangent[1];
            tgs.z = fvTangent[2];
            auto& sign = data->vertices[data->triangles[iFace].idx[iVert]].sign;
            sign = fSign;
          };

          SMikkTSpaceContext context;
          context.m_pInterface = &input;
          context.m_pUserData = &data;

          genTangSpaceDefault(&context);
        }


        BLAST_LOG("Instance %d: Added vert/prim: %d/%d", j, vertices.size(), triangles.size());

        Instance instance;
        instance.transform;

        const auto debug = false;
        if(debug)
        {
          instance.emission = glm::vec3(0.0f, 0.0f, 0.0f);
          instance.intensity = 0.0f;
          //material.ambient = glm::vec3(obj_material.ambient[0], obj_material.ambient[1], obj_material.ambient[2]);
          //material.dissolve = obj_material.dissolve;
          instance.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
          instance.metallic = 1.0f;
          instance.specular = glm::vec3(0.0f, 0.0f, 0.0f);
          instance.shininess = 1.0f;
          instance.transmittance = glm::vec3(0.0f, 0.0f, 0.0f); // *(1.0f - obj_material.dissolve);
          instance.ior = 1.0f;
        }
        else
        {
          instance.emission = glm::vec3(0.0f, 0.0f, 0.0f);
          instance.intensity = 0.0f;
          //material.ambient = glm::vec3(obj_material.ambient[0], obj_material.ambient[1], obj_material.ambient[2]);
          //material.dissolve = obj_material.dissolve;
          instance.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
          instance.metallic = 1.0f;
          instance.specular = glm::vec3(0.0f, 0.0f, 0.0f);
          instance.shininess = 1.0f;
          instance.transmittance = glm::vec3(0.0f, 0.0f, 0.0f); // *(1.0f - obj_material.dissolve);
          instance.ior = 1.0f;

          const auto texture_0_id = gltf_material.pbrMetallicRoughness.baseColorTexture.index;
          instance.texture0_idx = texture_0_id == -1 ? uint32_t(-1) : tex_reindex_fn(texture_0_indices, texture_0_id);
          const auto texture_1_id = gltf_material.occlusionTexture.index;
          instance.texture1_idx = texture_1_id == -1 ? uint32_t(-1) : tex_reindex_fn(texture_1_indices, texture_1_id);
          const auto texture_2_id = gltf_material.pbrMetallicRoughness.metallicRoughnessTexture.index;
          instance.texture2_idx = texture_2_id == -1 ? uint32_t(-1) : tex_reindex_fn(texture_2_indices, texture_2_id);
          const auto texture_3_id = gltf_material.normalTexture.index;
          instance.texture3_idx = texture_3_id == -1 ? uint32_t(-1) : tex_reindex_fn(texture_3_indices, texture_3_id);
        }

        instance.geometry_idx = uint32_t(instances_array.size());
        //instance.debug_color{ 0.0f, 0.0f, 0.0f };

        instance.vert_count = uint32_t(vertices.size());
        instance.vert_offset = uint32_t(vertices_offset);
        instance.prim_count = uint32_t(triangles.size());
        instance.prim_offset = uint32_t(triangles_offset);

        vertices_arrays.push_back(vertices);
        triangles_arrays.push_back(triangles);
        instances_array.push_back(instance);

        vertices_offset += uint32_t(vertices.size());
        triangles_offset += uint32_t(triangles.size());
      }
    }

    const auto tex_prepare_fn = [&gltf_model](uint32_t texture_index)
    {
      const auto image_index = gltf_model.textures[texture_index].source;

      const auto tex_x = gltf_model.images[image_index].width;
      const auto tex_y = gltf_model.images[image_index].height;
      const auto tex_n = gltf_model.images[image_index].component;
      const auto tex_data = gltf_model.images[image_index].image.data();

      Texture texture;
      texture.texels.resize(tex_x * tex_y);

      for (uint32_t i = 0; i < tex_x * tex_y; ++i)
      {
        const uint8_t r = tex_n > 0 ? tex_data[i * tex_n + 0] : 0; //0xFF;
        const uint8_t g = tex_n > 1 ? tex_data[i * tex_n + 1] : r; //0xFF;
        const uint8_t b = tex_n > 2 ? tex_data[i * tex_n + 2] : r; //0xFF;
        const uint8_t a = tex_n > 3 ? tex_data[i * tex_n + 3] : r; //0xFF;
        texture.texels[i] = glm::u8vec4(r, g, b, a);

      }
      texture.extent_x = tex_x;
      texture.extent_y = tex_y;

      return texture;
    };

    textures_0.resize(texture_0_indices.size());
    for (uint32_t i = 0; i < uint32_t(texture_0_indices.size()); ++i)
    {
      const auto texture_0_index = texture_0_indices[i];
      textures_0[i] = std::move(tex_prepare_fn(texture_0_index));
    }

    textures_1.resize(texture_1_indices.size());
    for (uint32_t i = 0; i < uint32_t(texture_1_indices.size()); ++i)
    {
      const auto texture_1_index = texture_1_indices[i];
      textures_1[i] = std::move(tex_prepare_fn(texture_1_index));
    }

    textures_2.resize(texture_2_indices.size());
    for (uint32_t i = 0; i < uint32_t(texture_2_indices.size()); ++i)
    {
      const auto texture_2_index = texture_2_indices[i];
      textures_2[i] = std::move(tex_prepare_fn(texture_2_index));
    }

    textures_3.resize(texture_3_indices.size());
    for (uint32_t i = 0; i < uint32_t(texture_3_indices.size()); ++i)
    {
      const auto texture_3_index = texture_3_indices[i];
      textures_3[i] = std::move(tex_prepare_fn(texture_3_index));
    }

  }




  void ConvertSceneOBJ(const tinyobj::attrib_t& obj_attrib, const std::vector<tinyobj::shape_t>& obj_shapes, const std::vector<tinyobj::material_t>& obj_materials,
    std::vector<std::vector<Vertex>>& vertices_arrays, std::vector<std::vector<Triangle>>& triangles_arrays, std::vector<Instance>& instances_array, float position_scale,
    const std::string& path, std::vector<Texture>& textures_0, std::vector<Texture>& textures_1, std::vector<Texture>& textures_2, std::vector<Texture>& textures_3)
  {

    const auto& obj_vertices = obj_attrib.vertices;
    const auto& obj_normals = obj_attrib.normals;
    const auto& obj_texcoords = obj_attrib.texcoords;

    const auto create_vertex_fn = [&obj_vertices, &obj_normals, &obj_texcoords](const tinyobj::index_t& obj_index, float position_scale)
    {
      Vertex vertex;

      const auto& obj_vertex_index = obj_index.vertex_index;
      vertex.pos = obj_vertex_index == -1 ? glm::fvec3{ 0.0f, 0.0f, 0.0f }
      : glm::fvec3{ obj_vertices[3 * obj_vertex_index + 0], obj_vertices[3 * obj_vertex_index + 1],-obj_vertices[3 * obj_vertex_index + 2] }  *position_scale;
      const auto& obj_normal_index = obj_index.normal_index;
      vertex.nrm = obj_normal_index == -1 ? glm::fvec3{ 0.0f, 0.0f, 0.0f }
      : glm::fvec3{ obj_normals[3 * obj_normal_index + 0], obj_normals[3 * obj_normal_index + 1], -obj_normals[3 * obj_normal_index + 2] };
      const auto& obj_texcoord_index = obj_index.texcoord_index;
      vertex.u = obj_texcoord_index == -1 ? 0.0f : obj_texcoords[2 * obj_texcoord_index + 0];
      vertex.v = obj_texcoord_index == -1 ? 0.0f : -obj_texcoords[2 * obj_texcoord_index + 1];

      vertex.tgn = glm::fvec3{ 0.0f, 0.0f, 0.0f };
      vertex.sign = 0.0f;

      return vertex;
    };

    vertices_arrays.clear();
    triangles_arrays.clear();
    instances_array.clear();


    const auto tex_reindex_fn = [](std::vector<std::string>& tex_names, const std::string& tex_name)
    {
      if (tex_name.empty())
      {
        return -1;
      }

      const auto tex_iter = std::find_if(tex_names.cbegin(), tex_names.cend(), [&tex_name](const auto& name) { return tex_name == name; });
      const auto tex_index = tex_iter == tex_names.cend() ? int32_t(tex_names.size()) : int32_t(tex_iter - tex_names.cbegin());
      if (tex_index == tex_names.size())
      {
        tex_names.push_back(tex_name);
      }
      return tex_index;
    };

    std::vector<std::string> textures_0_names;
    std::vector<std::string> textures_1_names;
    std::vector<std::string> textures_2_names;
    std::vector<std::string> textures_3_names;

    textures_0.clear();  // diffuse
    textures_1.clear();  // normal
    textures_2.clear();  // alpha
    textures_3.clear();  // specular


    uint32_t vertices_offset = 0;
    uint32_t triangles_offset = 0;

    for (uint32_t i = 0; i < uint32_t(obj_shapes.size()); ++i)
    {
      const auto& obj_mesh = obj_shapes[i].mesh;

      std::unordered_map<int, int> material_indices;
      for (uint32_t j = 0; j < uint32_t(obj_mesh.material_ids.size()); ++j)
      {
        const auto index = obj_mesh.material_ids[j];
        material_indices[index] = material_indices.find(index) == material_indices.end() ? 1 : material_indices[index] + 1;
      }

      for (const auto& material_index : material_indices)
      {
        std::vector<Vertex> vertices;
        std::vector<Triangle> triangles;

        //std::vector<uint32_t> material_refs;

        auto hash_vertex_fn = [](const Vertex& vertex)
        {
          const auto uref = reinterpret_cast<const uint32_t*>(&vertex);
          const auto hash0 = std::hash<glm::u32vec4>()(glm::f32vec4{ uref[0], uref[1], uref[2], uref[3] });
          const auto hash1 = std::hash<glm::u32vec4>()(glm::f32vec4{ uref[4], uref[5], uref[6], uref[7] });
          const auto hash2 = std::hash<glm::u32vec4>()(glm::f32vec4{ uref[8], uref[9], uref[10], uref[11] });
          return ((hash0 ^ (hash1 << 1)) >> 1) ^ (hash2 << 1);
          //return (hash0 ^ (hash1 << 1));
        };
        auto compare_vertex_fn = [](const Vertex& l, const Vertex& r)
        {
          return (memcmp(&l, &r, sizeof(Vertex)) == 0);
        };
        std::unordered_map<Vertex, uint32_t, decltype(hash_vertex_fn), decltype(compare_vertex_fn)> vertex_map(8, hash_vertex_fn, compare_vertex_fn);

        auto remap_vertex_fn = [&vertex_map, &vertices](const Vertex& vertex)
        {
          const auto result = vertex_map.emplace(vertex, uint32_t(vertices.size()));
          if (result.second)
          {
            vertices.push_back({ vertex.pos, vertex.u, vertex.nrm, vertex.v });
          }
          return result.first->second;
        };


        auto degenerated_geom_prim_count = 0;
        auto degenerated_wrap_prim_count = 0;

        for (uint32_t j = 0; j < uint32_t(obj_mesh.material_ids.size()); ++j)
        {
          if (obj_mesh.material_ids[j] != material_index.first)
          {
            continue;
          }

          const auto vtx0 = create_vertex_fn(obj_mesh.indices[3 * j + 0], position_scale);
          const auto vtx1 = create_vertex_fn(obj_mesh.indices[3 * j + 2], position_scale);
          const auto vtx2 = create_vertex_fn(obj_mesh.indices[3 * j + 1], position_scale);

          const auto dp_10 = vtx1.pos - vtx0.pos;
          const auto dp_20 = vtx2.pos - vtx0.pos;
          const auto ng = glm::cross(dp_10, dp_20);
          if (glm::length(ng) == 0.0f)
          {
            ++degenerated_geom_prim_count;
            continue;
          }

          auto has_textures = false;
          has_textures = obj_materials[obj_mesh.material_ids[j]].diffuse_texname.empty() ? has_textures : true;
          has_textures = obj_materials[obj_mesh.material_ids[j]].alpha_texname.empty() ? has_textures : true;
          has_textures = obj_materials[obj_mesh.material_ids[j]].specular_texname.empty() ? has_textures : true;
          has_textures = obj_materials[obj_mesh.material_ids[j]].bump_texname.empty() ? has_textures : true;

          if (has_textures)
          {
            const auto duv_10 = glm::fvec2(vtx1.u, vtx1.v) - glm::fvec2(vtx0.u, vtx0.v);
            const auto duv_20 = glm::fvec2(vtx2.u, vtx2.v) - glm::fvec2(vtx0.u, vtx0.v);
            const auto det = glm::determinant(glm::fmat2x2(duv_10, duv_20));
            if (det == 0.0f)
            {
              ++degenerated_wrap_prim_count;
              continue;
            }
          }

          const auto idx0 = remap_vertex_fn(vtx0);
          const auto idx1 = remap_vertex_fn(vtx1);
          const auto idx2 = remap_vertex_fn(vtx2);

          triangles.push_back({ glm::uvec3(idx0, idx1, idx2) });
        }

        if (vertices.empty() || triangles.empty()) continue;


        {
          struct SMikkTSpaceUserData
          {
            std::vector<Triangle>& triangles;
            std::vector<Vertex>& vertices;
          };
          SMikkTSpaceUserData data{ triangles, vertices };


          SMikkTSpaceInterface input = { 0 };
          input.m_getNumFaces = [](const SMikkTSpaceContext* ctx)
          {
            const auto data = reinterpret_cast<const SMikkTSpaceUserData*>(ctx->m_pUserData);
            return int32_t(data->triangles.size());
          };

          input.m_getNumVerticesOfFace = [](const SMikkTSpaceContext* ctx, const int iFace)
          {
            const auto data = reinterpret_cast<const SMikkTSpaceUserData*>(ctx->m_pUserData);
            return 3;
          };

          //input.m_getPosition = &GetPositionCb;
          //input.m_getNormal = &GetNormalCb;
          //input.m_getTexCoord = &GetTexCoordCb;
          //input.m_setTSpaceBasic = &SetTspaceBasicCb;
          //input.m_setTSpace = NULL;


          input.m_getPosition = [](const SMikkTSpaceContext* ctx, float fvPosOut[], int iFace, int iVert)
          {
            const auto data = reinterpret_cast<const SMikkTSpaceUserData*>(ctx->m_pUserData);
            const auto& pos = data->vertices[data->triangles[iFace].idx[iVert]].pos;
            fvPosOut[0] = pos.x;
            fvPosOut[1] = pos.y;
            fvPosOut[2] = pos.z;
          };

          input.m_getNormal = [](const SMikkTSpaceContext* ctx, float fvNormOut[], int iFace, int iVert)
          {
            const auto data = reinterpret_cast<const SMikkTSpaceUserData*>(ctx->m_pUserData);
            const auto& nrm = data->vertices[data->triangles[iFace].idx[iVert]].nrm;
            fvNormOut[0] = nrm.x;
            fvNormOut[1] = nrm.y;
            fvNormOut[2] = nrm.z;
          };

          input.m_getTexCoord = [](const SMikkTSpaceContext* ctx, float fvTexcOut[], int iFace, int iVert)
          {
            const auto data = reinterpret_cast<const SMikkTSpaceUserData*>(ctx->m_pUserData);
            const auto& u = data->vertices[data->triangles[iFace].idx[iVert]].u;
            const auto& v = data->vertices[data->triangles[iFace].idx[iVert]].v;
            fvTexcOut[0] = u;
            fvTexcOut[1] = v;
          };

          input.m_setTSpaceBasic = [](const SMikkTSpaceContext* ctx, const float fvTangent[], float fSign, int iFace, int iVert)
          {
            auto data = reinterpret_cast<SMikkTSpaceUserData*>(ctx->m_pUserData);
            auto& tgs = data->vertices[data->triangles[iFace].idx[iVert]].tgn;
            tgs.x = fvTangent[0];
            tgs.y = fvTangent[1];
            tgs.z = fvTangent[2];
            auto& sign = data->vertices[data->triangles[iFace].idx[iVert]].sign;
            sign = fSign;
          };

          SMikkTSpaceContext context;
          context.m_pInterface = &input;
          context.m_pUserData = &data;

          genTangSpaceDefault(&context);
        }


        BLAST_LOG("Instance %d [%s]: Added vert/prim: %d/%d", i, obj_shapes[i].name.c_str(), vertices.size(), triangles.size());

        Instance instance;
        instance.transform;


        const auto& obj_material = obj_materials[material_index.first];

        const auto debug = false;
        if (debug)
        {
          instance.emission = glm::vec3(0.0f, 0.0f, 0.0f);
          instance.intensity = 0.0f;
          //material.ambient = glm::vec3(obj_material.ambient[0], obj_material.ambient[1], obj_material.ambient[2]);
          //material.dissolve = obj_material.dissolve;
          instance.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
          instance.metallic = 1.0f;
          instance.specular = glm::vec3(0.0f, 0.0f, 0.0f);
          instance.shininess = 1.0f;
          instance.transmittance = glm::vec3(0.0f, 0.0f, 0.0f) * (1.0f - obj_material.dissolve);
          instance.ior = 1.0f;
        }
        else
        {

          instance.emission = glm::vec3(obj_material.emission[0], obj_material.emission[1], obj_material.emission[2]);
          instance.intensity = 10.0f;
          //material.ambient = glm::vec3(obj_material.ambient[0], obj_material.ambient[1], obj_material.ambient[2]);
          //material.dissolve = obj_material.dissolve;
          instance.diffuse = glm::vec3(obj_material.diffuse[0], obj_material.diffuse[1], obj_material.diffuse[2]);
          instance.metallic = obj_material.metallic;
          instance.specular = glm::vec3(obj_material.specular[0], obj_material.specular[1], obj_material.specular[2]);
          instance.shininess = obj_material.shininess;
          instance.transmittance = glm::vec3(obj_material.transmittance[0], obj_material.transmittance[1], obj_material.transmittance[2]) * (1.0f - obj_material.dissolve);
          instance.ior = obj_material.ior;

          const auto& texture_0_name = obj_material.diffuse_texname;
          instance.texture0_idx = texture_0_name.empty() ? uint32_t(-1) : tex_reindex_fn(textures_0_names, texture_0_name);
          const auto& texture_1_name = obj_material.alpha_texname;
          instance.texture1_idx = texture_1_name.empty() ? uint32_t(-1) : tex_reindex_fn(textures_1_names, texture_1_name);
          const auto& texture_2_name = obj_material.specular_texname;
          instance.texture2_idx = texture_2_name.empty() ? uint32_t(-1) : tex_reindex_fn(textures_2_names, texture_2_name);
          const auto& texture_3_name = obj_material.bump_texname;
          instance.texture3_idx = texture_3_name.empty() ? uint32_t(-1) : tex_reindex_fn(textures_3_names, texture_3_name);



          switch (obj_material.illum)
          {
          case 3: // mirror
            instance.diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
            instance.specular = glm::vec3(1.0f, 1.0f, 1.0f);
            instance.transmittance = glm::vec3(0.0f, 0.0f, 0.0f);
            instance.shininess = float(1 << 16);
            break;
          case 7: // glass
            instance.diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
            instance.specular = glm::vec3(0.0f, 0.0f, 0.0f);
            instance.transmittance = glm::vec3(1.0f, 1.0f, 1.0f);
            instance.ior = 1.5f;
            break;
          }
        }

        instance.geometry_idx = uint32_t(instances_array.size());
        //instance.debug_color{ 0.0f, 0.0f, 0.0f };

        instance.vert_count = uint32_t(vertices.size());
        instance.vert_offset = uint32_t(vertices_offset);
        instance.prim_count = uint32_t(triangles.size());
        instance.prim_offset = uint32_t(triangles_offset);


        vertices_arrays.push_back(vertices);
        triangles_arrays.push_back(triangles);
        instances_array.push_back(instance);

        vertices_offset += uint32_t(vertices.size());
        triangles_offset += uint32_t(triangles.size());

      }
    }

    const auto load_texture_fn = [&path](const std::string& name)
    {
      int32_t tex_x = 0;
      int32_t tex_y = 0;
      int32_t tex_n = 0;
      unsigned char* tex_data = stbi_load((path + name).c_str(), &tex_x, &tex_y, &tex_n, STBI_default);

      Texture texture;
      texture.texels.resize(tex_x * tex_y);

      for (uint32_t i = 0; i < tex_x * tex_y; ++i)
      {
        const uint8_t r = tex_n > 0 ? tex_data[i * tex_n + 0] : 0; //0xFF;
        const uint8_t g = tex_n > 1 ? tex_data[i * tex_n + 1] : r; //0xFF;
        const uint8_t b = tex_n > 2 ? tex_data[i * tex_n + 2] : r; //0xFF;
        const uint8_t a = tex_n > 3 ? tex_data[i * tex_n + 3] : r; //0xFF;
        texture.texels[i] = glm::u8vec4(r, g, b, a);

      }
      stbi_image_free(tex_data);

      texture.extent_x = tex_x;
      texture.extent_y = tex_y;

      return texture;
    };

    if (!textures_0_names.empty())
    {
      textures_0.resize(textures_0_names.size());
      for (uint32_t i = 0; i < uint32_t(textures_0_names.size()); ++i)
      {
        textures_0[i] = std::move(load_texture_fn(textures_0_names[i]));
      }

  //    instance.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    if (!textures_1_names.empty())
    {
      textures_1.resize(textures_1_names.size());
      for (uint32_t i = 0; i < uint32_t(textures_1_names.size()); ++i)
      {
        textures_1[i] = std::move(load_texture_fn(textures_1_names[i]));
      }
    }

    if (!textures_2_names.empty())
    {
      textures_2.resize(textures_2_names.size());
      for (uint32_t i = 0; i < uint32_t(textures_2_names.size()); ++i)
      {
        textures_2[i] = std::move(load_texture_fn(textures_2_names[i]));
      }

      // instance.specular = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    if (!textures_3_names.empty())
    {
      textures_3.resize(textures_3_names.size());
      for (uint32_t i = 0; i < uint32_t(textures_3_names.size()); ++i)
      {
        textures_3[i] = std::move(load_texture_fn(textures_3_names[i]));
      }
    }
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

      const auto transform_property = CreateFMat3x4Property();
      const auto emission_property = CreateFVec3Property();
      const auto intensity_property = CreateFloatProperty();
      const auto diffuse_property = CreateFVec3Property();
      const auto metallic_property = CreateFloatProperty();
      const auto specular_property = CreateFVec3Property();
      const auto shininess_propert = CreateFloatProperty();
      const auto transmittance_property = CreateFVec3Property();
      const auto ior_property = CreateFloatProperty();

      const auto texture0_idx_property = CreateUIntProperty();
      const auto texture1_idx_property = CreateUIntProperty();
      const auto texture2_idx_property = CreateUIntProperty();
      const auto texture3_idx_property = CreateUIntProperty();

      const auto debug_color_property = CreateFVec3Property();

      const auto geometry_idx_property = CreateUIntProperty();

      const auto prim_offset_property = CreateUIntProperty();
      const auto prim_count_property = CreateUIntProperty();
      const auto vert_offset_property = CreateUIntProperty();
      const auto vert_count_property = CreateUIntProperty();

      transform_property->FromFMat3x4(instance.transform);
      emission_property->FromFVec3(instance.emission);
      intensity_property->FromFloat(instance.intensity);
      diffuse_property->FromFVec3(instance.diffuse);
      metallic_property->FromFloat(instance.metallic);
      specular_property->FromFVec3(instance.specular);
      shininess_propert->FromFloat(instance.shininess);
      transmittance_property->FromFVec3(instance.transmittance);
      ior_property->FromFloat(instance.ior);

      texture0_idx_property->FromUInt(instance.texture0_idx);
      texture1_idx_property->FromUInt(instance.texture1_idx);
      texture2_idx_property->FromUInt(instance.texture2_idx);
      texture3_idx_property->FromUInt(instance.texture3_idx);

      debug_color_property->FromFVec3(instance.debug_color);

      prim_offset_property->FromUInt(instance.prim_offset);
      prim_count_property->FromUInt(instance.prim_count);
      vert_offset_property->FromUInt(instance.vert_offset);
      vert_count_property->FromUInt(instance.vert_count);

      item_property->SetObjectItem("transform", transform_property);
      item_property->SetObjectItem("emission", emission_property);
      item_property->SetObjectItem("intensity", intensity_property);
      item_property->SetObjectItem("diffuse", diffuse_property);
      item_property->SetObjectItem("metallic", metallic_property);
      item_property->SetObjectItem("specular", specular_property);
      item_property->SetObjectItem("shininess", shininess_propert);
      item_property->SetObjectItem("transmittance", transmittance_property);
      item_property->SetObjectItem("ior", ior_property);
      item_property->SetObjectItem("texture0_idx", texture0_idx_property);
      item_property->SetObjectItem("texture1_idx", texture1_idx_property);
      item_property->SetObjectItem("texture2_idx", texture2_idx_property);
      item_property->SetObjectItem("texture3_idx", texture3_idx_property);
      item_property->SetObjectItem("debug_color", debug_color_property);
      item_property->SetObjectItem("prim_offset", prim_offset_property);
      item_property->SetObjectItem("prim_count", prim_count_property);
      item_property->SetObjectItem("vert_offset", vert_offset_property);
      item_property->SetObjectItem("vert_count", vert_count_property);

      root_property->SetArrayItem(i, item_property);
    }

    return root_property;
  }


  std::shared_ptr<Property> ImportOBJ(const std::string& path, const std::string& name, float scale, uint32_t mipmaps)
  {
    tinyobj::attrib_t obj_attrib;
    std::vector<tinyobj::shape_t> obj_shapes;
    std::vector<tinyobj::material_t> obj_materials;

    std::string warnings;
    std::string errors;
    BLAST_ASSERT(true == tinyobj::LoadObj(&obj_attrib, &obj_shapes, &obj_materials, &warnings, &errors, (path + name).c_str(), path.c_str(), true));


    std::vector<Vertex> scene_vertices;
    std::vector<Triangle> scene_triangles;
    std::vector<Instance> scene_instances;

    std::vector<Texture> textures_0;
    std::vector<Texture> textures_1;
    std::vector<Texture> textures_2;
    std::vector<Texture> textures_3;

    std::vector<std::vector<Vertex>> temp_vertices;
    std::vector<std::vector<Triangle>> temp_triangles;

    ConvertSceneOBJ(obj_attrib, obj_shapes, obj_materials, 
      temp_vertices, temp_triangles, scene_instances, scale, 
      path, textures_0, textures_1, textures_2, textures_3);

    for (uint32_t i = 0; i < uint32_t(scene_instances.size()); ++i)
    {
      scene_vertices.insert(scene_vertices.end(), temp_vertices[i].data(), temp_vertices[i].data() + temp_vertices[i].size());
      scene_triangles.insert(scene_triangles.end(), temp_triangles[i].data(), temp_triangles[i].data() + temp_triangles[i].size());
    }
    temp_vertices.clear();
    temp_triangles.clear();

    auto root = std::shared_ptr<Property>(new Property(Property::TYPE_OBJECT));
    //root->SetValue(Property::object());

    const auto vertices_property = CreateBufferProperty(scene_vertices.data(), uint32_t(sizeof(Vertex)), uint32_t(scene_vertices.size()));
    root->SetObjectItem("vertices", vertices_property);
    const auto triangles_property = CreateBufferProperty(scene_triangles.data(), uint32_t(sizeof(Triangle)), uint32_t(scene_triangles.size()));
    root->SetObjectItem("triangles", triangles_property);
    const auto instances_property = CreateBufferProperty(scene_instances.data(), uint32_t(sizeof(Instance)), uint32_t(scene_instances.size()));
    root->SetObjectItem("instances", instances_property);

    const auto textures0_property = CreatePropertyFromTextures(textures_0, mipmaps);
    root->SetObjectItem("textures0", textures0_property);
    const auto textures1_property = CreatePropertyFromTextures(textures_1, mipmaps);
    root->SetObjectItem("textures1", textures1_property);
    const auto textures2_property = CreatePropertyFromTextures(textures_2, mipmaps);
    root->SetObjectItem("textures2", textures2_property);
    const auto textures3_property = CreatePropertyFromTextures(textures_3, mipmaps);
    root->SetObjectItem("textures3", textures3_property);

    return root;
  }


  std::shared_ptr<Property> ImportGLTF(const std::string& path, const std::string& name, float scale, uint32_t mipmaps)
  {
    tinygltf::Model model;
    tinygltf::TinyGLTF gltf_ctx;
    //tinygltf::LoadImageDataFunction loader;
    //tinygltf::LoadImageDataOption option;
    ////gltf_ctx.SetImageLoader()
    std::string err;
    std::string warn;
    const auto ret = gltf_ctx.LoadASCIIFromFile(&model, &err, &warn, (path + name).c_str());

    std::vector<Vertex> scene_vertices;
    std::vector<Triangle> scene_triangles;
    std::vector<Instance> scene_instances;

    std::vector<Texture> textures_0;
    std::vector<Texture> textures_1;
    std::vector<Texture> textures_2;
    std::vector<Texture> textures_3;

    std::vector<std::vector<Vertex>> temp_vertices;
    std::vector<std::vector<Triangle>> temp_triangles;

    ConvertSceneGLTF(model, temp_vertices, temp_triangles, scene_instances, scale,
      textures_0, textures_1, textures_2, textures_3);

    for (uint32_t i = 0; i < uint32_t(scene_instances.size()); ++i)
    {
      scene_vertices.insert(scene_vertices.end(), temp_vertices[i].data(), temp_vertices[i].data() + temp_vertices[i].size());
      scene_triangles.insert(scene_triangles.end(), temp_triangles[i].data(), temp_triangles[i].data() + temp_triangles[i].size());
    }
    temp_vertices.clear();
    temp_triangles.clear();

    auto root = std::shared_ptr<Property>(new Property(Property::TYPE_OBJECT));
    //root->SetValue(Property::object());

    const auto vertices_property = CreateBufferProperty(scene_vertices.data(), uint32_t(sizeof(Vertex)), uint32_t(scene_vertices.size()));
    root->SetObjectItem("vertices", vertices_property);
    const auto triangles_property = CreateBufferProperty(scene_triangles.data(), uint32_t(sizeof(Triangle)), uint32_t(scene_triangles.size()));
    root->SetObjectItem("triangles", triangles_property);
    //const auto instances_property = CreateInstanceProperty(scene_instances);
    const auto instances_property = CreateBufferProperty(scene_instances.data(), uint32_t(sizeof(Instance)), uint32_t(scene_instances.size()));
    root->SetObjectItem("instances", instances_property);

    const auto textures0_property = CreatePropertyFromTextures(textures_0, mipmaps);
    root->SetObjectItem("textures0", textures0_property);
    const auto textures1_property = CreatePropertyFromTextures(textures_1, mipmaps);
    root->SetObjectItem("textures1", textures1_property);
    const auto textures2_property = CreatePropertyFromTextures(textures_2, mipmaps);
    root->SetObjectItem("textures2", textures2_property);
    const auto textures3_property = CreatePropertyFromTextures(textures_3, mipmaps);
    root->SetObjectItem("textures3", textures3_property);

    return root;
  }

  std::shared_ptr<Property> ImportEXR(const std::string& path, const std::string& name, float exposure, uint32_t mipmaps)
  {
    int32_t src_tex_x = 0;
    int32_t src_tex_y = 0;
    int32_t src_tex_n = 4;
    float* src_tex_data = nullptr;
    BLAST_ASSERT(0 == LoadEXR(&src_tex_data, &src_tex_x, &src_tex_y, (name).c_str(), nullptr));

    int32_t dst_tex_x = src_tex_x;
    int32_t dst_tex_y = src_tex_y;
    int32_t dst_tex_n = 4;
    float* dst_tex_data = new float[dst_tex_x * dst_tex_y * dst_tex_n];
    for (uint32_t j = 0; j < src_tex_x * src_tex_y; ++j)
    {
      const auto r = src_tex_n > 0 ? src_tex_data[j * src_tex_n + 0] : 0; //0xFF;
      const auto g = src_tex_n > 1 ? src_tex_data[j * src_tex_n + 1] : r; //0xFF;
      const auto b = src_tex_n > 2 ? src_tex_data[j * src_tex_n + 2] : r; //0xFF;
      const auto a = src_tex_n > 3 ? src_tex_data[j * src_tex_n + 3] : r; //0xFF;
      dst_tex_data[j * dst_tex_n + 0] = r * exposure;
      dst_tex_data[j * dst_tex_n + 1] = g * exposure;
      dst_tex_data[j * dst_tex_n + 2] = b * exposure;
      dst_tex_data[j * dst_tex_n + 3] = a * exposure;
    }
    delete[] src_tex_data;

    src_tex_data = dst_tex_data;
    src_tex_x = dst_tex_x;
    src_tex_y = dst_tex_y;
    src_tex_n = dst_tex_n;

    const auto get_pot_fn = [](int32_t value)
    {
      int32_t power = 0;
      while ((1 << power) < value) ++power;
      return power;
    };

    const auto pow_tex_x = get_pot_fn(src_tex_x);
    const auto pow_tex_y = get_pot_fn(src_tex_y);
    const auto pow_delta = std::abs(pow_tex_x - pow_tex_y);

    //const uint32_t tex_x = (1 << (pow_tex_x > pow_tex_y ? mipmap_count + pow_delta : mipmap_count)) - 1;
    //const uint32_t tex_y = (1 << (pow_tex_y > pow_tex_x ? mipmap_count + pow_delta : mipmap_count)) - 1;
    //const uint32_t tex_n = 4;

    const auto texel_pow_x = pow_tex_x > pow_tex_y ? mipmaps + pow_delta : mipmaps;
    const auto texel_pow_y = pow_tex_y > pow_tex_x ? mipmaps + pow_delta : mipmaps;
    const auto texel_count = uint32_t(((1 << texel_pow_x) * (1 << texel_pow_y) - 1) / 3);
    const auto texel_stride = uint32_t(sizeof(glm::f32vec4));
    float* texel_data = new float[texel_count * 4];

    dst_tex_x = 1 << (texel_pow_x - 1);
    dst_tex_y = 1 << (texel_pow_y - 1);
    dst_tex_n = src_tex_n;
    dst_tex_data = texel_data;
    stbir_resize_float(src_tex_data, src_tex_x, src_tex_y, 0, dst_tex_data, dst_tex_x, dst_tex_y, 0, dst_tex_n);
    delete[] src_tex_data;

    //const auto size_x_property = std::shared_ptr<Property>(new Property());
    //size_x_property->SetValue(uint32_t(dst_tex_x));

    //const auto size_y_property = std::shared_ptr<Property>(new Property());
    //size_y_property->SetValue(uint32_t(dst_tex_y));

    //const auto mipmaps_property = std::shared_ptr<Property>(new Property());
    //mipmaps_property->SetValue(uint32_t(mipmaps));

    src_tex_data = dst_tex_data;
    src_tex_x = dst_tex_x;
    src_tex_y = dst_tex_y;
    src_tex_n = dst_tex_n;

    for (uint32_t i = 1; i < mipmaps; ++i)
    {
      dst_tex_x = src_tex_x >> 1;
      dst_tex_y = src_tex_y >> 1;
      dst_tex_n = src_tex_n;
      dst_tex_data += src_tex_x * src_tex_y * src_tex_n;
      stbir_resize_float(src_tex_data, src_tex_x, src_tex_y, 0, dst_tex_data, dst_tex_x, dst_tex_y, 0, dst_tex_n);

      src_tex_data = dst_tex_data;
      src_tex_x = dst_tex_x;
      src_tex_y = dst_tex_y;
      src_tex_n = dst_tex_n;
    }

    const auto texels_property = std::shared_ptr<Property>(new Property(Property::TYPE_RAW));
    {
      texels_property->RawAllocate(texel_count * texel_stride);
      texels_property->SetRawBytes({ texel_data, texel_count * texel_stride }, 0);
    }
    delete[] texel_data;

    const auto texture_property = std::shared_ptr<Property>(new Property(Property::TYPE_ARRAY));
    //texture_property->SetValue(Property::array());
    texture_property->SetArraySize(1);
    texture_property->SetArrayItem(0, texels_property);

    return texture_property;
  }


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


  void SaveToPNG(const std::string& file_path, std::pair<const void*, uint32_t> bytes, uint32_t width, uint32_t height)
  {
    const auto src_tex_data = stbi_write_png(file_path.c_str(), width, height, 3, bytes.first, 4 * width);
  }


  std::tuple<std::pair<const void*, uint32_t>, int32_t, int32_t> LoadTextureFromFile(const std::string& path_name, bool gamma)
  {
    int32_t src_tex_x = 0;
    int32_t src_tex_y = 0;
    int32_t src_tex_n = 0;
    unsigned char* src_tex_data = stbi_load(path_name.c_str(), &src_tex_x, &src_tex_y, &src_tex_n, STBI_default);

    if (gamma)
    {
      const auto gamma_value = 2.2f;
      for (uint32_t i = 0; i < src_tex_x * src_tex_y; ++i)
      {
        if (src_tex_n > 0) src_tex_data[i * src_tex_n + 0] = uint8_t(255.0f * std::pow(src_tex_data[i * src_tex_n + 0] / 255.0f, gamma_value));
        if (src_tex_n > 1) src_tex_data[i * src_tex_n + 1] = uint8_t(255.0f * std::pow(src_tex_data[i * src_tex_n + 1] / 255.0f, gamma_value));
        if (src_tex_n > 2) src_tex_data[i * src_tex_n + 2] = uint8_t(255.0f * std::pow(src_tex_data[i * src_tex_n + 2] / 255.0f, gamma_value));
      }
    }

    int32_t dst_tex_x = src_tex_x;
    int32_t dst_tex_y = src_tex_y;
    int32_t dst_tex_n = 4;

    const auto dst_tex_size = dst_tex_x * dst_tex_y * dst_tex_n;
    auto* dst_tex_data = new unsigned char[dst_tex_size];
    for (uint32_t j = 0; j < src_tex_x * src_tex_y; ++j)
    {
      const uint8_t r = src_tex_n > 0 ? src_tex_data[j * src_tex_n + 0] : 0; //0xFF;
      const uint8_t g = src_tex_n > 1 ? src_tex_data[j * src_tex_n + 1] : r; //0xFF;
      const uint8_t b = src_tex_n > 2 ? src_tex_data[j * src_tex_n + 2] : r; //0xFF;
      const uint8_t a = src_tex_n > 3 ? src_tex_data[j * src_tex_n + 3] : r; //0xFF;
      dst_tex_data[j * dst_tex_n + 0] = r;
      dst_tex_data[j * dst_tex_n + 1] = g;
      dst_tex_data[j * dst_tex_n + 2] = b;
      dst_tex_data[j * dst_tex_n + 3] = a;

    }
    stbi_image_free(src_tex_data);

    src_tex_data = dst_tex_data;
    src_tex_x = dst_tex_x;
    src_tex_y = dst_tex_y;
    src_tex_n = dst_tex_n;

    const auto tex_x = src_tex_x;
    const auto tex_y = src_tex_y;

    return { { dst_tex_data, dst_tex_size }, tex_x, tex_y };
  }

  std::shared_ptr<Property> CreatePropertyFromTexture(std::pair<const void*, uint32_t> bytes, int32_t tex_x, int32_t tex_y, uint32_t mipmaps)
  {
    const auto mipmap_count_fn = [](uint32_t value)
    {
      uint32_t power = 0;
      while ((value >> power) > 0) ++power;
      return power;
    };
    mipmaps = mipmaps > 0 ? mipmaps : std::min(mipmap_count_fn(tex_x), mipmap_count_fn(tex_y));

    //const uint32_t tex_x = (1 << mipmaps) - 1;
    //const uint32_t tex_y = (1 << mipmaps) - 1;
    //const uint32_t tex_n = 4;

    const auto texel_count = uint32_t(((1 << mipmaps) * (1 << mipmaps) - 1) / 3);
    const auto texel_stride = uint32_t(sizeof(glm::u8vec4));
    unsigned char* texel_data = new unsigned char[texel_count * 4];

    auto dst_tex_x = 1 << (mipmaps - 1);
    auto dst_tex_y = 1 << (mipmaps - 1);
    auto dst_tex_n = 4;
    auto dst_tex_data = texel_data;

    stbir_resize_uint8(reinterpret_cast<const unsigned char*>(bytes.first), tex_x, tex_y, 0, dst_tex_data, dst_tex_x, dst_tex_y, 0, 4);

    auto src_tex_x = dst_tex_x;
    auto src_tex_y = dst_tex_y;
    auto src_tex_n = dst_tex_n;
    auto src_tex_data = dst_tex_data;

    for (uint32_t i = 1; i < mipmaps; ++i)
    {
      dst_tex_x = 1 << (mipmaps - 1 - i);
      dst_tex_y = 1 << (mipmaps - 1 - i);
      dst_tex_n = src_tex_n;
      dst_tex_data += src_tex_x * src_tex_y * src_tex_n;
      stbir_resize_uint8(src_tex_data, src_tex_x, src_tex_y, 0, dst_tex_data, dst_tex_x, dst_tex_y, 0, dst_tex_n);

      src_tex_data = dst_tex_data;
      src_tex_x = dst_tex_x;
      src_tex_y = dst_tex_y;
      src_tex_n = dst_tex_n;
    }


    const auto texels_property = std::shared_ptr<Property>(new Property(Property::TYPE_RAW));
    {
      texels_property->RawAllocate(texel_count * texel_stride);
      texels_property->SetRawBytes({ texel_data, texel_count * texel_stride }, 0);
    }
    delete[] texel_data;

    return texels_property;
  }


  std::shared_ptr<Property> CreatePropertyFromTextures(const std::vector<Texture>& textures, uint32_t mipmaps)
  {
    auto textures_property = std::shared_ptr<Property>(new Property(Property::TYPE_ARRAY));
 
    if (textures.empty())
    {
      textures_property->SetArraySize(uint32_t(1));

      const auto texel_value = glm::u8vec4(255, 255, 255, 255);
      const auto texel_size = uint32_t(sizeof(texel_value));

      const auto texels_property = std::shared_ptr<Property>(new Property(Property::TYPE_RAW));
      texels_property->RawAllocate(texel_size);
      texels_property->SetRawBytes({ &texel_value, texel_size }, 0);
      textures_property->SetArrayItem(0, texels_property);
    }
    else
    {
      textures_property->SetArraySize(uint32_t(textures.size()));
      for (uint32_t i = 0; i < textures_property->GetArraySize(); ++i)
      {
        const Texture& texture = textures[i];

        const auto tex_x = int32_t(texture.extent_x);
        const auto tex_y = int32_t(texture.extent_y);
        const auto tex_data = reinterpret_cast<const void*>(texture.texels.data());
        const auto tex_size = uint32_t(texture.texels.size() * sizeof(glm::u8vec4));

        const auto mipmaps_property = CreatePropertyFromTexture(std::pair(tex_data, tex_size), tex_x, tex_y, mipmaps);

        textures_property->SetArrayItem(i, mipmaps_property);
      }
    }
    return textures_property;
  }
}