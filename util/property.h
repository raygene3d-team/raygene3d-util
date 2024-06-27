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
#include "types.h"

#include <nlohmann/json.hpp>
#include <digestpp/digestpp.hpp>



namespace RayGene3D
{
  //class Tickable
  //{
  //protected:
  //  std::string name;

  //protected:
  //  uint32_t limit{ 1u };
  //  uint32_t count{ 0u };

  //public:
  //  virtual void Tick() = 0;

  //public:
  //  const std::string& GetName() const { return name; }

  //public:
  //  uint32_t GetLimit() const { return limit; }
  //  uint32_t GetCount() const { return count; }

  //public:
  //  Tickable(const std::string& name) : name(name) {};
  //  virtual ~Tickable() {}
  //};


  class Property //Entity
  {
  //protected:
  //  std::string name;

  //public:
  //  enum Operation
  //  {
  //    OPERATION_NONE = 0,
  //    OPERATION_LOAD = 1,
  //    OPERATION_SAVE = 2,
  //  };

  //protected:
  //  Operation operation{ OPERATION_NONE };

  public:
    enum Type
    {
      TYPE_UNDEFINED = 0,
      TYPE_BOOL = 1,
      TYPE_REAL = 2,
      TYPE_SINT = 3,
      TYPE_UINT = 4,
      TYPE_STRING = 5,
      TYPE_OBJECT = 6,
      TYPE_ARRAY = 7,
      TYPE_RAW = 8,
    };

  public:
    typedef std::monostate undefined_t;
    typedef bool bool_t;
    typedef float real_t;
    typedef int32_t sint_t;
    typedef uint32_t uint_t;
    typedef std::string string_t;
    typedef std::map<std::string, std::shared_ptr<Property>> object_t;
    typedef std::vector<std::shared_ptr<Property>> array_t;
    typedef Raw raw_t;
    typedef std::variant<undefined_t, bool_t, sint_t, uint_t, real_t, string_t, object_t, array_t, raw_t> value_t;

  protected:
    value_t _value;

  public:
    void SetBool(bool_t value) { _value = value; }
    bool_t GetBool() const { return std::get<bool_t>(_value); }
    void SetSint(sint_t value) { _value = value; }
    sint_t GetSint() const { return std::get<sint_t>(_value); }
    void SetUint(uint_t value) { _value = value; }
    uint_t GetUint() const { return std::get<uint_t>(_value); }
    void SetReal(real_t value) { _value = value; }
    real_t GetReal() const { return std::get<real_t>(_value); }

    void SetString(const string_t& value) { _value = value; }
    const string_t& GetString() const { return std::get<string_t>(_value); }

    const std::shared_ptr<Property>& GetObjectItem(const std::string& name) const { return std::get<object_t>(_value).at(name); }
    void SetObjectItem(const std::string& name, const std::shared_ptr<Property>& property) { std::get<object_t>(_value)[name] = property; }
    bool HasObjectItem(const std::string& name) { return std::get<object_t>(_value).find(name) != std::get<object_t>(_value).end(); }
    void RemoveObjectItem(const std::string& name) { std::get<object_t>(_value).erase(name); }
    //void VisitObjectItem(std::function<void(const std::string&, const std::shared_ptr<Property>&)> visitor) { for (auto& v : std::get<object>(_value)) visitor(v.first, v.second); }
    //uint32_t CountObjectItem(){ return static_cast<uint32_t>(std::get<object>(_value).size()); }

    const std::shared_ptr<Property>& GetArrayItem(uint32_t index) const { return std::get<array_t>(_value).at(index); }
    void SetArrayItem(uint32_t index, const std::shared_ptr<Property>& property) { std::get<array_t>(_value).at(index) = property; }
    uint32_t GetArraySize() const { return uint32_t(std::get<array_t>(_value).size()); }
    void SetArraySize(uint32_t size) { std::get<array_t>(_value).resize(size); }

