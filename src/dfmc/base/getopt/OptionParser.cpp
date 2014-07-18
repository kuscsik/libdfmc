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

#include <dfmc/base/getopt/OptionParser.hpp>
#include <dfmc/base/string/ParseUtil.hpp>
#include <dfmc/base/system/ProcessAffinity.hpp>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>

namespace dfmc
{
  namespace 
  {
    void FillArgumentVector(std::vector<struct option>& rDst, const std::deque<Option>& src)
    {
      rDst.resize(src.size()+1);
      const int count = src.size();
      for( int i=0; i<count; ++i )
        rDst[i] = src[i];

      // Terminate the argument list
      rDst[count] = Option(0, 0, 0, 0, 0);
    }

    const char*const SafeString(const char*const psz)
    {
      return psz != nullptr ? psz : "";
    }

    const std::string GetFormattedDescription(const char*const psz, const int indentation)
    {
      std::string str(psz);
      std::stringstream stream;

      std::string::const_iterator itrFrom = str.begin();
      std::string::const_iterator itrTo = str.end();
      std::string::const_iterator itrFound;
      const std::streamsize defaultWidth = stream.width();
      do
      {
        itrFound = std::find(itrFrom, itrTo, '\n');

        while (itrFrom != itrFound)
        {
          stream << *itrFrom;
          ++itrFrom;
        }
        if (itrFound != itrTo)
        {
          stream << "\n";
          stream.width(indentation);
          stream << " ";
          stream.width(defaultWidth);
          ++itrFound;
          itrFrom = itrFound;
        }
      } while (itrFound != itrTo);

      return stream.str();
    }

    int FindMaxCommandNameLength(const std::deque<Option>& args, const bool showHiddenOptions)
    {
      int maxLength = 0;
      std::deque<Option>::const_iterator itr = args.begin();
      const std::deque<Option>::const_iterator itrEnd = args.end();
      while (itr != itrEnd)
      {
        if (showHiddenOptions || !itr->isHiddenOption)
        {
          const int len = itr->name != nullptr ? strlen(itr->name) : 0;
          if (len > maxLength)
            maxLength = len;
        }
        ++itr;
      }
      return maxLength;
    }

    void DisplayHelp(const std::deque<Option>& args, const bool showHiddenOptions)
    {
      const int maxCommandNameLength = FindMaxCommandNameLength(args, showHiddenOptions);

      std::deque<Option>::const_iterator itr = args.begin();
      const std::deque<Option>::const_iterator itrEnd = args.end();

      // We utilize a string stream to ensure that no 'race conditions' occur with other users of cout
      std::stringstream stream;

      const std::streamsize defaultWidth = stream.width();
      while (itr != itrEnd)
      {
        if (showHiddenOptions || !itr->isHiddenOption)
        {
          // 4+ because of the "  --" 3+ because of the " = "
          std::string strDesc = GetFormattedDescription(SafeString(itr->pszDescription), 4+3+maxCommandNameLength);
          stream << "  --";
          stream.width(maxCommandNameLength);
          stream << std::left << SafeString(itr->name);
          stream.width(defaultWidth);
          stream << " = " << strDesc << std::endl;
        }
        ++itr;
      }

      std::cout << stream.str();
    }


    void SetProcessAffinity(const char*const pszCpuId)
    {
      int cpuId;
      ParseUtil::ParseString(cpuId, pszCpuId);
      ProcessAffinity::SetAffinity(cpuId);
    }

  }

  OptionParser::OptionParser()
    : mIsVerbose(false)
    , mbIncludeProcessAffinityOption(false)
  {
  }

  OptionParser::OptionParser(const bool bIncludeProcessAffinityOption)
    : mIsVerbose(false)
    , mbIncludeProcessAffinityOption(bIncludeProcessAffinityOption)
  {
  }

  bool OptionParser::Parse(int argc, char **argv, IOptionParser& optionParser)
  {
    std::vector<IOptionParser*> optionParsers;
    optionParsers.push_back(&optionParser);
    return Parse(argc, argv, optionParsers);
  }


  // TODO: this should output better error descriptions and it should supply a 'writer' to the optionParser
  bool OptionParser::Parse(int argc, char **argv, const std::vector<IOptionParser*>& optionParsers)
  {
    try
    {
      std::string strCombinedOptions;
      std::deque<Option> args;

      for (size_t i = 0; i < optionParsers.size(); ++i)
      {
        assert(optionParsers[i] != nullptr);
        std::string strOptions;
        optionParsers[i]->ExtractArguments(args, strOptions);
        strCombinedOptions += strOptions;
      }

      int verboseFlag = 0;
      // Add arguments that all test cases accept
      args.push_back(Option("help", no_argument, 0, 'h', "Display the help menu"));
      args.push_back(Option("verbose", no_argument, &verboseFlag, 1, "Enable verbose output"));
      args.push_back(Option("brief", no_argument, &verboseFlag, 0, "Disable verbose output"));
      args.push_back(Option("devHelp", no_argument, 0, 2, "Display the developer options", true));
      args.push_back(Option("devOverride", no_argument, 0, 3, "Enable the developer override flag", true));
      if (mbIncludeProcessAffinityOption)
        args.push_back(Option("processAffinity", required_argument, 0, 4, "Set process affinity", false));

      // FIX: we should detect option conflicts in the option configuration here

      strCombinedOptions += "h";

      // Convert the argument list to a vector so we can parse it to getopt
      std::vector<struct option> options;
      FillArgumentVector(options, args);

      bool devOverride = false;
      bool displayedHelp = false;
      int argumentErrorCount = 0;
      int argumentCount = 0;
      { // Parse the input parameters
        const char*const pszOptions = strCombinedOptions.c_str();
        int optionIndex = 0;
        int val = getopt_long(argc, argv, pszOptions, &options[0], &optionIndex);
        while (val >= 0)
        {
          switch (val)
          {
          case 0: // brief
            break;
          case 1: // verbose
            break;
          case 2: // Show hidden developer help
            DisplayHelp(args, true);
            displayedHelp = true;
            break;
          case 3:
            devOverride = true;
            break;
          case 4:
            SetProcessAffinity(optarg);
            break;
          case 'h':
            DisplayHelp(args, false);
            displayedHelp = true;
            break;
          default:
            {
              OptionParseResult::Enum result = OptionParseResult::NotHandled;
              size_t i = 0;
              while (i < optionParsers.size() && result == OptionParseResult::NotHandled)
              {
                result = optionParsers[i]->Parse(val, optarg, optionIndex);
                ++i;
              }
              if (result == OptionParseResult::Success)
                ++argumentCount;
              else // For now we just log unknown arguments as errors
                ++argumentErrorCount;
              break;
            }
          }
          val = getopt_long(argc, argv, pszOptions, &options[0], &optionIndex);
        }
      }

      mIsVerbose = (verboseFlag != 0);

      // For now we handle '-h' and '--devHelp' as errors if they are the only arguments (causing the program execution to stop)
      if (argumentErrorCount > 0)
        return false;
      if (argumentCount == 0 && displayedHelp)
        return false;

      for (size_t i = 0; i < optionParsers.size(); ++i)
      {
        if (!optionParsers[i]->ParsingCompleted(devOverride))
          return false;
      }
    }
    catch (const std::exception& ex)
    {
      std::cout << "OptionParsing failed with: " << ex.what() << std::endl;
      return false;
    }
    return true;
  }


  bool OptionParser::IsVerbose() const
  {
    return mIsVerbose;
  }

}
