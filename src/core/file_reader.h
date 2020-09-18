#pragma once

#include "common.h"

#include <filesystem>
#include <string>
#include <vector>

class FileReader {
  std::filesystem::path rootDirectory;

 public:
  FileReader();

  TurbineLocations readTurbineLocations(const std::string &path) const;
  PowerCurve readPowerCurve(const std::string &path) const;
  WindData readWindData(const std::string &path) const;

 private:
  std::vector<std::vector<std::string>> readCsv(const std::string &path) const;
  std::filesystem::path resolvePath(const std::string &path) const;
};
