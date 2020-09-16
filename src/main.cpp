#include "file_reader.h"
#include "evaluator.h"

#include <iostream>
#include <list>
#include <string>

int main() {
  FileReader fileReader;
  Evaluator evaluator;

  auto turbineLocations = fileReader.readTurbineLocations("data/turbine_loc_test.csv");
  auto powerCurve = fileReader.readPowerCurve("data/power_curve.csv");

  std::list<std::string> windDataFiles;
  for (int year = 2007; year <= 2017; year++) {
    if (year > 2009 && year < 2013) {
      continue;
    }

    windDataFiles.push_back("data/wind/wind_data_" + std::to_string(year) + ".csv");
  }

  auto windSingle = fileReader.readWindData({windDataFiles.front()});
  auto windAll = fileReader.readWindData(windDataFiles);

  std::cout << "==================================================" << std::endl;
  std::cout << "Turbine locations:" << std::endl;
  std::cout << "==================================================" << std::endl;
  std::cout << turbineLocations << std::endl;

  std::cout << std::endl;

  std::cout << "==================================================" << std::endl;
  std::cout << "Power curve:" << std::endl;
  std::cout << "==================================================" << std::endl;
  std::cout << powerCurve << std::endl;

  std::cout << std::endl;

  std::cout << "==================================================" << std::endl;
  std::cout << "Wind data (single):" << std::endl;
  std::cout << "==================================================" << std::endl;
  std::cout << windSingle << std::endl;

  std::cout << std::endl;

  std::cout << "==================================================" << std::endl;
  std::cout << "Wind data (all):" << std::endl;
  std::cout << "==================================================" << std::endl;
  std::cout << windAll << std::endl;

  return 0;
}
