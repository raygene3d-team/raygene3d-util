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
#include "util/storage.h"

namespace RayGene3D
{
  class Util : public Usable
  {
  public:
    enum StorageType
    {
      STORAGE_UNKNOWN = 0,
      STORAGE_LOCAL = 1,
      STORAGE_REMOTE = 2,
    };

  protected:
    StorageType type;

  protected:
    std::unique_ptr<Storage> storage;

  protected:
    std::list<std::weak_ptr<Property>> properties;

  public:
    void Initialize() override;
    void Use() override;
    void Discard() override;

  public:
    const std::unique_ptr<Storage>& GetStorage() { return storage; }

  public:
    void AddProperty(const std::shared_ptr<Property>& property) { return properties.push_back(property); }
    void VisitProperty(std::function<void(const std::shared_ptr<Property>&)> visitor) { for (const auto& property : properties) visitor(property.lock()); }
    //void RemoveProperty(const std::shared_ptr<Property>& property) { return properties.remove(property); }

  public:
    Util(StorageType type);
    virtual ~Util();
  };
}