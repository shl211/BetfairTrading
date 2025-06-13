#pragma once

#include <cmath>
#include <limits>
#include <algorithm>

namespace BetfairAPI::Utils {

    inline bool almostEqual(double a, double b, 
                            double relEps = 1e-9, 
                            double absEps = 1e-12) {
        return std::fabs(a - b) <= std::max(relEps * std::max(std::fabs(a), std::fabs(b)), absEps);
    }
}