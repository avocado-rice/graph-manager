#include <fstream>
#include <iostream>

#include "Control/Manager.h"

using namespace std;

void help() {
    cout << "file mode: \n --file ./aizoGraph  mode  problem  algorithm  input_file  [output_file]\ntest  mode: \n --test ./aizoGraph  mode  problem  algorithm  size  density  count  output_file\n //////" << endl;
}

int main(int argc, const char** argv) {
    if (argc < 5) {
        help();
        return 1;
    }

    string mode = argv[1];
    int problem = atoi(argv[2]);
    int algorithm = atoi(argv[3]);

    auto run = [&](auto type) {
        using T = decltype(type);

        if (mode=="file") {
            if (argc == 5) {
                Manager<T> manager(problem, algorithm, argv[4]);          // bez output fild
                manager.sortArray();
            } else {
                Manager<T> manager(problem, algorithm, argv[4], argv[5]); // podany output file
                manager.sortArray();
            }
        } else if (mode=="test") {
            int size = std::stoi(argv[4]);
            int density = std::stoi(argv[5]);
            int count = std::stoi(argv[6]);
            Manager<T> manager(problem, algorithm, size, density, count, argv[7]);
            manager.sortArray();
        } else {
            help();
        }
    };

    switch (dataType) {
        case 1: run(int{}); break;
        case 2: run(float{}); break;
        case 3: run(double{}); break;
        default: throw std::invalid_argument("Invalid data type. ");
    } // ??????

    return 0;
}