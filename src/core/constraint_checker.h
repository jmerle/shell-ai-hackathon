#pragma once

#include "core/constants.h"

#include <eigen3/Eigen/Dense>

class ConstraintChecker {
 public:
  bool isValidLayout(const Eigen::Matrix<double, TurbineCount, 2> &turbineLocations) const;

 private:
  bool checkPerimeterConstraint(const Eigen::Matrix<double, TurbineCount, 2> &turbineLocations) const;
  bool checkProximityConstraint(const Eigen::Matrix<double, TurbineCount, 2> &turbineLocations) const;

  double getDistance(double x1, double y1, double x2, double y2) const;
};
