#include "test_helpers.h"

#include "core/constraint_checker.h"
#include "core/file_reader.h"

CLASS("ConstraintChecker") {
  ConstraintChecker constraintChecker;

  METHOD("isValidLayout") {
    TEST("Returns true on the turbine locations provided by the organizers") {
      FileReader fileReader;
      auto turbineLocations = fileReader.readTurbineLocations("data/turbine_loc_test.csv");

      REQUIRE(constraintChecker.isValidLayout(turbineLocations));
    }

    TEST("Returns false if the perimeter constraint is violated") {
      TurbineLocations turbineLocations;

      int currentRow = 0;

      for (int y = PerimeterClearance; y < MapHeight - PerimeterClearance; y += ProximityThreshold) {
        for (int x = PerimeterClearance; x < MapWidth - PerimeterClearance; x += ProximityThreshold) {
          if (currentRow >= TurbineCount) {
            break;
          }

          turbineLocations(currentRow, 0) = x;
          turbineLocations(currentRow, 1) = y;
          currentRow++;
        }
      }

      turbineLocations(0, 0) = PerimeterClearance - 1.0;

      REQUIRE(!constraintChecker.isValidLayout(turbineLocations));
    }

    TEST("Returns false if the proximity constraint is violated") {
      TurbineLocations turbineLocations;

      int currentRow = 0;

      for (int y = PerimeterClearance; y < MapHeight - PerimeterClearance; y += ProximityThreshold) {
        for (int x = PerimeterClearance; x < MapWidth - PerimeterClearance; x += ProximityThreshold) {
          if (currentRow >= TurbineCount) {
            break;
          }

          turbineLocations(currentRow, 0) = x;
          turbineLocations(currentRow, 1) = y;
          currentRow++;
        }
      }

      turbineLocations(0, 0) = PerimeterClearance + 1.0;

      REQUIRE(!constraintChecker.isValidLayout(turbineLocations));
    }
  }
}
