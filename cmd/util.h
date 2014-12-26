/* Misc. useful utilities in command line programs */

#pragma once

#include <base/thrower.h>

namespace Cmd {

// Thrown when parsing args there is an error.
DEFINE_ERROR(TArgError, std::runtime_error, "problem with an argument");

// Throw this to unwind the stack and exit without an error code.
// Useful when you just need to get out (ex: --help is specified)
struct TCleanExit {};

struct TErrorExit {
  int ExitCode=-1;
  const std::string Message;
};

/* Helpers for parsing arguments of specific types. */
template <typename TVal>
TVal ParseArg(const std::string &val);


// Whether or not a value is required.
template <typename TVal>
struct THasValue : public std::true_type {};

// Parsing of a value when specified
template <>
inline std::string ParseArg<std::string>(const std::string &val) {
  return val;
}

// Specializations for different types
template <>
inline uint32_t ParseArg<uint32_t>(const std::string &val) {
  //TODO(cmaloney): This isn't a perfect parse...
  return std::stoi(val);
}

template <>
struct THasValue<bool> : public std::false_type {};

template <>
inline bool ParseArg<bool>(const std::string &val) {
  if (val.empty()) {
    return true;
  } else {
    if (val == "true" || val == "t" || val == "yes" || val == "y") {
      return true;
    } else if (val == "false" || val == "f" || val == "no" || val == "n") {
      return false;
    } else {
      throw TArgError("Bool value must be one of: true,false,t,f,yes,no,y,n");
    }
  }
}



} // Cmd
