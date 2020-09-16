#pragma once

#include <eigen3/Eigen/Eigen>

#include <list>
#include <string>

class FileReader {
 public:
  Eigen::Matrix2d readTurbineLocations(const std::string &path) const;
  Eigen::Matrix3Xd readPowerCurve(const std::string &path) const;
  Eigen::Matrix2Xd readWindData(const std::list<std::string> &paths) const;
};
