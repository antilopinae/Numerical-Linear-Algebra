module;

#include <iterative_methods_export.h>
#include <iostream>
#include "include/matplotlibcpp.h"
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "matrix.cpp"
#include <Eigen/Dense>

export module iterative_methods;

export class ITERATIVE_METHODS_EXPORT Algo    // <-- ALGO_EXPORT annotation added to the class definition
{
public:
    void helloWorld();
};

export void test_iterative_methods();

export int test_modules_f();

module: private;

int test_modules_f() //definition not reachable from importers of foo
{
    using namespace std;
    cout << __PRETTY_FUNCTION__ << endl;
    cout << "definition not reachable from importers of foo" << endl;
    return 43;
}

