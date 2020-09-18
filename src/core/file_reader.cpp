#include "file_reader.h"

#include <fstream>
#include <sstream>

FileReader::FileReader() {
  auto currentPath = std::filesystem::current_path();

  // Figure out what the root directory of the project is
  // It is assumed that the binary is ran from the root of the project or from one of the directories in its subtree
  // When relative paths are to be converted into absolute ones, they are resolved relative to the root directory
  while (currentPath.has_parent_path()) {
    if (std::filesystem::exists(currentPath / "README.md")) {
      rootDirectory = currentPath;
      break;
    }

    currentPath = currentPath.parent_path();
  }
}

Eigen::Matrix<double, TurbineCount, 2> FileReader::readTurbineLocations(const std::string &path) const {
  auto csv = readCsv(path);

  Eigen::Matrix<double, TurbineCount, 2> turbineLocations;

  for (int i = 0; i < TurbineCount; i++) {
    turbineLocations(i, 0) = std::stod(csv[i][0]);
    turbineLocations(i, 1) = std::stod(csv[i][1]);
  }

  return turbineLocations;
}

Eigen::Matrix<double, Eigen::Dynamic, 3> FileReader::readPowerCurve(const std::string &path) const {
  auto csv = readCsv(path);

  Eigen::Matrix<double, Eigen::Dynamic, 3> powerCurve(csv.size(), 3);

  for (int i = 0; i < csv.size(); i++) {
    powerCurve(i, 0) = std::stod(csv[i][0]);
    powerCurve(i, 1) = std::stod(csv[i][1]);
    powerCurve(i, 2) = std::stod(csv[i][2]);
  }

  return powerCurve;
}

Eigen::Matrix<double, Eigen::Dynamic, 2> FileReader::readWindData(const std::string &path) const {
  auto csv = readCsv(path);

  Eigen::Matrix<double, Eigen::Dynamic, 2> windData(csv.size(), 2);

  for (int i = 0; i < csv.size(); i++) {
    windData(i, 0) = std::stod(csv[i][1]);
    windData(i, 1) = std::stod(csv[i][2]);
  }

  return windData;
}

std::vector<std::vector<std::string>> FileReader::readCsv(const std::string &path) const {
  std::ifstream file(resolvePath(path));

  std::string line;
  std::vector<std::vector<std::string>> rows;

  while (std::getline(file, line)) {
    std::vector<std::string> row;

    std::stringstream stream(line);
    std::string value;

    while (std::getline(stream, value, ',')) {
      row.push_back(value);
    }

    rows.push_back(row);
  }

  // All provided files contain a header row which we don't need
  if (!rows.empty()) {
    rows.erase(rows.begin());
  }

  return rows;
}

std::filesystem::path FileReader::resolvePath(const std::string &path) const {
  return rootDirectory / std::filesystem::path(path);
}
