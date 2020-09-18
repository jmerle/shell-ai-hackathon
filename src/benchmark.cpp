#include "core/evaluator.h"
#include "core/file_reader.h"

#include <chrono>
#include <iostream>

// The amount of times to run the evaluator
constexpr int Runs = 100;

int main() {
  std::cout << "Preparing" << std::endl;

  FileReader fileReader;
  auto turbineLocations = fileReader.readTurbineLocations("data/turbine_loc_test.csv");
  auto powerCurve = fileReader.readPowerCurve("data/power_curve.csv");
  auto windData = fileReader.readWindData("data/wind/wind_data_2007.csv");

  Evaluator evaluator(powerCurve, windData);

  std::cout << "Running the evaluator " << Runs << " times, this may take a while" << std::endl;

  auto start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < Runs; i++) {
    evaluator.calculateAEP(turbineLocations);
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  std::cout << "Evaluations per second: " << ((double) Runs / ((double) duration / 1000.0)) << std::endl;

  return 0;
}
