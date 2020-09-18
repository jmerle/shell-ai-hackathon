#pragma once

#include "common.h"

#include "core/evaluator.h"
#include "core/file_reader.h"

#include <string>
#include <vector>

class LayoutEvaluator {
  std::vector<Evaluator> evaluators;

  FileReader fileReader;
  PowerCurve powerCurve;

 public:
  LayoutEvaluator();

  double calculateAEP(const TurbineLocations &turbineLocations) const;

  void addWindData(const std::string &path);
};
