#include "test_helpers.h"

#include "core/evaluator.h"
#include "core/file_reader.h"

CLASS("Evaluator") {
  Evaluator evaluator;

  METHOD("calculateAEP") {
    TEST("Returns the correct AEP") {
      FileReader fileReader;
      auto turbineLocations = fileReader.readTurbineLocations("data/turbine_loc_test.csv");
      auto powerCurve = fileReader.readPowerCurve("data/power_curve.csv");
      auto windData = fileReader.readWindData("data/wind/wind_data_2007.csv");

      // There seem to be some floating point precision differences between C++ and Python
      // I hope a precision of 0.0001 is enough
      REQUIRE_THAT(evaluator.calculateAEP(turbineLocations, powerCurve, windData),
                   Catch::WithinAbs(505.450636596680, 0.0001));
    }
  }
}
