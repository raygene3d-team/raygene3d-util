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
  template<typename T>
  struct StructureBuffer
  {
    std::list<Raw> raws;

  public:
    void Create(size_t count, T value = {}) { raws.push_back(std::move(Raw(count, value))); }
    void Create(std::pair<const T*, size_t> structures) { raws.push_back(std::move(Raw(structures))); }
    void Delete() { raws.pop_back(); }

  public:
    bool Empty(size_t layer) const { return raws.back().AccessBytes().second != 0; }
    size_t Count() const { return raws.back().AccessBytes().second / sizeof(T); }
    void Set(size_t index, const T& value) { raws.back().SetElement<T>(value, index); }
    const T& Get(size_t index) const { return raws.back().GetElement<T>(index); };
    std::pair<uint8_t*, size_t> Access() { return raws.back().AccessBytes(); }
    
  public:
    std::list<Raw>::iterator begin() { return raws.begin(); }
    std::list<Raw>::iterator end() { return raws.end(); }
    std::list<Raw>::const_iterator cbegin() const { return raws.cbegin(); }
    std::list<Raw>::const_iterator cend() const { return raws.cend(); }
    void Push(Raw&& raw) { raws.push_back(std::move(raw)); }
    void Pop() { raws.pop_back(); }

  //public:
  //  void Load(const char* name);
  //  void Save(const char* name);

  public:
    SPtrProperty Export() const
    {
      auto length = 0ull;
      auto counts = std::vector<size_t>();
      for (const auto& r : raws)
      {
        const auto count = r.GetBytes().second / sizeof(T); counts.push_back(count); length += count;
      }

      auto offset = 0ull;
      auto raw = Raw(length * sizeof(T));
      for (const auto& r : raws)
      {
        auto bytes = r.GetBytes(); raw.SetBytes(bytes, offset); offset += bytes.second;
      }


      const auto root_property = std::shared_ptr<Property>(new Property(Property::TYPE_OBJECT));

      const auto stride_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
      stride_property->SetUint(sizeof(T));
      root_property->SetObjectItem("stride", stride_property);

      const auto counts_property = std::shared_ptr<Property>(new Property(Property::TYPE_ARRAY));
      counts_property->SetArraySize(counts.size());
      for (auto i = 0ull; i < counts.size(); ++i)
      {
        const auto count_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
        count_property->SetUint(counts[i]);
        counts_property->SetArrayItem(i, count_property);
      }
      root_property->SetObjectItem("counts", counts_property);

      const auto raw_property = std::shared_ptr<Property>(new Property(Property::TYPE_RAW));
      raw_property->SetRaw(std::move(raw));
      root_property->SetObjectItem("raw", raw_property);

      return root_property;
    }
    void Import(SPtrProperty property);

  public:
    StructureBuffer(std::initializer_list<std::pair<const T*, size_t>> initializers = {})
      : raws(initializers.begin(), initializers.end())
    {}

  public:
    StructureBuffer(const StructureBuffer& raw) = delete;
    StructureBuffer& operator=(const StructureBuffer& raw) = delete;
    StructureBuffer(StructureBuffer&& buffer) noexcept
    {
      std::swap(raws, buffer.raws);
    }
    StructureBuffer& operator=(StructureBuffer&& buffer) noexcept
    {
      std::swap(raws, buffer.raws);
      return *this;
    }
    ~StructureBuffer() {}
  };
}