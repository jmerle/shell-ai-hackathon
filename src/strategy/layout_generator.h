#pragma once

#include "common.h"

#include "core/constraint_checker.h"

#include <random>

class LayoutGenerator {
  ConstraintChecker constraintChecker;

  std::uniform_real_distribution<double> distribution;
  std::mt19937 rng;

 public:
  LayoutGenerator();

  TurbineLocations generateLayout();

 private:
  double generateCoordinate();
};
