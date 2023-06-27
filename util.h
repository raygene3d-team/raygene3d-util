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
#include "broker.h"

namespace RayGene3D
{
  class Util : public Usable
  {
  public:
    enum Storage
    {
      STORAGE_UNKNOWN = 0,
      STORAGE_LOCAL = 1,
      STORAGE_REMOTE = 2,
    };

  protected:
    Storage storage;

  protected:
    std::shared_ptr<Property> property;

  protected:
    std::list<std::weak_ptr<Broker>> brokers;

  public:
    void Initialize() override;
    void Use() override;
    void Discard() override;

  public:
    const std::shared_ptr<Property>& GetProperty() { return property; }

  public:
    void AddBroker(const std::shared_ptr<Broker>& broker) { return brokers.push_back(broker); }
    void VisitBroker(std::function<void(const std::shared_ptr<Broker>&)> visitor) { for (const auto& broker : brokers) visitor(broker.lock()); }
    void RemoveBroker(const std::shared_ptr<Broker>& broker) { return brokers.remove(broker); }

  public:
    Util(Storage storage);
    virtual ~Util();
  };
}