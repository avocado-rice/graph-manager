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
        incidenceMatrix[startVertex][currentEdgeIndex] = weight;
        incidenceMatrix[endVertex][currentEdgeIndex] = -weight;
        successorList[startVertex].append(endVertex, weight);
        currentEdgeIndex++;
    }

    void addEdgeNotDirected(int startVertex, int endVertex, int weight) {
        incidenceMatrix[startVertex][currentEdgeIndex] = weight;
        incidenceMatrix[endVertex][currentEdgeIndex] = weight;
        successorList[startVertex].append(endVertex, weight);
        successorList[endVertex].append(startVertex, weight);
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