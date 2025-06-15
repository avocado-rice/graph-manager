#pragma once

#include <random>
#include <string>

#include "Structures/Graph.h"
#include "FileHandler.h"
#include "Timer/Timer.h"

class Manager {
public:
    //file mode
    Manager(int p, int a, const std::string& iF, const std::string& oF) {
        problem = p;
        algorithm = a;
        inputFile = iF;
        outputFile = oF;

        loadFromFile();
    }

    Manager(int p, int a, const std::string& iF) {
        problem = p;
        algorithm = a;
        inputFile = iF;

        loadFromFile();
    }

    //test mode
    Manager(int p, int a, int s, int d, int c, const std::string& oF) {
        problem = p;
        algorithm = a;
        size = s;
        density = d;
        count = c;
        outputFile = oF;

        generateGraph();
    }

    void generateGraph(){
        int edges = density * (size * (size - 1)) / 2;
        dataGraph = Graph(size, edges);

        bool* visited = new bool[size]{false};
        dfs(size - 1, visited, size, dataGraph);

        int residue = edges - size - 1;
        for (int i = 0; i < residue; i++) {
            int a = randomNumber(residue);
            int b = randomNumber(residue);

            while (a = b) {
                b = randomNumber(residue);
            }

            if (dataGraph.getSuccessorList().)
        }
    }

private:
    void dfs(int current, bool* visited, int n, Graph& graph) {
        visited[current] = true;
        int c = 0;

        int* neighbors = new int[size];
        for (int i = 0; i < size; i++) {
            if (!visited[i]) {
                neighbors[c++] = i;
            }
        }

        shuffle(neighbors, size);

        for (int i = 0; i < count; ++i) {
            int neighbor = neighbors[i];
            if (!visited[neighbor]) {
                graph.addEdge(current, neighbor, randomNumber(INT_MAX));
                 dfs(neighbor, visited, n, graph);
            }
        }

        delete[] neighbors;
    }

    void swap(int& a, int& b) {         //zamianka dwoch pozycji w tablicy
        int temp = a;
        a = b;
        b = temp;
    }

    int randomNumber(int upperRange) {
        std::mt19937 rand(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, upperRange);
        return dist(rand);
    }

    void shuffle(int* array, int size) {

        for (int i = size - 1; i > 0; i--) {
            int j = randomNumber(i);
            swap(array[i], array[j]);
        }
    }

    void loadFromFile() {

    }

    int problem;
    int algorithm;
    double density;
    int count;
    int size = 0;

    std::string inputFile;
    std::string outputFile;

    Graph dataGraph;
    FileHandler fileHandler;
};