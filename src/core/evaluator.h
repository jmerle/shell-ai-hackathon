#pragma once

#include "common.h"

class Evaluator {
 public:
  double calculateAEP(const TurbineLocations &turbineLocations,
                      const PowerCurve &powerCurve,
                      const WindData &windData) const;

 private:
  /**
   * Converts wind data into a 2D matrix in which each row represents a wind direction and each row a speed instance.
   * Directions are binned in sections of 10 degrees, speed instances in sections of 2 m/s.
   *
   * Example:
   *             | 0<=s<2 | 2<=s<4 | ... | 26<=s<28 | 28<=s<30 |
   * |-----------|--------|--------|-----|----------|----------|
   * | dir = 360 |   --   |   --   | --- |    --    |    --    |
   * | dir = 10  |   --   |   --   | --- |    --    |    --    |
   * | dir = 20  |   --   |   --   | --- |    --    |    --    |
   * |    ...    |   --   |   --   | --- |    --    |    --    |
   * | dir = 340 |   --   |   --   | --- |    --    |    --    |
   * | dir = 350 |   --   |   --   | --- |    --    |    --    |
   */
  Matrix<36, 15> binWindData(const WindData &windData) const;

  /**
   * Rotates euclidean coordinates to downwind-crosswind coordinates.
   * Rotates the axes such that the wind flow direction aligns with the positive x-axis.
   */
  TurbineLocations rotateFrame(const TurbineLocations &turbineLocations, double windDirection) const;

  /**
   * For each turbine, returns the total velocity deficit due to the wakes from all contributing upstream turbines.
   * Uses Jensen's wake model.
   */
  Vector<TurbineCount> jensenParkWake(const TurbineLocations &rotatedTurbineLocations,
                                      const PowerCurve &powerCurve,
                                      double windSpeed) const;

  /**
   * Returns the total power produced by all turbines for the wind instance represented by windDirection.
   */
  double calculatePartialAEP(const TurbineLocations &turbineLocations,
                             const PowerCurve &powerCurve,
                             double windDirection,
                             double windSpeed) const;
};
