#pragma once

#include <random>
#include <string>

#include "C:\\Users\\KatarzynaNowomiejska\\Desktop\\aizo_dwa\\aizoGraph\\Structures\\Graph.h"
#include "FileHandler.h"
#include "C:\\Users\\KatarzynaNowomiejska\\Desktop\\aizo_dwa\\aizoGraph\\Timer\\Timer.h"

class Manager {
public:
    // file mode z plikiem wyjsciowym
    Manager(int p, int a, const std::string& iF, const std::string& oF)
        : problem(p), algorithm(a), inputFile(iF), outputFile(oF), dataGraph(nullptr)
    {
        loadFromFile();
    }

    // file mode bez podanego wyjscia
    Manager(int p, int a, const std::string& iF)
        : problem(p), algorithm(a), inputFile(iF), dataGraph(nullptr)
    {
        loadFromFile();
        dataGraph->printIncidence();
    }

    // tryb benchmarkowy z generowaniem
    Manager(int p, int a, int s, double d, int c, const std::string& oF)
        : problem(p), algorithm(a), size(s), density(d), count(c), outputFile(oF), dataGraph(nullptr)
    {
        generateGraph();
        dataGraph->printIncidence();
    }

    ~Manager() {
    }

    Graph* getGraph() {
        return dataGraph;
    }

    int getSize() const {
        return size;
    }

private:
    void generateGraph() {
        int edges = static_cast<int>(density * (size * (size - 1)));
        dataGraph = new Graph(size, edges);

        bool* visited = new bool[size]{false};
        dfs(size - 1, visited, *dataGraph);

        int residue = edges - (size - 1);
        int added = 0;

        while (added < residue) {
            int a = randomNumber(size - 1);
            int b = randomNumber(size - 1);
            while (a == b) b = randomNumber(size - 1); // nie chcemy pętli

            if (!dataGraph->edgeExists(a, b)) {
                dataGraph->addEdge(a, b, randomNumber(100000));
                added++;
            }
        }


        delete[] visited;
    }

    void dfs(int current, bool* visited, Graph& graph) {
        visited[current] = true;
        int c = 0;

        int* neighbors = new int[size];
        for (int i = 0; i < size; i++) {
            if (!visited[i]) {
                neighbors[c++] = i;
            }
        }

        shuffle(neighbors, c);

        for (int i = 0; i < c; ++i) {
            int neighbor = neighbors[i];
            if (!visited[neighbor]) {
                graph.addEdge(current, neighbor, randomNumber(INT_MAX));
                dfs(neighbor, visited, graph);
            }
        }

        delete[] neighbors;
    }

    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

    int randomNumber(int upperRange) {
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
        fileHandler.readFile(inputFile);
        dataGraph = fileHandler.getGraph();  // wskazujemy bez kopiowania
        size = fileHandler.getSize();
    }

    int problem = 0;
    int algorithm = 0;
    double density = 0;
    int count = 0;
    int size = 0;

    std::string inputFile;
    std::string outputFile;

    std::mt19937 rand{ std::random_device{}() };

    Graph* dataGraph;      // wskaźnik na aktualny graf
    FileHandler fileHandler;
};
