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

        if (mode == "file") {
            if (argc == 5) {
                Manager manager(problem, algorithm, argv[4]);                   // bez output file
                //manager.sortArray();
            } else {
                Manager manager(problem, algorithm, argv[4], argv[5]); //  output file
                //manager.
            }
        } else if (mode == "test") {
            int size = std::stoi(argv[4]);
            int density = std::stoi(argv[5]);
            int count = std::stoi(argv[6]);
            Manager manager(problem, algorithm, size, density, count, argv[7]);
            //manager.
        } else {
            help();
        }
    return 0;
    }