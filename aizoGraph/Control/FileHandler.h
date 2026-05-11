#pragma once
#include <stdexcept>
#include <string>
#include <sstream>
#include <fstream>
#include "Graph.h"

class FileHandler {
public:
    FileHandler() : graph(nullptr) {}

    ~FileHandler() {
        delete graph;
    }

    void readFile(const std::string& filename, bool directed) {
        if (filename.empty()) {
            throw std::invalid_argument("No filename given.");
        }

        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file.");
        }

        std::string line;
        getline(file, line);

        std::istringstream headerStream(line);
        int edgeNumber, vertexNumber;

        if (!(headerStream >> edgeNumber >> vertexNumber)) {
            throw std::runtime_error("Invalid format.");
        }

        delete graph;
        graph = new Graph(vertexNumber, edgeNumber);

        for (int i = 0; i < edgeNumber; i++) {
            if (!getline(file, line)) {
                throw std::runtime_error("Not enough edge data.");
            }

            std::istringstream edgeStream(line);
            int v1, v2, weight;
            if (!(edgeStream >> v1 >> v2 >> weight)) {
                throw std::runtime_error("Invalid edge format.");
            }

            if (!directed) {
                graph->addEdgeNotDirected(v1, v2, weight);
            } else {
                graph->addEdge(v1, v2, weight);
            }
        }
    }

    // benchmark mode: write to file
    void writeFileResults(int p, int a, int s, double d, std::string oF, int t1, int t2) {
        std::ofstream file(oF, std::ios::app);

        file << p << " " << a << " " << s << " " << d << " " << t1 << " " << t2 << "\n";
        file.close();
    }

    // file mode: write to file
    void writeFileDone(std::string done, std::string oF) {
        std::cout << "Saving results to file... ";
        std::ofstream file(oF);
        file << done;
        file.close();
    }

    Graph* getGraph() const {
        return graph;
    }

    int getSize() const {
        return graph ? graph->getVertexes() : 0;
    }

private:
    Graph* graph;
};
