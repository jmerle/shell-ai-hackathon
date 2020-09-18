#include "core/file_reader.h"
#include "strategy/layout_evaluator.h"
#include "strategy/layout_generator.h"

#include <fstream>
#include <iostream>

int main() {
  LayoutEvaluator layoutEvaluator;
  layoutEvaluator.addWindData("data/wind/wind_data_2014.csv");
  layoutEvaluator.addWindData("data/wind/wind_data_2015.csv");
  layoutEvaluator.addWindData("data/wind/wind_data_2017.csv");

  FileReader fileReader;
  auto outputPath = fileReader.resolvePath("output/turbine_locations.csv");

  auto currentBestTurbineLocations = fileReader.readTurbineLocations(outputPath);
  auto currentBestAEP = layoutEvaluator.calculateAEP(currentBestTurbineLocations);

  std::cout << std::fixed << std::setprecision(5);
  std::cout << "Current best AEP: " << currentBestAEP << std::endl;

  LayoutGenerator layoutGenerator;

  // Continuously check for better layouts
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
  while (true) {
    auto turbineLocations = layoutGenerator.generateLayout();

    // If the first cell is set to -1.0 the LayoutGenerator was unable to create a valid layout
    // While exceptions would be nicer, this is faster
    if (turbineLocations(0, 0) < 0.0) {
      continue;
    }

    double aep = layoutEvaluator.calculateAEP(turbineLocations);

    if (aep > currentBestAEP) {
      std::cout << "New best AEP: " << aep << std::endl;

      currentBestAEP = aep;
      std::ofstream outputFile(outputPath);

      outputFile << "x,y" << std::endl;
      outputFile << std::fixed << std::setprecision(6);

      for (int i = 0; i < TurbineCount; i++) {
        outputFile << turbineLocations(i, 0) << "," << turbineLocations(i, 1) << std::endl;
      }

      outputFile.close();
    }
  }
#pragma clang diagnostic pop

  return 0;
}
