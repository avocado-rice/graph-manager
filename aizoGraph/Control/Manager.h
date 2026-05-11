#pragma once

#include <random>
#include <string>
#include <utility>

#include "Graph.h"
#include "FileHandler.h"
#include "Timer.h"
#include "Prim.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include "BellmanFord.h"

class Manager {
public:
    Manager(int p, int a, std::string  iF, const std::string& oF, int src, int dst)
        : problem(p), algorithm(a), inputFile(std::move(iF)), outputFile(oF), dataGraph(nullptr), source(src), destination(dst)
    {
        file = true;
        loadFromFile();
    }


    Manager(int p, int a, const std::string& iF, int src, int dst)
        : problem(p), algorithm(a), inputFile(iF), dataGraph(nullptr), source(src), destination(dst)
    {
        file = true;
        loadFromFile();
    }

    Manager(int p, int a, const std::string& iF, const std::string& oF)
        : problem(p), algorithm(a), inputFile(iF), outputFile(oF), dataGraph(nullptr)
    {
        file = true;
        loadFromFile();
    }


    Manager(int p, int a, const std::string& iF)
        : problem(p), algorithm(a), inputFile(iF), dataGraph(nullptr)
    {
        file = true;
        loadFromFile();
    }

    // benchmark mode with graph generation
    Manager(int p, int a, int s, double d, const std::string& oF)
        : problem(p), algorithm(a), size(s), density(d), outputFile(oF), dataGraph(nullptr)
    {
        generateGraph();
    }

    void runAppropriate() {
        switch (problem) {
            case 0:
                algorithm == 0 ? runPrim() : runKruskal();
                break;
            case 1:
                algorithm == 0 ? runDijkstra() : runBellmanFord();
                break;
            default: throw std::runtime_error("Something went wrong with running. ");
        }
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
    void runPrim() {
        Prim primekI(dataGraph);
        Timer zegarunio1;
        primekI.mstIncidenceMatrix();
        zegarunio1.stop();
        std::cout  << "Run on Incidence Matrix:" << std::endl;
        primekI.updateMST();

        Prim primekS(dataGraph);
        Timer zegarunio2;
        primekS.mstSuccessorList();
        zegarunio2.stop();
        std::cout  << "Run on Successor List:" << std::endl;
        primekS.updateMST();

        if (file && !outputFile.empty()) {
            fileHandler.writeFileDone(primekS.getMSTstring(), outputFile);
        } else {
            fileHandler.writeFileResults(problem, algorithm, size, density, outputFile, zegarunio1.result(), zegarunio2.result());
        }
    }

    void runKruskal() {
        Kruskal krusekI(dataGraph);
        Timer zegarunio1;
        krusekI.mstIncidenceMatrix();
        zegarunio1.stop();
        std::cout  << "Run on Incidence Matrix:" << std::endl;
        krusekI.print();

        Kruskal krusekS(dataGraph);
        Timer zegarunio2;
        krusekS.mstSuccessorList();
        zegarunio2.stop();
        std::cout  << "Run on Successor List:" << std::endl;
        krusekS.print();

        if (file && !outputFile.empty()) {
            fileHandler.writeFileDone(krusekS.getMSTstring(), outputFile);
        } else {
            fileHandler.writeFileResults(problem, algorithm, size, density, outputFile, zegarunio1.result(), zegarunio2.result());
        }
    }

    void runDijkstra() {
        Dijkstra dijkstronI(dataGraph, source, destination);
        Timer zegarunio1;
        dijkstronI.pathIncidenceMatrix();
        zegarunio1.stop();
        dijkstronI.printPath();

        Dijkstra dijkstronS(dataGraph, source,destination);
        Timer zegarunio2;
        dijkstronS.pathSuccessorList();
        zegarunio2.stop();
        dijkstronS.print();

        if (file && !outputFile.empty()) {
            fileHandler.writeFileDone(dijkstronS.getPathString(), outputFile);
        } else {
            fileHandler.writeFileResults(problem, algorithm, size, density, outputFile, zegarunio1.result(), zegarunio2.result());
        }
    }

    void runBellmanFord() {
        BellmanFord bellmanI(dataGraph, source, destination);
        Timer zegarunio1;
        bellmanI.pathIncidenceMatrix(source, destination);
        zegarunio1.stop();

        BellmanFord bellmanS(dataGraph, source, destination);
        Timer zegarunio2;
        bellmanS.pathSuccessorList(source, destination);
        zegarunio2.stop();

        if (file && !outputFile.empty()) {
            fileHandler.writeFileDone(bellmanS.getPathString(), outputFile);
        } else {
            fileHandler.writeFileResults(problem, algorithm, size, density, outputFile, zegarunio1.result(), zegarunio2.result());
        }
    }

    void generateGraph() {
        int edges;
        directed = isDirected(problem);

        if (!directed) {
            edges = static_cast<int>(density * (size * (size - 1)) / 2);
        } else {
            edges = static_cast<int>(density * (size * (size - 1)));
        }

        dataGraph = new Graph(size, edges);

        bool* visited = new bool[size]{false};
        dfs(size - 1, visited, *dataGraph);

        int residue = edges - (size - 1);
        int added = 0;

        while (added < residue) {
            int a = randomNumber(size - 1);
            int b = randomNumber(size - 1);
            while (a == b) b = randomNumber(size - 1);

            if (directed) {
                if (!dataGraph->edgeExists(a, b)) {
                    dataGraph->addEdge(a, b, randomNumber(100000));
                    added++;
                }
            } else {
                if (!dataGraph->edgeExists(a, b) && !dataGraph->edgeExists(b, a)) {
                    dataGraph->addEdgeNotDirected(a, b, randomNumber(100000));
                    added++;
                }
            }
        }

        delete[] visited;
    }

    void dfs(int current, bool* visited, Graph& graph) {
        visited[current] = true;

        int* neighbors = new int[size];
        int c = 0;

        for (int i = 0; i < size; i++) {
            if (!visited[i]) {
                neighbors[c++] = i;
            }
        }

        shuffle(neighbors, c);

        for (int i = 0; i < c; i++) {
            int neighbor = neighbors[i];
            if (!visited[neighbor]) {
                if (directed) {
                    graph.addEdge(current, neighbor, randomNumber(100000));
                } else {
                    graph.addEdgeNotDirected(neighbor, current, randomNumber(100000));
                }
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

    bool isDirected(int decision) {
        if (decision == 1) {
            return true;
        }
        return false;
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
        bool dir = false;
        if (problem == 1) {
            dir = true;
        }

        fileHandler.readFile(inputFile, dir);
        dataGraph = fileHandler.getGraph();
        size = fileHandler.getSize();
    }

    int problem;
    int algorithm;
    double density;
    int count;
    int size;
    int source, destination;
    bool directed = false;
    bool file = false;

    std::string inputFile;
    std::string outputFile = "";

    std::mt19937 rand{ std::random_device{}() };

    Graph* dataGraph;
    FileHandler fileHandler;
};
