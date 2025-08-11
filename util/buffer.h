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
    void Initialize(size_t count, T value = {});
    void Initialize(std::pair<const T*, size_t> structures);
    void Discard();

  public:
    size_t Count() const;
    void Set(size_t index, const T& value);
    const T& Get(size_t index) const;
    std::pair<uint8_t*, size_t> Access();
    
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
    SPtrProperty Export() const;
    void Import(SPtrProperty property);

  public:
    StructureBuffer(std::initializer_list<std::pair<const T*, size_t>> initializers = {})
      : raws(initializers.begin(), initializers.end())
    {}
    ~StructureBuffer() {}
  };
}