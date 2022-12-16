#include <iostream>
#include <string>
#include <filesystem>

#include "aoc2022.h"

int main(int argc, char ** argv) {
    static const std::filesystem::path this_dir = std::filesystem::path{__FILE__}.parent_path();

    for (int i = 1; i <= 25; ++i) {
        for (int j = 1; j <= 2; ++j) {
            std::cout << "Day " << i << " part " << j << "\n";
            if (aoc2022::run_solution(i, j, this_dir / "test_inputs" / ("Day" + std::to_string(i) + ".txt"))) {
                std::cerr << "error\n";
                return 1;
            }
            std::cout << "\n";
        }
    }
}
