#pragma once

#include <eigen3/Eigen/Dense>

// This file contains all commonly used constants and typedefs
// It is included by all files needing constants and/or matrices

// Constants
// All distances are in meters

constexpr int TurbineCount = 50;

constexpr double MapWidth = 4000.0;
constexpr double MapHeight = 4000.0;

constexpr double PerimeterClearance = 50.0;
constexpr double ProximityThreshold = 400.0;

constexpr double RotorDiameter = 100.0;
constexpr double RotorRadius = RotorDiameter / 2.0;

// Typedefs

template<int Rows, int Cols>
using Matrix = Eigen::Matrix<double, Rows, Cols>;

template<int Rows>
using Vector = Matrix<Rows, 1>;

using TurbineLocations = Matrix<TurbineCount, 2>;
using PowerCurve = Matrix<Eigen::Dynamic, 3>;
using WindData = Matrix<Eigen::Dynamic, 2>;
