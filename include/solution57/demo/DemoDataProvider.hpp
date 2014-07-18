#ifndef DFMC_DEMO_DEMODATAPROVIDER_HPP
#define DFMC_DEMO_DEMODATAPROVIDER_HPP
// ----------------------------------------------------------------------------
// Copyright 2013 DFMC Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------------------------------------------------------

#include <dfmc/base/Pointers.hpp>
#include <dfmc/base/Exceptions.hpp>
#include <dfmc/base/rtti/TypeInfo.hpp>
#include <dfmc/demo/IDemoData.hpp>
#include <map>

namespace dfmc
{
  typedef DFMC::shared_ptr<IDemoData> IDemoDataPtr;

  class DemoDataProvider 
  {
    typedef std::map<TypeInfo, IDemoDataPtr> TypeToDataMap;
    TypeToDataMap mMap;
  public:
    DemoDataProvider();
    ~DemoDataProvider();


    //! @brief Get the data associated with the type
    //! @return nullptr if not found.
    const IDemoDataPtr GetData(const TypeInfo& typeInfo) const;
    void SetData(const TypeInfo& typeInfo, const IDemoDataPtr& data);

    template<typename T>
    const DFMC::shared_ptr<T> Get()
    {
      const TypeInfo typeInfo(typeid(T));
      DFMC::shared_ptr<T> ptr = DFMC::dynamic_pointer_cast<T, IDemoData>(GetData(typeInfo));
      if (!ptr)
        throw UnknownTypeException(typeInfo.name());
      return ptr;
    }

    template<typename T>
    void Set(const DFMC::shared_ptr<T>& data)
    {
      const TypeInfo typeInfo(typeid(T));
      SetData(typeInfo, data);
    }
  };

}
#endif
