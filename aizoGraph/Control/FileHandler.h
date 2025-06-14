#pragma once
#include <stdexcept>
#include <string>
#include <sstream>
#include <C:\Users\KatarzynaNowomiejska\CLionProjects\aizoGraph\Structures\Graph.h>

class FileHandler {
public:
    ~FileHandler() = default;

    void readFile(const std::string& filename) {
        if (filename.empty()) {
            throw std::invalid_argument("No filename given.");
        }

        std::string line;

        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file.");
        }

        //TODO: sstream

        size_t tabIndex = line.find('\t');
        if (tabIndex == std::string::npos) {
            throw std::runtime_error("Tab wasn't found.");
        }

        getline(file, line);
        try {
            edgeNumber = stoi(line.substr(0, tabIndex));
            vertexNumber = stoi(line.substr(tabIndex + 1));
        } catch (const std::invalid_argument&) {
            throw std::runtime_error("Invalid format.");
        }

        std::istringstream iss(line);

        graph = Graph(edgeNumber, vertexNumber);

        for (int i = 0; i < edgeNumber; i++){
            getline(file, line);
            if (line.empty()) throw std::runtime_error("Not enough data.");
            std::istringstream iss(line);

            if (!(iss >> v1 >> t1 >> v2 >> t2 >> weight) || t1 != '\t' || t2 != '\t') {
                throw std::runtime_error("Invalid edge format.");
            }

            graph.addEdge(v1, v2, i, weight);
        }
    }

    // void writeFileResults(int a, int dt, int s, std::string oF, int time) {
    //     std::ofstream file(oF, std::ios::app);
    //
    //     file << a << " " << dt << " " << s << " " << time << "\n";
    //     file.close();
    // }
    //
    // [[nodiscard]] Graph getGraph() const {
    //     return graph;
    // }

private:
    int edgeNumber, vertexNumber = 0;
    Graph graph;
    int v1, v2, weight;
    char t1, t2;
};
