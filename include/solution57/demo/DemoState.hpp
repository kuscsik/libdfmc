#ifndef DFMC_DEMO_DEMOSTATE_HPP
#define DFMC_DEMO_DEMOSTATE_HPP
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

namespace dfmc
{
  struct DemoState
  {
    enum Enum
    {
      // Continue rendering frames
      Running,
      // Stop rendering updating, drawing and flipping (the app can only be terminated via a interrupt)
      Freeze
    };
  };

}
#endif
