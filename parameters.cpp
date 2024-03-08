#include "parameters.hpp"
#include <cmath>

const std::vector<coord_diff> CLOSEST8{
    coord{-1, -1},
    coord{-1, 0},
    coord{-1, 1},
    coord{0, -1},
    coord{0, 1},
    coord{1, -1},
    coord{1, 0},
    coord{1, 1}
};

const std::vector<coord_diff> ONEACROSS{
    coord{-2, 0},
    coord{0, -2},
    coord{0, 2},
    coord{2, 0}
};

double potential(const Matrix<int_fast8_t> &mat, const size_t r, const size_t c,
                 const bool wrap) {

    double V = 0;

    auto close = valid_neighbors(r, c, HEIGHT, WIDTH, CLOSEST8);
    for (const auto & n : *close) {
        V += 4 * mat[n.first][n.second];
    }

    auto far = valid_neighbors(r, c, HEIGHT, WIDTH, ONEACROSS);
    int_fast8_t far_count = 1;
    for (const auto & n : *far) {
        if (mat[n.first][n.second] == 1) {
            far_count *= 2;
        }
    }

    V -= far_count * 2;

    return V;
}

bool accept(const double V_diff, const double T) {

    if (V_diff < 0) {
        return true;
    }

    return (static_cast<double>(rand())) / RAND_MAX < std::exp(-V_diff / T);
}
