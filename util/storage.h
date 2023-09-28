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
  class Storage : public Usable //Serializable
  {
  protected:
    std::shared_ptr<Property> tree;

  //protected:
  //  std::string alias;

  //public:
  //  void SetProperty(const std::shared_ptr<Property>& property) { this->property = property; }
  //  const std::shared_ptr<Property>& GetProperty() const { return property; }

  //public:
  //  void SetAlias(const std::string& alias) { this->alias = alias; }
  //  const std::string& GetAlias() const { return alias; }

  //public:
  //  void Set(const std::string& name, const std::shared_ptr<Property>& property) { this->property->SetObjectItem(name, property); }
  //  const std::shared_ptr<Property>& Get(const std::string& name) const { return this->property->GetObjectItem(name); }
  //  bool Has(const std::string& name) { return this->property->HasObjectItem(name); }
  //  void Remove(const std::string& name) { this->property->RemoveObjectItem(name); }

  public:
    void SetTree(const std::shared_ptr<Property>& tree) { this->tree = tree; }
    const std::shared_ptr<Property>& GetTree() const { return tree; }
    
  public:
    virtual void Save(const std::string& alias, const std::shared_ptr<Property>& property) = 0;
    virtual void Load(const std::string& alias, std::shared_ptr<Property>& property) const = 0;

  public:
    void Initialize() override = 0;
    void Use() override = 0;
    void Discard() override = 0;

  public:
    Storage(const std::string& name) 
      : Usable(name) 
    {
      //property = std::shared_ptr<Property>(new Property(Property::TYPE_OBJECT));
    };

    virtual ~Storage()
    {
      //property.reset();
    };
  };
}