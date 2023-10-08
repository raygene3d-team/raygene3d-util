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

#include "local_storage.h"

namespace RayGene3D
{
  void LocalStorage::Save(const std::string& alias, const std::shared_ptr<Property>& property)
  {
    std::map<std::shared_ptr<Property>, std::string> binaries;
    auto json = Property::ToJSON(property, binaries);

    try
    {
      std::string file_name = folder + '/' + alias + std::string(".json");
      std::ofstream file_stream(file_name, std::ios::out);
      file_stream << std::setw(4) << json << std::endl;
      file_stream.close();
    }
    catch (std::exception e)
    {
      return;
    }


    for (auto& [key, value] : binaries)
    {
      std::string file_name = folder + '/' + alias + value;
      std::ofstream file_stream(file_name, std::ios::out | std::ios::binary);

      const auto [byte, size] = key->GetRawBytes(0);
      file_stream.write(reinterpret_cast<const char*>(byte), size);
      file_stream.close();
    }
  }

  void LocalStorage::Load(const std::string& alias, std::shared_ptr<Property>& property) const
  {
    nlohmann::json json;

    try
    {
      std::string file_name = folder + '/' + alias + std::string(".json");
      std::ifstream file_stream(file_name, std::ios::in);
      file_stream >> std::setw(4) >> json;
      file_stream.close();
    }
    catch (std::exception e)
    {
      return;
    }

    std::map<std::shared_ptr<Property>, std::string> binaries;
    property = Property::FromJSON(json, binaries);

    for (auto& [key, value] : binaries)
    {
      std::string file_name = folder + '/' + alias + value;
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
  }
}