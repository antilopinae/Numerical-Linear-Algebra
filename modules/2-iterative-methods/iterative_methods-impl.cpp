module;

#include <Eigen/Dense>
#include <iostream>

module iterative_methods;

void Algo::helloWorld() { std::cout << "hello world\n"; }

void test_iterative_methods() {
  std::cout << "Test modules" << std::endl;

  using Eigen::MatrixXd;
  MatrixXd m(2, 2);
  m(0, 0) = 3;
  m(1, 0) = 2.5;
  m(0, 1) = -1;
  m(1, 1) = m(1, 0) + m(0, 1);
  std::cout << m << std::endl;
}
