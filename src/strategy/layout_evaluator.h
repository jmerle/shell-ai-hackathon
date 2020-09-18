#pragma once

#include "common.h"

#include "core/evaluator.h"
#include "core/file_reader.h"

#include <string>
#include <utility>
#include <vector>

class LayoutEvaluator {
  Evaluator *evaluator = nullptr;

  FileReader fileReader;
  PowerCurve powerCurve;

  std::vector<std::pair<double, double>> rows;

 public:
  LayoutEvaluator();

  double calculateAEP(const TurbineLocations &turbineLocations) const;

  void addWindData(const std::string &path);
};
