#include "test_helpers.h"

#include "core/file_reader.h"

CLASS("FileReader") {
  FileReader fileReader;

  METHOD("readTurbineLocations") {
    TEST("Correctly reads from the provided file") {
      auto result = fileReader.readTurbineLocations("data/turbine_loc_test.csv");

      REQUIRE(result.rows() == TurbineCount);
      REQUIRE(result.cols() == 2);

      REQUIRE_NEAR(result(0, 0), 3690.323986);
      REQUIRE_NEAR(result(0, 1), 370.7575602);

      REQUIRE_NEAR(result(23, 0), 2666.504241);
      REQUIRE_NEAR(result(23, 1), 2714.172409);

      REQUIRE_NEAR(result(49, 0), 1776.427277);
      REQUIRE_NEAR(result(49, 1), 2577.90668);
    }
  }

  METHOD("readPowerCurve") {
    TEST("Correctly reads from the provided file") {
      auto result = fileReader.readPowerCurve("data/power_curve.csv");

      REQUIRE(result.rows() == 501);
      REQUIRE(result.cols() == 3);

      REQUIRE_NEAR(result(0, 0), 0.0);
      REQUIRE_NEAR(result(0, 1), 0.0);
      REQUIRE_NEAR(result(0, 2), 0.0);

      REQUIRE_NEAR(result(115, 0), 11.5);
      REQUIRE_NEAR(result(115, 1), 0.614938513);
      REQUIRE_NEAR(result(115, 2), 2.327019057);

      REQUIRE_NEAR(result(500, 0), 50.0);
      REQUIRE_NEAR(result(500, 1), 0.0);
      REQUIRE_NEAR(result(500, 2), 0.0);
    }
  }

  METHOD("readWindData") {
    TEST("Correctly reads from the provided file") {
      auto result = fileReader.readWindData("data/wind/wind_data_2007.csv");

      REQUIRE(result.rows() == 15548);
      REQUIRE(result.cols() == 2);

      REQUIRE_NEAR(result(0, 0), 290.0);
      REQUIRE_NEAR(result(0, 1), 12.829798);

      REQUIRE_NEAR(result(8895, 0), 310.0);
      REQUIRE_NEAR(result(8895, 1), 7.1014156);

      REQUIRE_NEAR(result(15547, 0), 160.0);
      REQUIRE_NEAR(result(15547, 1), 11.655424);
    }
  }
}
