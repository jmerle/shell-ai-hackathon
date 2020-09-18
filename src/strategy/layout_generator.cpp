#include "strategy/layout_generator.h"

TurbineLocations LayoutGenerator::generateLayout() const {
  TurbineLocations turbineLocations;

  int currentRow = 0;

  for (int y = PerimeterClearance; y < MapHeight - PerimeterClearance; y += ProximityThreshold) {
    for (int x = PerimeterClearance; x < MapWidth - PerimeterClearance; x += ProximityThreshold) {
      turbineLocations(currentRow, 0) = x;
      turbineLocations(currentRow, 1) = y;
      currentRow++;

      if (currentRow >= TurbineCount) {
        turbineLocations(49, 0) = turbineLocations(49, 0) + 0.0005;
        return turbineLocations;
      }
    }
  }

  return turbineLocations;
}
