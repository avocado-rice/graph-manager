#pragma once
#include "LinkedList.h"

class Graph {
public:
    ~Graph() {
        for (int i = 0; i < vertexes; ++i) {
            delete[] incidenceMatrix[i];
        }

        delete[] incidenceMatrix;

        delete[] successorList;
    }

    Graph(int v, int e) {
        edges = e;
        vertexes = v;
        incidenceMatrix = new int*[vertexes];
        for (int i = 0; i < vertexes; i++) {
            incidenceMatrix[i] = new int[edges]{0};
        }

        successorList = new LinkedList[vertexes];
    }

    void addEdge(int startVertex, int endVertex, int edgeIndex, int weight) {
        incidenceMatrix[startVertex][edgeIndex] = weight;
        incidenceMatrix[endVertex][edgeIndex] = -weight;

        successorList[startVertex].append(endVertex, weight);
    }

    [[nodiscard]] int getEdges() const {
        return edges;
    }

    [[nodiscard]] int getVertexes() const {
        return vertexes;
    }

    [[nodiscard]] LinkedList * getSuccessorList() const {
        return successorList;
    }

private:
    int edges, vertexes;
    int** incidenceMatrix = nullptr;
    LinkedList* successorList = nullptr;
};