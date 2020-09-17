#include <catch2/catch.hpp>

#include <cmath>
#include <string>

namespace internal {
bool isDouble(const std::string &thing) {
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

double getAbsoluteError(const std::string &number) {
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

#define REQUIRE_NEAR(actual, expected) \
  REQUIRE_THAT((actual), Catch::WithinAbs((expected), internal::getAbsoluteError(#expected)))

#define CLASS(name) TEST_CASE(name)
#define METHOD(name) SECTION(name)
#define TEST(description) SECTION("  " description)
