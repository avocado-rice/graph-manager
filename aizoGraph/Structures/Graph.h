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
        currentEdgeIndex = 0;
        edges = e;
        vertexes = v;
        incidenceMatrix = new int*[vertexes];
        for (int i = 0; i < vertexes; i++) {
            incidenceMatrix[i] = new int[edges]{0};
        }

        successorList = new LinkedList[vertexes];
    }

    void addEdge(int startVertex, int endVertex, int weight) {
        incidenceMatrix[startVertex][currentEdgeIndex] = weight;
        incidenceMatrix[endVertex][currentEdgeIndex] = -weight;

        successorList[startVertex].append(endVertex, weight);
        currentEdgeIndex++;
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
    bool edgeExists(int start, int end) {
        return successorList[start].contains(end);
    }

    int edges, vertexes, currentEdgeIndex;
    int** incidenceMatrix = nullptr;
    LinkedList* successorList = nullptr;
};