#include "strategy/layout_evaluator.h"

LayoutEvaluator::LayoutEvaluator() : powerCurve(fileReader.readPowerCurve("data/power_curve.csv")) {}

double LayoutEvaluator::calculateAEP(const TurbineLocations &turbineLocations) const {
  double totalAEP = 0.0;

  for (const auto &evaluator : evaluators) {
    totalAEP += evaluator.calculateAEP(turbineLocations);
  }

  return totalAEP / evaluators.size();
}

void LayoutEvaluator::addWindData(const std::string &path) {
  evaluators.push_back({powerCurve, fileReader.readWindData(path)});
}
