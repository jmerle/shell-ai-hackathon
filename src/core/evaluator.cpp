#include "evaluator.h"

#include <iostream>

Evaluator::Evaluator() {
  for (int i = 0; i < directionSlices.rows(); i++) {
    if (i == 0) {
      directionSlices(i) = 360.0;
    } else {
      directionSlices(i) = 10.0 * i;
    }
  }

  for (int i = 0; i < speedSlices.rows(); i++) {
    speedSlices(i) = 2.0 * i;
  }
}

double Evaluator::calculateAEP(const TurbineLocations &turbineLocations,
                               const PowerCurve &powerCurve,
                               const WindData &windData) const {
  // Power produced by the wind farm from each wind instance
  Matrix<36, 15> farmPower;
  farmPower.setZero();

  // Loop over every wind instance and calculate the power for that instance
  for (int i = 0, iMax = directionSlices.rows(); i < iMax; i++) {
    for (int j = 0, jMax = speedSlices.rows() - 1; j < jMax; j++) {
      // Take the middle value as effective speed
      double windDirection = directionSlices[i];
      double windSpeed = (speedSlices[j] + speedSlices[j + 1]) / 2.0;

      farmPower(i, j) = calculatePartialAEP(turbineLocations, powerCurve, windDirection, windSpeed);
    }
  }

  // Multiply the respective values with the probabilities of the wind instances
  farmPower *= binWindData(windData);

  // Convert farm power to AEP
  double aep = 365.0 * 24.0 * farmPower.sum();

  // Convert MWh to GWh
  return aep / 1000.0;
}

double Evaluator::calculatePartialAEP(const TurbineLocations &turbineLocations,
                                      const PowerCurve &powerCurve,
                                      double windDirection,
                                      double windSpeed) const {
  // Rotate turbine locations to downwind-crosswind according to the given wind direction
  auto rotatedLocations = rotateFrame(turbineLocations, windDirection);

  // Use Jensen's wake model to calculate speed deficits by wake
  auto speedDeficit = jensenParkWake(rotatedLocations, powerCurve, windSpeed);

  // Power of all turbines
  Vector<TurbineCount> turbinePower;
  turbinePower.setZero();

  // Calculate the individual turbine power for the given wind speed
  for (int i = 0; i < TurbineCount; i++) {
    // Effective wind speed due to the happening wake
    double effectiveWindSpeed = windSpeed * (1.0 - speedDeficit[i]);

    // Use the power curve data as look up to estimate the power produced
    // by the turbine for the corresponding closest matching wind speed
    int minRowIndex;
    (powerCurve.col(0) - effectiveWindSpeed).abs().minCoeff(&minRowIndex);

    turbinePower[i] = powerCurve(minRowIndex, 2);
  }

  // Sum the power from all turbines for the given wind instance
  return turbinePower.sum();
}

TurbineLocations Evaluator::rotateFrame(const TurbineLocations &turbineLocations, double windDirection) const {
  // TODO: Implement
  return TurbineLocations();
}

Vector<TurbineCount> Evaluator::jensenParkWake(const TurbineLocations &rotatedTurbineLocations,
                                               const PowerCurve &powerCurve,
                                               double windSpeed) const {
  // TODO: Implement
  return Vector<TurbineCount>();
}

Matrix<36, 15> Evaluator::binWindData(const WindData &windData) const {
  Matrix<36, 15> binnedWindData;
  binnedWindData.setZero();

  // Trap data points inside the bins
  for (int i = 0, iMax = directionSlices.rows(); i < iMax; i++) {
    for (int j = 0, jMax = speedSlices.rows() - 1; j < jMax; j++) {
      double targetDirection = directionSlices[i];
      double minSpeed = speedSlices[j];
      double maxSpeed = speedSlices[j + 1];

      int total = 0;

      for (int k = 0, kMax = windData.rows(); k < kMax; k++) {
        double direction = windData(k, 0);
        double speed = windData(k, 1);

        if (direction == targetDirection && speed >= minSpeed && speed < maxSpeed) {
          total++;
        }

        binnedWindData(i, j) = total;
      }
    }
  }

  return binnedWindData / binnedWindData.sum();
}
