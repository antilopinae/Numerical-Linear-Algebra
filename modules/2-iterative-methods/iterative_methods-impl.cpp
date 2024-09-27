module;

#include "include/matplotlibcpp.h"
#include "matrix.cpp"
#include <Eigen/Dense>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterative_methods_export.h>
#include <vector>

module iterative_methods;

void Algo::helloWorld() { std::cout << "hello world\n"; }

namespace plt = matplotlibcpp;

void print_matrix(Matrix<double> &&matrix, std::string name) {
  std::cout << name << std::endl;
  for (int i = 0; i < matrix.get_rows(); i++) {
    for (int j = 0; j < matrix.get_cols(); j++) {
      std::cout << matrix(i, j) << ", ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int method_UR(Matrix<double> A, int n, double t, double eps, int k_Max,
              int &k_Out, double &eps_Out) {
  double norm_old = 0;
  k_Out = 0;
  eps_Out = 0;
  int fl = 0;
  double t1 = 1 - t;

  // Нормировка системы
  for (int i = 0; i < n; ++i) {
    A(i, n + 1) = A(i, n); // копируем правую часть
    if (std::fabs(A(i, i)) < 1e-8)
      return 1; // если диагональный элемент мал, возвращаем ошибку
    A(i, n) = t * A(i, n) / A(i, i);
    for (int j = 0; j < n; ++j) {
      if (i != j)
        A(i, j) = t * A(i, j) / A(i, i);
    }
  }

  // Цикл по итерациям
  for (int k = 0; k < k_Max; ++k) {
    double norm = 0;
    ++k_Out;

    // Цикл по уравнениям
    for (int i = 0; i < n; ++i) {
      double buf = t1 * A(i, n + 1) + A(i, n);
      for (int j = 0; j < n; ++j) {
        if (i != j)
          buf -= A(i, j) * A(j, n + 1);
      }
      double nt = std::fabs(buf - A(i, n + 1));
      A(i, n + 1) = buf;
      if (nt > norm)
        norm = nt;
    }

    if (norm <= eps) {
      eps_Out = norm;
      return 0; // решение найдено
    }

    if (norm > norm_old) {
      ++fl;
    } else {
      fl = 0;
    }

    if (fl > 3) {
      eps_Out = norm;
      return 2; // решение не сходится
    }
    norm_old = norm;
  }
  return 0;
}

void test_iterative_methods() {
  int n = 3;
  double eps = 0.00001;
  int k_Max = 50000;
  double t = 1;

  Matrix<double> A(n, n, 0.0);
  Matrix<double> b(n, 1, 0.0);
  Matrix<double> x(n, 1, 0.0);

  std::srand(
      std::time(nullptr)); // use current time as seed for random generator

  // Генерация случайных чисел для матрицы A
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      A(i, j) = (std::rand() / double(RAND_MAX)) - 0.5;
    }
  }

  print_matrix(std::move(A), "Matrix A:");

  A = A.transpose() * A; // формируем систему уравнений

  print_matrix(std::move(A), "Matrix At * A:");

  // Генерация случайных чисел для вектора b
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      b(i, 0) += A(i, j);
    }
  }

  print_matrix(std::move(b), "Vector b (Ax=b):");

  Matrix<double> AR(n, n + 2, 0.0);

  // Формируем расширенную матрицу
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j)
      AR(i, j) = A(i, j);
    AR(i, n) = b(i, 0); // добавляем столбец b в расширенную матрицу
    AR(i, n + 1) = x(i, 0); // столбец для решения
  }

  print_matrix(std::move(AR), "Matrix (A,b,x):");

  Matrix<double> AR_old{AR}; // сохраняем исходную расширенную матрицу

  int k_Out = 0;
  double eps_Out = 0;
  int code = method_UR(std::move(AR), n, t, eps, k_Max, k_Out, eps_Out);

  std::cout << "code, eps, k: " << code << ", " << eps_Out << ", " << k_Out
            << std::endl;

  // Вывод решения
  std::cout << "Единичное решение: ";
  for (int i = 0; i < n; ++i) {
    std::cout << AR(i, n + 1) << " ";
  }
  std::cout << std::endl;

  print_matrix(std::move(AR), "Matrix (A,b,x):");

  // Построение зависимости
  t = 0.025;
  double topt = 5;
  double dt = 0.025;
  std::vector<double> Lt;
  std::vector<double> Lk;
  int k_Min = k_Max;

  for (int i = 0; i < 200; ++i) {
    AR = AR_old; // восстанавливаем исходную матрицу перед каждой итерацией
    code = method_UR(std::move(AR), n, t, eps, k_Max, k_Out, eps_Out);

    if (code == 0) {
      Lt.push_back(t);
      Lk.push_back(k_Out);
      if (k_Out < k_Min) {
        topt = t;
        k_Min = k_Out;
      }
    }
    std::cout << code;
    t += dt;
  }
  std::cout << std::endl;
  print_matrix(std::move(AR_old), "Old matrix");

  std::cout << "Оптимальные значения параметра t и итераций: " << topt << ", "
            << k_Min << std::endl;

  plt::plot(Lt, Lk);
  plt::title("Number of iter (param T)");

  plt::show();
}

// std::cout << "Test modules" << std::endl;
//
// using Eigen::MatrixXd;
// MatrixXd m(2, 2);
// m(0, 0) = 3;
// m(1, 0) = 2.5;
// m(0, 1) = -1;
// m(1, 1) = m(1, 0) + m(0, 1);
// std::cout << m << std::endl;
