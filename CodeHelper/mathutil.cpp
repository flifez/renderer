//
// Created by flif3 on 8/2/2023.
//

#include "mathutil.h"

namespace Raytracer {
    bool epsilonComparison(double a, double epsilon) {
        // compare a and epsilon. If std::abs(a) < epsilon return true
        return std::abs(a) < epsilon;
    }

    bool areFloatingNumbersEqual(double a, double b, double epsilon) {
        return epsilonComparison(a - b, epsilon);
    }
}