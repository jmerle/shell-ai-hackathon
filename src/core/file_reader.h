#pragma once

#include "constants.h"

#include <eigen3/Eigen/Dense>

#include <filesystem>
#include <string>
#include <vector>

class FileReader {
  std::filesystem::path rootDirectory;

 public:
  FileReader();

  Eigen::Matrix<double, TurbineCount, 2> readTurbineLocations(const std::string &path) const;
  Eigen::Matrix<double, Eigen::Dynamic, 3> readPowerCurve(const std::string &path) const;
  Eigen::Matrix<double, Eigen::Dynamic, 2> readWindData(const std::string &path) const;

 private:
  std::vector<std::vector<std::string>> readCsv(const std::string &path) const;
  std::filesystem::path resolvePath(const std::string &path) const;
};
