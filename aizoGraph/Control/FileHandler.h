#pragma once
#include <stdexcept>
#include <string>
#include <sstream>
#include <fstream>
#include "C:\Users\KatarzynaNowomiejska\Desktop\aizo_dwa\aizoGraph\Structures\Graph.h"

class FileHandler {
public:
    FileHandler() : graph(nullptr) {}

    ~FileHandler() {
        delete graph;
    }

    void readFile(const std::string& filename) {
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


            graph->addEdge(v1, v2, weight);
        }
    }

    // Zwraca wskaźnik do grafu (może być nullptr jeśli nie wczytano)
    Graph* getGraph() const {
        return graph;
    }

    // Zwraca liczbę wierzchołków (lub 0 jeśli graf nie istnieje)
    int getSize() const {
        return graph ? graph->getVertexes() : 0;
    }

private:
    Graph* graph;
};
