#include "core/constraint_checker.h"

#include <cmath>

bool ConstraintChecker::isValidLayout(const Eigen::Matrix<double, TurbineCount, 2> &turbineLocations) const {
  return checkPerimeterConstraint(turbineLocations) && checkProximityConstraint(turbineLocations);
}

bool ConstraintChecker::checkPerimeterConstraint(const Eigen::Matrix<double, TurbineCount, 2> &turbineLocations) const {
  for (int i = 0; i < TurbineCount; i++) {
    double x = turbineLocations(i, 0);
    double y = turbineLocations(i, 1);

    if (x < PerimeterClearance || x > MapWidth - PerimeterClearance
        || y < PerimeterClearance || y > MapHeight - PerimeterClearance) {
      return false;
    }
  }

  return true;
}

bool ConstraintChecker::checkProximityConstraint(const Eigen::Matrix<double, TurbineCount, 2> &turbineLocations) const {
  for (int i = 0; i < TurbineCount; i++) {
    for (int j = 0; j < TurbineCount; j++) {
      if (i != j) {
        double x1 = turbineLocations(i, 0);
        double y1 = turbineLocations(i, 1);
        double x2 = turbineLocations(j, 0);
        double y2 = turbineLocations(j, 1);

        if (getDistance(x1, y1, x2, y2) < ProximityThreshold) {
          return false;
        }
      }
    }
  }

  return true;
}

double ConstraintChecker::getDistance(double x1, double y1, double x2, double y2) const {
  return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}
