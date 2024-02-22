annealing: annealing.cpp parameters.hpp parameters.cpp
	g++ -Wall -Wpedantic -Werror -O2 -o annealing parameters.cpp annealing.cpp
