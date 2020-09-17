#include "core/evaluator.h"
#include "core/file_reader.h"

#include <iostream>

int main() {
  FileReader fileReader;
  auto turbineLocations = fileReader.readTurbineLocations("data/turbine_loc_test.csv");
  auto powerCurve = fileReader.readPowerCurve("data/power_curve.csv");
  auto windData = fileReader.readWindData("data/wind/wind_data_2007.csv");

  Evaluator evaluator;
  double aep = evaluator.calculateAEP();

  std::cout << "AEP: " << aep << std::endl;

  return 0;
}
