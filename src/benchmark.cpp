#include "core/evaluator.h"
#include "core/file_reader.h"
#include "strategy/layout_generator.h"

#include <chrono>
#include <functional>
#include <iostream>

// The amount of times to run each function
constexpr int Runs = 5000;

double measureRunsPerSecond(const std::function<void()> &func) {
  auto start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < Runs; i++) {
    func();
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  return (double) Runs / ((double) duration / 1000.0);
}

double benchmarkEvaluator() {
  std::cout << "Preparing evaluator" << std::endl;

  FileReader fileReader;
  auto turbineLocations = fileReader.readTurbineLocations("data/turbine_loc_test.csv");
  auto powerCurve = fileReader.readPowerCurve("data/power_curve.csv");
  auto windData = fileReader.readWindData("data/wind/wind_data_2007.csv");

  Evaluator evaluator(powerCurve, windData);

  std::cout << "Running the evaluator " << Runs << " times, this may take a while" << std::endl;

  return measureRunsPerSecond([&]() -> void {
    evaluator.calculateAEP(turbineLocations);
  });
}

double benchmarkGenerator() {
  std::cout << "Preparing layout generator" << std::endl;

  LayoutGenerator layoutGenerator;

  std::cout << "Running the layout generator " << Runs << " times, this may take a while" << std::endl;

  return measureRunsPerSecond([&]() -> void {
    layoutGenerator.generateLayout();
  });
}

int main() {
  double evaluatorRuns = benchmarkEvaluator();
  double generatorRuns = benchmarkGenerator();

  std::cout << "Evaluations per second: " << evaluatorRuns << std::endl;
  std::cout << "Layout generations per second: " << generatorRuns << std::endl;

  return 0;
}
