#pragma once

#include "LinkedList.h"
#include "Graph.h"

class Prim {
public:
    explicit Prim(const Graph* graph) {
        incidenceMatrix = graph->getIncidenceMatrix();
        successorList = graph->getSuccessorList();
        vertexNumber = graph->getVertexes();
        edgeNumber = graph->getEdges();

        mstResult = 0;

        visited = new bool[vertexNumber];
        key = new int[vertexNumber];
        parent = new int[vertexNumber];

        for (int i = 0; i < vertexNumber; i++) {
            visited[i] = false;
            key[i] = 100000;
            parent[i] = -1;
        }
    }

    ~Prim() {
        delete[] visited;
        delete[] key;
        delete[] parent;
    }

    void mstIncidenceMatrix() {
        key[0] = 0;

        for (int count = 0; count < vertexNumber; count++) {
            int n = extractMin(key, visited, vertexNumber);
            if (n == -1) break;
            visited[n] = true;

            for (int e = 0; e < edgeNumber; e++) {
                if (incidenceMatrix[n][e] != 0) {
                    int weight = std::abs(incidenceMatrix[n][e]);
                    int v = -1;

                    for (int vertex = 0; vertex < vertexNumber; vertex++) {
                        if (vertex != n && incidenceMatrix[vertex][e] != 0) {
                            v = vertex;
                            break;
                        }
                    }

                    if (v != -1 && !visited[v] && weight < key[v]) {
                        key[v] = weight;
                        parent[v] = n;
                    }
                }
            }
        }
    }

    void mstSuccessorList() {
        key[0] = 0;

        for (int count = 0; count < vertexNumber; count++) {
            int n = extractMin(key, visited, vertexNumber);
            if (n == -1) break;
            visited[n] = true;

            LinkedList::Node* current = successorList[n].getHead();
            while (current != nullptr) {
                int v = current->data.vertex;
                int weight = current->data.weight;

                if (!visited[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = n;
                }
                current = current->next;
            }
        }
    }

    static int extractMin(const int* key, const bool* visited, int n) {
        int min = 100000;
        int minIndex = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && key[i] < min) {
                min = key[i];
                minIndex = i;
            }
        }
        return minIndex;
    }

    void updateMST() {
        for (int i = 1; i < vertexNumber; i++) {
            if (parent[i] != -1) {
                std::cout << "( " << parent[i] << ", " << i << " ) : " << key[i] << std::endl;
                mstResult += key[i];
            }
        }

        std::cout << "TOTAL MST: " << mstResult << std::endl << std::endl;
    }

    std::string getMSTstring() const {
        std::string s;
        s = std::to_string(mstResult);
        s = "MST: " + s;
        return s;
    }

private:
    int** incidenceMatrix;
    LinkedList* successorList;

    bool* visited;
    int* key;
    int* parent;

    int vertexNumber, edgeNumber, mstResult;
};
