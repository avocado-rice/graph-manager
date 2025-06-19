#pragma once
#include "LinkedList.h"

class Graph {
public:
    // destruktor

    ~Graph() {
        for (int i = 0; i < vertexes; ++i) {
            delete[] incidenceMatrix[i];
        }

        delete[] incidenceMatrix;
        delete[] successorList;
    }

    // konstruktory

    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;


    Graph(int v, int e) {
        edges = e;
        vertexes = v;
        incidenceMatrix = new int*[vertexes];
        for (int i = 0; i < vertexes; i++) {
            incidenceMatrix[i] = new int[edges]{0};
        }

        successorList = new LinkedList[vertexes];
    }

    // dodanie krawedzi do grafu (macierz incydencji + lista nastepnikow)

    void addEdge(int startVertex, int endVertex, int weight) {
        if (startVertex < 0 || startVertex >= vertexes) {
            std::cerr << "Error: startVertex out of range\n";
            return;
        }
        if (endVertex < 0 || endVertex >= vertexes) {
            std::cerr << "Error: endVertex out of range\n";
            return;
        }
        if (currentEdgeIndex < 0 || currentEdgeIndex >= edges) {
            std::cerr << "Error: currentEdgeIndex out of range\n";
            return;
        }

        incidenceMatrix[startVertex][currentEdgeIndex] = weight;
        incidenceMatrix[endVertex][currentEdgeIndex] = -weight;
        std::cout << '1';
        successorList[startVertex].append(endVertex, weight);
        std::cout << '2';
        currentEdgeIndex++;
    }

    // gettery

    int getEdges() const {
        return edges;
    }

    int getVertexes() const {
        return vertexes;
    }

    LinkedList * getSuccessorList() const {
        return successorList;
    }

    // sprawdzanie czy krawedz miedzy dwoma wiercholkami istnieje

    bool edgeExists(int start, int end) {
        return successorList[start].contains(end);
    }

    void printIncidence() {
        for (int i = 0; i < vertexes; ++i) {
            std::cout << "VERTEX " <<  i << ": " << std::endl;
            successorList[i].printList();
        }
    }

private:
    // zmienne
    int edges, vertexes;
    int currentEdgeIndex = 0;
    int** incidenceMatrix = nullptr;
    LinkedList* successorList = nullptr;
};