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

static constexpr uint32_t MAX_STEPS = 300000;


typedef std::pair<size_t, size_t>                   coord_t;
typedef std::pair<ptrdiff_t, ptrdiff_t>             coord_diff_t;

template <typename T>
using mat_t = std::array<std::array<T, WIDTH>, HEIGHT>;
template <typename T>
using up = std::unique_ptr<T>;

extern const std::vector<coord_diff_t> CLOSEST8;

extern const std::vector<coord_diff_t> ONEACROSS;

// Implemented in annealing.cpp!
// Returns the vector of coordinate pairs for all of the valid neighbors
// of ([r], [c]) defined by [offsets].
extern up<std::vector<coord_t>>
valid_neighbors(const size_t r, const size_t c,
                const size_t max_r, const size_t max_c,
                const std::vector<coord_diff_t> & offsets,
                const bool wrap=true);

extern double potential(const mat_t<int_fast8_t> & mat,
                        const size_t r, const size_t c,
                        const bool wrap=true);

extern bool accept(const double V_diff, const double T);

#endif
