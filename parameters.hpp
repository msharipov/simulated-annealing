#ifndef ANNEALING_PARAM_HPP
#define ANNEALING_PARAM_HPP

#include <cstdint>
#include <cstdbool>
#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>

static constexpr size_t HEIGHT = 200,
                        WIDTH = 200;

static constexpr bool WRAPPED = true;
    
static constexpr uint32_t MAX_STEPS = 500000;


typedef std::pair<size_t, size_t>                   coord;
typedef std::pair<ptrdiff_t, ptrdiff_t>             coord_diff;
typedef std::pair<std::array<size_t, HEIGHT>,
                  std::array<size_t, WIDTH>>        path_t;

template <typename T>
using Matrix = std::array<std::array<T, WIDTH>, HEIGHT>;
template <typename T>
using up = std::unique_ptr<T>;

extern const std::vector<coord_diff> CLOSEST8;

extern const std::vector<coord_diff> ONEACROSS;

// Implemented in annealing.cpp!
// Returns the vector of coordinate pairs for all of the valid neighbors
// of ([r], [c]) defined by [offsets].
extern up<std::vector<coord>>
valid_neighbors(const size_t r, const size_t c,
                const ptrdiff_t max_r, const ptrdiff_t max_c,
                const std::vector<coord_diff> & offsets,
                const bool wrap=true);

extern double potential(const Matrix<int_fast8_t> & mat,
                        const size_t r, const size_t c,
                        const bool wrap=true);

extern bool accept(const double V_diff, const double T);

#endif
