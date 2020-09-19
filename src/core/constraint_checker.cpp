#include "core/constraint_checker.h"

#include <cmath>

bool ConstraintChecker::isValidLayout(const TurbineLocations &turbineLocations) const {
  return checkPerimeterConstraint(turbineLocations) && checkProximityConstraint(turbineLocations);
}

bool ConstraintChecker::checkPerimeterConstraint(const TurbineLocations &turbineLocations) const {
  for (int i = 0; i < TurbineCount; i++) {
    double x = turbineLocations(i, 0);
    double y = turbineLocations(i, 1);

    if (x < PerimeterClearance || x > MapSize - PerimeterClearance
        || y < PerimeterClearance || y > MapSize - PerimeterClearance) {
      return false;
    }
  }

  return true;
}

bool ConstraintChecker::checkProximityConstraint(const TurbineLocations &turbineLocations, int locationsToCheck) const {
  for (int i = 0; i < TurbineCount && i < locationsToCheck; i++) {
    for (int j = i + 1; j < TurbineCount && j < locationsToCheck; j++) {
      double x1 = turbineLocations(i, 0);
      double y1 = turbineLocations(i, 1);
      double x2 = turbineLocations(j, 0);
      double y2 = turbineLocations(j, 1);

      if (getDistance(x1, y1, x2, y2) < ProximityThreshold) {
        return false;
      }
    }
  }

  return true;
}

double ConstraintChecker::getDistance(double x1, double y1, double x2, double y2) const {
  return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}
