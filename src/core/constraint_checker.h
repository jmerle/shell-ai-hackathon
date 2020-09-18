#pragma once

#include "common.h"

class ConstraintChecker {
 public:
  bool isValidLayout(const TurbineLocations &turbineLocations) const;

  bool checkPerimeterConstraint(const TurbineLocations &turbineLocations) const;
  bool checkProximityConstraint(const TurbineLocations &turbineLocations, int locationsToCheck = TurbineCount) const;

 private:
  double getDistance(double x1, double y1, double x2, double y2) const;
};