    void RawAllocate(uint32_t size) { std::get<raw_t>(_value).Allocate(size); }
    void RawFree() { std::get<raw_t>(_value).Free(); }
    void SetRawBytes(std::pair<const void*, uint32_t> bytes, uint32_t offset) { std::get<raw_t>(_value).SetBytes(bytes, offset); }
    std::pair<const void*, uint32_t> GetRawBytes(uint32_t offset) const { return std::get<raw_t>(_value).GetBytes(offset); }
    template<typename T> void SetTypedBytes(std::pair<const T*, uint32_t> bytes, uint32_t offset) { std::get<raw_t>(_value).SetElements<T>(bytes, offset); }
    template<typename T> std::pair<const T*, uint32_t> GetTypedBytes(uint32_t offset) { return std::get<raw_t>(_value).GetElements<T>(offset); }

    void SetRaw(Raw&& raw) { std::get<raw_t>(_value) = std::move(raw); }
    Raw&& GetRaw() { return std::move(std::get<raw_t>(_value)); }
    const Raw&& GetRaw() const { return std::move(std::get<raw_t>(_value)); }



  public:
    void FromFMat3x4(const glm::f32mat3x4& mat);
    void FromFVec4(const glm::f32vec4& vec);
    void FromFVec3(const glm::f32vec3& vec);
    void FromFVec2(const glm::f32vec2& vec);
    void FromFloat(float value);
    void FromUVec4(const glm::u32vec4& vec);
    void FromUVec3(const glm::u32vec3& vec);
    void FromUVec2(const glm::u32vec2& vec);
    void FromUInt(uint32_t value);

    glm::f32mat3x4 ToFMat3x4() const;
    glm::f32vec4 ToFVec4() const;
    glm::f32vec3 ToFVec3() const;
    glm::f32vec2 ToFVec2() const;
    float ToFloat() const;
    glm::u32vec4 ToUVec4() const;
    glm::u32vec3 ToUVec3() const;
    glm::u32vec2 ToUVec2() const;
    uint32_t ToUInt() const;

  public:
    Property(Type type)
    {
      switch (type)
      {
      case TYPE_UNDEFINED:  _value.emplace<0>(); break;
      case TYPE_BOOL:       _value.emplace<1>(); break;
      case TYPE_REAL:       _value.emplace<2>(); break;
      case TYPE_SINT:       _value.emplace<3>(); break;
      case TYPE_UINT:       _value.emplace<4>(); break;
      case TYPE_STRING:     _value.emplace<5>(); break;
      case TYPE_OBJECT:     _value.emplace<6>(); break;
      case TYPE_ARRAY:      _value.emplace<7>(); break;
      case TYPE_RAW:        _value.emplace<8>(); break;
      }
    }
    ~Property() {}

  public:
    static nlohmann::json ToJSON(const std::shared_ptr<Property>& property, std::map<std::shared_ptr<Property>, std::string>& binaries);
    static std::shared_ptr<Property> FromJSON(const nlohmann::json& node, std::map<std::shared_ptr<Property>, std::string>& binaries);
  };

  typedef std::shared_ptr<Property> SPtrProperty;
  typedef std::weak_ptr<Property> WPtrProperty;
  typedef std::unique_ptr<Property> UPtrProperty;

  //class Prop;
  //
  //using null_t = std::monostate;
  //using bool_t = bool;
  //using sint_t = int;
  //using uint_t = unsigned int;
  //using real_t = float;
  //using span_t = Span;
  //using string_t = std::string;
  //using array_t = std::vector<Prop>;
  //using object_t = std::map<std::string, Prop>;
  //using value_t = std::variant<null_t, bool_t, sint_t, uint_t, real_t, span_t, string_t, array_t, object_t>;

  //class Prop
  //{
  //protected:
  //  value_t value;

  //public:
  //  template<typename T> const T& GetPropValue() const { return std::get<T>(this->value); }
  //  template<typename T> void SetPropValue(const T& value) { this->value = value; }

