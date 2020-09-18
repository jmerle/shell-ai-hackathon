#include "helpers.h"

#include "core/constraint_checker.h"
#include "core/file_reader.h"

CLASS("ConstraintChecker") {
  ConstraintChecker constraintChecker;

  FileReader fileReader;
  auto turbineLocations = fileReader.readTurbineLocations("data/turbine_loc_test.csv");

  METHOD("isValidLayout") {
    TEST("Returns true on the turbine locations provided by the organizers") {
      REQUIRE(constraintChecker.isValidLayout(turbineLocations));
    }

    TEST("Returns false if the perimeter constraint is violated") {
      turbineLocations(0, 0) = PerimeterClearance - 1.0;

      REQUIRE(!constraintChecker.isValidLayout(turbineLocations));
    }

    TEST("Returns false if the proximity constraint is violated") {
      turbineLocations(0, 0) = PerimeterClearance;
      turbineLocations(0, 1) = PerimeterClearance;

      turbineLocations(1, 0) = PerimeterClearance + ProximityThreshold - 1.0;
      turbineLocations(1, 1) = PerimeterClearance;

      REQUIRE(!constraintChecker.isValidLayout(turbineLocations));
    }
  }
}
