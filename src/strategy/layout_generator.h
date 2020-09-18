#pragma once

#include "common.h"

#include "core/constraint_checker.h"

#include <random>

class LayoutGenerator {
  ConstraintChecker constraintChecker;

  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution;

 public:
  LayoutGenerator();

  TurbineLocations generateLayout();

 private:
  double generateCoordinate();
};
