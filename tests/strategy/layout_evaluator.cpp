#include "test_helpers.h"

#include "strategy/layout_evaluator.h"

#include <string>
#include <unordered_map>

CLASS("LayoutEvaluator") {
  METHOD("calculateAEP") {
    std::unordered_map<std::string, double> fixtures;
    fixtures["data/fixtures/turbine_locations_528_84361.csv"] = 528.84361;
    fixtures["data/fixtures/turbine_locations_528_37033.csv"] = 528.37033;
    fixtures["data/fixtures/turbine_locations_528_39818.csv"] = 528.39818;
    fixtures["data/fixtures/turbine_locations_529_59957.csv"] = 529.59957;
    fixtures["data/fixtures/turbine_locations_528_88678.csv"] = 528.88678;

    for (const auto &fixture : fixtures) {
      TEST("Returns the correct mean AEP (" + std::to_string(fixture.second) + ")") {
        LayoutEvaluator layoutEvaluator;
        layoutEvaluator.addWindData("data/wind/wind_data_2014.csv");
        layoutEvaluator.addWindData("data/wind/wind_data_2015.csv");
        layoutEvaluator.addWindData("data/wind/wind_data_2017.csv");

        FileReader fileReader;
        auto turbineLocations = fileReader.readTurbineLocations(fixture.first);

        // There seem to be some floating point precision differences between C++ and Python
        // I hope a precision of 0.0001 is enough
        REQUIRE_THAT(layoutEvaluator.calculateAEP(turbineLocations), Catch::WithinAbs(528.84361, 0.0001));
      }
    }
  }
}
