#include "strategy/layout_evaluator.h"

LayoutEvaluator::LayoutEvaluator() : powerCurve(fileReader.readPowerCurve("data/power_curve.csv")) {}

double LayoutEvaluator::calculateAEP(const TurbineLocations &turbineLocations) const {
  return evaluator->calculateAEP(turbineLocations);
}

void LayoutEvaluator::addWindData(const std::string &path) {
  auto windData = fileReader.readWindData(path);

  for (int i = 0; i < windData.rows(); i++) {
    rows.push_back({windData(i, 0), windData(i, 1)});
  }

  WindData allWindData(rows.size(), 2);
  for (int i = 0; i < rows.size(); i++) {
    allWindData(i, 0) = rows[i].first;
    allWindData(i, 1) = rows[i].second;
  }

  if (evaluator != nullptr) {
    delete evaluator;
  }

  evaluator = new Evaluator(powerCurve, allWindData);
}
