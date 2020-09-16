#include <eigen3/Eigen/Eigen>

#include <iostream>

int main() {
  Eigen::Matrix3d mat;
  mat.fill(3.14159);

  std::cout << mat << std::endl;

  return 0;
}
