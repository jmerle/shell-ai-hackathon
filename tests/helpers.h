#pragma once

#include <catch2/catch.hpp>

#include <cmath>
#include <string>

namespace internal {
inline bool isDouble(const std::string &thing) {
  for (int i = 0; i < thing.length(); i++) {
    char ch = thing[i];

    if (ch == '.'
        || (ch >= '0' && ch <= '9')
        || ((ch == '+' || ch == '-') && i == 0)) {
      continue;
    }

    return false;
  }

  return true;
}

inline double getAbsoluteError(const std::string &number) {
  if (!isDouble(number)) {
    return 0.000'000'1;
  }

  auto dotIndex = number.find('.');
  if (dotIndex == std::string::npos) {
    return 0.000'000'1;
  }

  return 1.0 / std::pow(10.0, number.length() - dotIndex);
}
}

// Convenient wrappers around Catch2's TEST_CASE and SECTION macros
#define CLASS(name) TEST_CASE(name)
#define METHOD(name) SECTION(name)

// Catch2 only indents sections inside test cases, not sections inside sections
// Test descriptions are prefixed by two spaces so that they are properly indented when displayed
#define TEST(description) SECTION("  " description)

// A custom require which automatically figures out the absolute error to use when comparing doubles
// The absolute error that is used is 1/10^(decimals+1), where decimals is the amount of digits after the dot
// This affectively means that for an expected value of 1.234 an absolute error of 0.0001 is used
// If the amount of digits after the dot is not clear from the given expression, it falls back to 0.0000001
#define REQUIRE_NEAR(actual, expected) \
  REQUIRE_THAT((actual), Catch::WithinAbs((expected), internal::getAbsoluteError(#expected)))
