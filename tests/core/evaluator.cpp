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

      REQUIRE_NEAR(evaluator.calculateAEP(turbineLocations, powerCurve, windData), 505.450636596680);
    }
  }
}
