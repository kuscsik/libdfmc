#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
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

#include <dfmc/demo/DemoDataProvider.hpp>
#include <cassert>

namespace dfmc
{
  DemoDataProvider::DemoDataProvider()
  {
  }


  DemoDataProvider::~DemoDataProvider()
  {
  }


  const IDemoDataPtr DemoDataProvider::GetData(const TypeInfo& typeInfo) const
  {
    const TypeToDataMap::const_iterator itr = mMap.find(typeInfo);
    return (itr != mMap.end() ? itr->second : IDemoDataPtr());
  }

  void DemoDataProvider::SetData(const TypeInfo& typeInfo, const IDemoDataPtr& data)
  {
    mMap[typeInfo] = data;
  }

}
