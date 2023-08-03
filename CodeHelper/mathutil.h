//
// Created by flif3 on 8/1/2023.
//

#pragma once

#include <cmath>

namespace Raytracer {

    bool epsilonComparison(double a, double epsilon = 1e-06);

    bool areFloatingNumbersEqual(double a, double b, double epsilon = 1e-06);
}