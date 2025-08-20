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
  private:
    Raw _raw;

  public:
    size_t Stride() const { return sizeof(T); }
    size_t Count() const { return _raw.GetItems<T>().second; }
    void Set(std::pair<const T*, size_t> items, size_t offset = 0) { _raw.SetItems<T>(items, offset); }
    std::pair<const T*, size_t> Get(size_t offset = 0) const { return _raw.GetItems<T>(offset); }

  public:
    T& operator[](size_t index) { return *_raw.AccessItems<T>(index).first; }
    std::pair<uint8_t*, size_t> Bytes() { return _raw.AccessBytes(); }
    std::pair<T*, size_t> Items() { return _raw.AccessItems<T>(); }

  public:
    void Resize(size_t count, T value = {})
    { 
      auto raw = Raw(count, value);
      raw.SetItems<T>({ _raw.GetItems<T>().first, std::min(_raw.GetItems<T>().second, count) });
      std::swap(raw, _raw);
    }
    
  //public:
  //  Append(Raw raw) {}
  //  Raw Consume() {}

  //public:
  //  void Load(const char* name);
  //  void Save(const char* name);

  public:
    SPtrProperty Export() const
    {
      return SPtrProperty(new Property({
        {"stride", SPtrProperty(new Property(uint32_t(sizeof(T))))},
        {"count", SPtrProperty(new Property(uint32_t(_raw.AccessBytes().second / sizeof(T))))},
        {"raw", SPtrProperty(new Property(_raw.AccessBytes()))}}));
    }

    void Import(SPtrProperty property);

  public:
    StructureBuffer(std::pair<const T*, size_t> items = {})
      : _raw(items)
    {}

  public:
    StructureBuffer(const StructureBuffer& buffer) = delete;
    StructureBuffer& operator=(const StructureBuffer& buffer) = delete;
    StructureBuffer(StructureBuffer&& buffer) noexcept
    {
      std::swap(_raw, buffer._raw);
    }
    StructureBuffer& operator=(StructureBuffer&& buffer) noexcept
    {
      std::swap(_raw, buffer._raw);
      return *this;
    }
    ~StructureBuffer() {}
  };
}