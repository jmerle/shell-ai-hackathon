#include "test_helpers.h"

#include "strategy/layout_evaluator.h"

CLASS("LayoutEvaluator") {
  METHOD("calculateAEP") {
    TEST("Returns the correct mean AEP") {
      LayoutEvaluator layoutEvaluator;
      layoutEvaluator.addWindData("data/wind/wind_data_2014.csv");
      layoutEvaluator.addWindData("data/wind/wind_data_2015.csv");
      layoutEvaluator.addWindData("data/wind/wind_data_2017.csv");

      FileReader fileReader;
      auto turbineLocations = fileReader.readTurbineLocations("data/fixtures/turbine_locations_528_84361.csv");

      // There seem to be some floating point precision differences between C++ and Python
      // I hope a precision of 0.0001 is enough
      REQUIRE_THAT(layoutEvaluator.calculateAEP(turbineLocations), Catch::WithinAbs(528.84361, 0.0001));
    }
  }
}
