#include "strategy/layout_generator.h"

LayoutGenerator::LayoutGenerator()
    : generator(std::random_device{}()), distribution(PerimeterClearance, MapSize - PerimeterClearance) {}

TurbineLocations LayoutGenerator::generateLayout() {
  TurbineLocations turbineLocations;

  for (int i = 0; i < TurbineCount; i++) {
    do {
      turbineLocations(i, 0) = generateCoordinate();
      turbineLocations(i, 1) = generateCoordinate();
    } while (!constraintChecker.checkProximityConstraint(turbineLocations, i + 1));
  }

  return turbineLocations;
}

double LayoutGenerator::generateCoordinate() {
  return distribution(generator);
}
