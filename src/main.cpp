#include "core/constraint_checker.h"
#include "core/evaluator.h"
#include "core/file_reader.h"

#include <iostream>

int main() {
  FileReader fileReader;
  auto turbineLocations = fileReader.readTurbineLocations("data/turbine_loc_test.csv");
  auto powerCurve = fileReader.readPowerCurve("data/power_curve.csv");
  auto windData = fileReader.readWindData("data/wind/wind_data_2007.csv");

  ConstraintChecker constraintChecker;
  if (constraintChecker.isValidLayout(turbineLocations)) {
    std::cout << "Turbine locations are valid" << std::endl;
  } else {
    std::cout << "Turbine locations are invalid" << std::endl;
    return 1;
  }

  Evaluator evaluator;
  double aep = evaluator.calculateAEP(turbineLocations, powerCurve, windData);

  std::cout << "AEP: " << aep << std::endl;

  return 0;
}
