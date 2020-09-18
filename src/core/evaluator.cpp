#include "evaluator.h"

#include <cmath>
#include <iostream>

Evaluator::Evaluator(const PowerCurve &powerCurve, const WindData &windData) : powerCurve(powerCurve) {
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

  binnedWindData = binWindData(windData);
}

double Evaluator::calculateAEP(const TurbineLocations &turbineLocations) const {
  // Power produced by the wind farm from each wind instance
  Matrix<36, 15> farmPower;
  farmPower.setZero();

  // Loop over every wind instance and calculate the power for that instance
  for (int i = 0, iMax = directionSlices.rows(); i < iMax; i++) {
    for (int j = 0, jMax = speedSlices.rows() - 1; j < jMax; j++) {
      // Take the middle value as effective speed
      double windDirection = directionSlices[i];
      double windSpeed = (speedSlices[j] + speedSlices[j + 1]) / 2.0;

      // Calculate the AEP for this wind instance and multiply it by the probability of the wind instance
      farmPower(i, j) = calculatePartialAEP(turbineLocations, windDirection, windSpeed) * binnedWindData(i, j);
    }
  }

  // Convert farm power to AEP
  double aep = 365.0 * 24.0 * farmPower.sum();

  // Convert MWh to GWh
  return aep / 1000.0;
}

double Evaluator::calculatePartialAEP(const TurbineLocations &turbineLocations,
                                      double windDirection,
                                      double windSpeed) const {
  // Rotate turbine locations to downwind-crosswind according to the given wind direction
  auto rotatedLocations = rotateFrame(turbineLocations, windDirection);

  // Use Jensen's wake model to calculate speed deficits by wake
  auto speedDeficit = jensenParkWake(rotatedLocations, windSpeed);

  // Power of all turbines
  double turbinePower = 0.0;

  // Calculate the individual turbine power for the given wind speed
  for (int i = 0; i < TurbineCount; i++) {
    // Effective wind speed due to the happening wake
    double effectiveWindSpeed = windSpeed * (1.0 - speedDeficit[i]);

    // Use the power curve data as look up to estimate the power produced
    // by the turbine for the corresponding closest matching wind speed
    turbinePower += powerCurve(std::round(effectiveWindSpeed / 0.1), 2);
  }

  return turbinePower;
}

TurbineLocations Evaluator::rotateFrame(const TurbineLocations &turbineLocations, double windDirection) const {
  // Rotate the wind flow direction so that it aligns with the +ve x-axis
  windDirection -= 90.0;

  // Convert in-flow wind direction from degrees to radians
  windDirection = windDirection * Pi / 180.0;

  // Constants for coordinate transformation
  double cosDirection = std::cos(windDirection);
  double sinDirection = std::sin(windDirection);

  // Rotate coordinates to downwind-crosswind coordinates
  TurbineLocations rotatedLocations;
  rotatedLocations.col(0) = (turbineLocations.col(0) * cosDirection) - (turbineLocations.col(1) * sinDirection);
  rotatedLocations.col(1) = (turbineLocations.col(0) * sinDirection) + (turbineLocations.col(1) * cosDirection);

  return rotatedLocations;
}

Vector<TurbineCount> Evaluator::jensenParkWake(const TurbineLocations &rotatedTurbineLocations,
                                               double windSpeed) const {
  // Use the power curve data as look up to estimate the thrust coefficient
  // by the turbine for the corresponding closest matching wind speed
  double thrustCoefficient = powerCurve(std::round(windSpeed / 0.1), 1);

  // Velocity deficit suffered by each turbine for this particular wind instance
  Matrix<TurbineCount, TurbineCount> impactOnIbyj;
  impactOnIbyj.setZero();

  // Check the effect each turbine has on the others
  // i is the target turbine, j is the turbine which may cause a deficit for i
  for (int i = 0; i < TurbineCount; i++) {
    for (int j = 0; j < TurbineCount; j++) {
      double x = rotatedTurbineLocations(i, 0) - rotatedTurbineLocations(j, 0);

      if (x > 0) {
        double y = rotatedTurbineLocations(i, 1) - rotatedTurbineLocations(j, 1);
        double threshold = TurbineRadius + WakeDecay * x;

        if (std::abs(y) <= threshold) {
          // Use Jensen's model to calculate the impact
          impactOnIbyj(i, j) =
              (1 - std::sqrt(1 - thrustCoefficient)) * std::pow(TurbineRadius / threshold, 2);
        }
      }
    }
  }

  // Calculate the total speed deficit from all upstream turbines
  impactOnIbyj = impactOnIbyj.pow(2.0);
  Vector<TurbineCount> sum;

  for (int i = 0; i < TurbineCount; i++) {
    sum(i) = impactOnIbyj.row(i).sum();
  }

  return sum.sqrt();
}

Matrix<36, 15> Evaluator::binWindData(const WindData &windData) const {
  Matrix<36, 15> binnedData;
  binnedData.setZero();

  // Trap data points inside the bins
  for (int i = 0, iMax = directionSlices.rows(); i < iMax; i++) {
    for (int j = 0, jMax = speedSlices.rows() - 1; j < jMax; j++) {
      double targetDirection = directionSlices[i];
      double minSpeed = speedSlices[j];
      double maxSpeed = speedSlices[j + 1];

      int total = 0;

      for (int k = 0, kMax = windData.rows(); k < kMax; k++) {
        double direction = windData(k, 0);

        if (direction == targetDirection) {
          double speed = windData(k, 1);

          if (speed >= minSpeed && speed < maxSpeed) {
            total++;
          }
        }
      }

      binnedData(i, j) = total;
    }
  }

  return binnedData / binnedData.sum();
}