  //  const Prop& GetObjectProp(const std::string& name) const { return std::get<object_t>(this->value).at(name); }
  //  void SetObjectProp(const std::string& name, const Prop& item) { std::get<object_t>(this->value).emplace(name, item); }
  //  Prop& operator[](const std::string& name) { return std::get<object_t>(this->value).operator[](name); }
  //  bool ExistObjectProp(const std::string& name) { return std::get<object_t>(this->value).find(name) != std::get<object_t>(this->value).end(); }
  //  void RemoveObjectProp(const std::string& name) { std::get<object_t>(this->value).erase(name); }

  //  const Prop& GetArrayProp(uint32_t index) const { return std::get<array_t>(this->value).at(index); }
  //  void SetArrayProp(uint32_t index, const Prop& item) { std::get<array_t>(this->value).at(index) = item; }
  //  Prop& operator[](uint32_t index) { return std::get<array_t>(this->value).at(index); }
  //  uint32_t GetArraySize() const { return static_cast<uint32_t>(std::get<array_t>(this->value).size()); }
  //  void SetArraySize(uint32_t size) { std::get<array_t>(this->value).resize(size); }

  //  void SetSpanSize(std::pair<uint32_t, uint32_t> size) { std::get<span_t>(this->value).SetSize(size); }
  //  std::pair<uint32_t, uint32_t> GetSpanSize() const { return std::get<span_t>(this->value).GetSize(); }
  //  void SetSpanBytes(std::pair<const void*, uint32_t> bytes, uint32_t offset) { std::get<span_t>(this->value).SetBytes(bytes, offset); }
  //  std::pair<const void*, uint32_t> GetSpanBytes(uint32_t offset) const { return std::get<span_t>(this->value).GetBytes(offset); }

  //public:
  //  Prop() {}
  //  Prop(const value_t& value) { this->value = value; }
  //  ~Prop() {}

  //};

  std::shared_ptr<Property> ParseJSON(const nlohmann::json& node);



  std::shared_ptr<Property> CreateFMat3x4Property();
  std::shared_ptr<Property> CreateFVec4Property();
  std::shared_ptr<Property> CreateFVec3Property();
  std::shared_ptr<Property> CreateFVec2Property();
  std::shared_ptr<Property> CreateFloatProperty();
  std::shared_ptr<Property> CreateUVec4Property();
  std::shared_ptr<Property> CreateUVec3Property();
  std::shared_ptr<Property> CreateUVec2Property();
  std::shared_ptr<Property> CreateUIntProperty();

  std::shared_ptr<Property> CreateBufferProperty(const std::vector<Raw>& raws, uint32_t stride, uint32_t count);
  std::shared_ptr<Property> CreateTextureProperty(const std::vector<Raw>& raws, uint32_t extent_x, uint32_t extent_y, 
    Format format, uint32_t mipmap, uint32_t layers);

  void ExportTextureLDR(const std::shared_ptr<Property>& root, const std::string& path, uint32_t layer = 0u);
  std::shared_ptr<Property> ImportTextureLDR(const std::vector<std::string>& path, uint32_t mipmap, bool symmetric, bool srgb);

  void ExportTextureHDR(const std::shared_ptr<Property>& root, const std::string& path, uint32_t layer = 0u);
  std::shared_ptr<Property> ImportTextureHDR(const std::vector<std::string>& path, uint32_t mipmap, bool symmetric, bool cube);

  void ExportBuffer(const std::shared_ptr<Property>& root, const std::string& path, uint32_t index = 0u);
  std::shared_ptr<Property> ImportBuffer(const std::vector<std::string>& path, uint32_t stride);

  void SaveProperty(const std::string& directory, const std::string& name, const std::shared_ptr<Property>& root);
  std::shared_ptr<Property> LoadProperty(const std::string& directory, const std::string& name);

  std::tuple<Raw, uint32_t, uint32_t> LoadTexture(const std::string& path, bool symmetric, bool srgb);
  void SaveTexture(const std::string& path, const Raw& raw, uint32_t extent_x, uint32_t extent_y);

  Raw LoadBuffer(const std::string& path);
  void SaveBuffer(const std::string& path, const Raw& raw);
}


