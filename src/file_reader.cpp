#include "file_reader.h"

#include <fstream>
#include <sstream>

FileReader::FileReader() {
  auto currentPath = std::filesystem::current_path();

  while (currentPath.has_parent_path()) {
    if (std::filesystem::exists(currentPath / "README.md")) {
      rootDirectory = currentPath;
      break;
    }

    currentPath = currentPath.parent_path();
  }
}

Eigen::Matrix<double, 50, 2> FileReader::readTurbineLocations(const std::string &path) const {
  auto csv = readCsv(path);

  Eigen::Matrix<double, 50, 2> turbineLocations;

  for (int i = 0; i < 50; i++) {
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

Eigen::Matrix<double, Eigen::Dynamic, 2> FileReader::readWindData(const std::list<std::string> &paths) const {
  std::vector<std::vector<std::string>> rows;

  for (const auto &path : paths) {
    auto content = readCsv(path);
    rows.insert(rows.end(), content.begin(), content.end());
  }

  Eigen::Matrix<double, Eigen::Dynamic, 2> windData(rows.size(), 2);

  for (int i = 0; i < rows.size(); i++) {
    windData(i, 0) = std::stod(rows[i][1]);
    windData(i, 1) = std::stod(rows[i][2]);
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

  if (!rows.empty()) {
    rows.erase(rows.begin());
  }

  return rows;
}

std::filesystem::path FileReader::resolvePath(const std::string &path) const {
  return rootDirectory / std::filesystem::path(path);
}
