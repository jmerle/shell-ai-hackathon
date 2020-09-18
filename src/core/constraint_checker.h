#pragma once

#include "common.h"

class ConstraintChecker {
 public:
  bool isValidLayout(const TurbineLocations &turbineLocations) const;

 private:
  bool checkPerimeterConstraint(const TurbineLocations &turbineLocations) const;
  bool checkProximityConstraint(const TurbineLocations &turbineLocations) const;

  double getDistance(double x1, double y1, double x2, double y2) const;
};
