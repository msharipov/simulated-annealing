#include "parameters.hpp"
#include <cstddef>


up<std::vector<coord_t>>
valid_neighbors(const size_t r, const size_t c,
                const ptrdiff_t max_r, const ptrdiff_t max_c,
                const std::vector<coord_diff_t> &offsets,
                const bool wrap) {

    up<std::vector<coord_t>> neighbors(new std::vector<coord_t>());
    for (const auto & n: offsets) {
        if (wrap) {

            coord_t new_n{(r + n.first + max_r) % max_r,
                          (c + n.second + max_c) % max_c};
            neighbors->push_back(new_n);

        } else {

            ptrdiff_t nr = r + n.first, nc = c + n.second;
            if (nr >= 0 && nr < max_r && nc >= 0 && nc < max_c) {
                neighbors->push_back(coord_t{nr, nc});
            }
        }
    }

    return neighbors;
}


void etch(mat_t<int_fast8_t> &mat, const bool wrap = true) {

    up<mat_t<up<std::vector<coord_t>>>> neighbors(new mat_t<up<std::vector<coord_t>>>());

    for (size_t r = 0; r < HEIGHT; r++) {
    for (size_t c = 0; c < WIDTH; c++) {
        (*neighbors)[r][c] = valid_neighbors(r, c, HEIGHT, WIDTH, CLOSEST8);
    }
    }

    bool sparse = false;
    while (!sparse) {

        sparse = true;
        for (size_t r = 0; r < HEIGHT; r++) {
        for (size_t c = 0; c < WIDTH; c++) {

            if ((*neighbors)[r][c]->size() == 0 || mat[r][c] == 0) {

              continue;

            } else {

              sparse = false;
              size_t n = rand() % (*neighbors)[r][c]->size();
              coord_t etch_at = (*(*neighbors)[r][c])[n];
              mat[etch_at.first][etch_at.second] = 0;
              (*neighbors)[r][c]->erase((*neighbors)[r][c]->begin() + n);
            }
        }
        }
    }
}


std::ofstream &print_mat(const mat_t<int_fast8_t> &mat, std::ofstream &ofs) {

    for (auto row : mat) {
        for (int_fast8_t x : row) {
            ofs << std::to_string(x) << " ";
        }
        ofs << '\n';
    }

    return ofs;
}   


std::ifstream &load_mat(mat_t<int_fast8_t> &mat, std::ifstream &ifs) {

    for (size_t r = 0; r < HEIGHT; r++) {
    for (size_t c = 0; c < WIDTH; c++) {

        try {

            std::string x;
            ifs >> x;
            mat[r][c] = std::stoi(x);

        } catch (const std::ifstream::failure &exc) {

            std::cerr << "Failed reading the file! Aborting...\n";
            exit(1);
        }
    }
    }

    return ifs;
}


double anneal_step(mat_t<int_fast8_t> &mat, const double T,
                   const mat_t<up<std::vector<coord_t>>> &moves,
                   const bool wrap = true) {

    double V_total = 0;
    int32_t count = 0;

    up<mat_t<double>> V(new mat_t<double>());

    for (size_t r = 0; r < HEIGHT; r++) {
    for (size_t c = 0; c < WIDTH; c++) {

        (*V)[r][c] = potential(mat, r, c);

        if (mat[r][c] != 0) {
            V_total += (*V)[r][c];
            count++;
        }
    }
    }

    for (size_t r = 0; r < HEIGHT; r++) {
    for (size_t c = 0; c < WIDTH; c++) {

        if (mat[r][c] == 0) {
            continue;
        }

        coord_t move((*moves[r][c])[rand() % (*moves[r][c]).size()]);
        double V_diff = (*V)[move.first][move.second] - (*V)[r][c];

        if (accept(V_diff, T) && mat[move.first][move.second] == 0) {
            mat[move.first][move.second] = mat[r][c];
            mat[r][c] = 0;
        }
    }
    }

    return V_total / count;
}


int main(int argc, char *argv[]) {

    std::ofstream ofs;
    std::ostringstream name("", std::ios_base::ate);

    uint32_t step_offset = 0;

    up<mat_t<int_fast8_t>> mat(new mat_t<int_fast8_t>());
    for (size_t r = 0; r < HEIGHT; r++) {
    for (size_t c = 0; c < WIDTH; c++) {
        (*mat)[r][c] = 1;
    }
    }

    up<mat_t<up<std::vector<coord_t>>>> MOVES(new mat_t<up<std::vector<coord_t>>>());
    for (size_t r = 0; r < HEIGHT; r++) {
    for (size_t c = 0; c < WIDTH; c++) {
        (*MOVES)[r][c] = valid_neighbors(r, c, HEIGHT, WIDTH, CLOSEST8, WRAPPED);
    }
    }

    if (argc == 3) {

        std::ifstream ifs;

        std::string filename(argv[1]);
        std::cout << "Loading " << filename << '\n';

        ifs.open(filename);
        if (!ifs.is_open()) {
            std::cerr << "Failed reading the file! Aborting...\n";
            exit(1);
        }

        load_mat(*mat, ifs);
        ifs.close();
        std::cout << "Initial condition loaded.\n";

        step_offset = std::stoi(argv[2]);

    } else {

        std::cout << "Etching the initial condition\n";
        etch(*mat, WRAPPED);
    }

    std::cout << "Annealing...\n";
    double V_avg = 0;

    for (uint32_t step = step_offset;
         step <= MAX_STEPS + step_offset;
         step++) { 
        
        if (step % 10000 == 0) {

            name.str("./output/");
            name << std::to_string(step) << ' ' << std::to_string(V_avg) << ".dat";
            ofs.open(name.str());

            if (ofs.fail()) {
                std::cout << "Failed to open a file at step "
                          << std::to_string(step) << '\n';
            } else {
                print_mat(*mat, ofs).close();
            }
        }
        
        double T_factor = (step + 1.0)/1500000 - 1;
        double T = 4*T_factor*T_factor;
        V_avg = anneal_step(*mat, T, *MOVES, WRAPPED);
        std::cout << "step " << std::to_string(step) << '\n';
    }

    return 0;
}

