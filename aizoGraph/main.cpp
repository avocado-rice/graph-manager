#include <fstream>
#include <iostream>

#include "Manager.h"

using namespace std;

void help() {
    cout << "file mode: \n ./aizoGraph  file  problem  algorithm  input_file  [output_file] source destination\n\ntest  mode: \n ./aizoGraph  test  problem  algorithm  size  density  count  output_file\n\nproblem: 0. MST 1. Shortest Path\n\nalgorithm: \n (problem 0) 0. Prim 1. Kruskal\n (problem 1) 0. Dijkstry 1. Bellman-Ford \n\nprovide source and destination if using shortest path\n\neg.\n./aizoGraph file 1 1 \"input.txt\" \"output.txt\" 1 2\nis equal to \nRun shortest path problem using Bellman-Ford (path from vertex 1 to vertex 2) on file input.txt, save results in output.txt" << endl;
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
if(problem == 1){
    if (argc == 7) {
        int src = atoi(argv[5]);
        int dst = atoi(argv[6]);
        Manager manager(problem, algorithm, argv[4], src, dst);                   // bez output file
        manager.runAppropriate();
    } else if (argc == 8) {
        int src = atoi(argv[6]);
        int dst = atoi(argv[7]);
        Manager manager(problem, algorithm, argv[4], argv[5], src, dst); //  output file
        manager.runAppropriate();
    } else {
        help();
    }
} else if (problem == 0) {
    if (argc == 5) {
        Manager manager(problem, algorithm, argv[4]);                   // bez output file
        manager.runAppropriate();
    } else if (argc == 6) {
        Manager manager(problem, algorithm, argv[4], argv[5]); //  output file
        manager.runAppropriate();
    } else {
        help();
    }
}
        } else if (mode == "test") {
            int size = std::stoi(argv[4]);
            double density = std::stod(argv[5]);
            int count = std::stoi(argv[6]);

            for (int i = 0; i < count; i++) {
                Manager manager(problem, algorithm, size, density, argv[7]);
                manager.runAppropriate();
            }

        } else {
            help();
        }
    return 0;
    }