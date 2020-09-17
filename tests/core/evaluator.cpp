#include "helpers.h"

#include "core/evaluator.h"

CLASS("Evaluator") {
  Evaluator evaluator;

  GIVEN("aaa") {}

  METHOD("calculateAEP") {
    TEST("Returns the correct AEP") {
      REQUIRE_NEAR(evaluator.calculateAEP(), 3.14159);
    }
  }
}
