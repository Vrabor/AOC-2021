#include <iostream>
#include <fstream>
#include <string>
#include <array>

#define N 10

typedef std::array<std::array<char, N>, N> grid_t;
typedef std::array<std::array<bool, N>, N> ind_t;

void flash(grid_t& grid, int x, int y) {
    const int size = N - 1;
    //corners
    if (x > 0 && y > 0){
        grid[x - 1][y - 1]++;
    }
    if (x < size && y < size){
        grid[x + 1][y + 1]++;
    }
    if (x > 0 && y < size){
        grid[x - 1][y + 1]++;
    }
    if (x < size && y > 0){
        grid[x + 1][y - 1]++;
    }

    // edges
    if (x > 0){
        grid[x - 1][y]++;
    }
    if (y > 0){
        grid[x][y - 1]++;
    }
    if (x < size){
        grid[x + 1][y]++;
    }
    if (y < size){
        grid[x][y + 1]++;
    }
}

std::size_t step(grid_t& grid) {
    ind_t ind { false };
    std::size_t flashes { 0 };

    // first increase every cell by 1
    for (auto& x : grid){
        for (auto& y : x){
            y++;
        }
    }

    bool changes = true;
    while (changes){
        changes = false;
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                if (grid[i][j] > 9 && !ind[i][j]){
                    flash(grid, i, j);
                    ind[i][j] = true;
                    changes = true;
                    flashes++;
                }
                
            }
        }
    }

    for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                // if flashed reset energy
                if (ind[i][j]){
                    grid[i][j] = 0;
                }
            }
        }

    return flashes;
}

void print_grid(grid_t& grid){
    for (auto& x : grid){
            for (auto& y : x){
                std::cout << (int)y;
            }
            std::cout << '\n';
        }
    std::cout << '\n';
}

std::size_t solution1(grid_t grid, int iterations) {
    std::size_t flashes { 0 };
    for (int i = 1; i <= iterations; i++){
        flashes += step(grid);
    }

    return flashes;
}

std::size_t solution2(grid_t grid) {
    // 1 indexed
    for(std::size_t iteration{ 1 }; ; iteration++){
        // all flashed means N*N flashes
        if (step(grid) == N*N){
            return iteration;
        }
    }
}

int main() {
    const std::string filename = "./input.txt";
    std::ifstream in(filename, std::ios::in);

    grid_t grid { 0 };
    std::string buff {};
    int line = 0;
    while (std::getline(in, buff)){
        for (auto i = 0; i < N; i++){
            grid[line][i] = buff[i] - '0';
        }
        line++;
    }

    std::cout << "Solution1: " << solution1(grid, 100) << "\n";
    std::cout << "Solution2: " << solution2(grid) << "\n";

    return 0;
}