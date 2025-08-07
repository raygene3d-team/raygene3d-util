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

#include "buffer.h"

namespace RayGene3D
{
  size_t StructureBuffer::Count() const
  { 
    return raws.back().AccessBytes().second / stride;
  }

  template<typename T> void StructureBuffer::Initialize(size_t count, T value)
  {
    raws.push_back(std::move(Raw(count, value)));
  }

  void StructureBuffer::Discard()
  {
    raws.pop_back();
  }

  template<typename T> void StructureBuffer::Set(size_t index, const T& value)
  {
    raws.back().SetElement<T>(value, index);
  }

  template<typename T> const T& StructureBuffer::Get(size_t index) const
  {
    return raws.back().GetElement<T>(index);
  }

  std::pair<uint8_t*, size_t> StructureBuffer::Access()
  { 
    return raws.back().AccessBytes();
  }

  SPtrProperty StructureBuffer::Export() const
  {
    auto length = 0ull;
    auto counts = std::vector<size_t>();
    for (const auto& raw : raws)
    {
      const auto count = raw.GetBytes().second / stride;
      counts.push_back(count);
      length += count;
    }

    auto offset = 0ull;
    auto raw = Raw(length * stride);
    for(const auto& raw : raws)
    {
      auto bytes = raw.GetBytes();
      raw.SetBytes(bytes, offset);
      offset += bytes.second;
    }
        

    const auto root_property = std::shared_ptr<Property>(new Property(Property::TYPE_OBJECT));

    const auto stride_property = std::shared_ptr<Property>(new Property(Property::TYPE_UINT));
    stride_property->SetUint(stride);
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

  void StructureBuffer::Import(SPtrProperty property)
  {

  }
}