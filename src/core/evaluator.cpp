#include "evaluator.h"

double Evaluator::calculateAEP(const TurbineLocations &turbineLocations,
                               const PowerCurve &powerCurve,
                               const WindData &windData) const {
  // TODO: Implement
  return 3.14159;
}

Matrix<36, 15> Evaluator::binWindData(const WindData &windData) const {
  return Matrix<36, 15>();
}

TurbineLocations Evaluator::rotateFrame(const TurbineLocations &turbineLocations, double windDirection) const {
  return TurbineLocations();
}

Vector<TurbineCount> Evaluator::jensenParkWake(const TurbineLocations &rotatedTurbineLocations,
                                               const PowerCurve &powerCurve,
                                               double windSpeed) const {
  return Vector<TurbineCount>();
}

double Evaluator::calculatePartialAEP(const TurbineLocations &turbineLocations,
                                      const PowerCurve &powerCurve,
                                      double windDirection,
                                      double windSpeed) const {
  return 0;
}
