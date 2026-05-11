#pragma once

#include "Graph.h"
#include <string>
#include <iostream>
#include <climits>

class BellmanFord {
public:
    BellmanFord(const Graph* graph, int src, int dst)
        : incidenceMatrix(graph->getIncidenceMatrix()),
          successorList(graph->getSuccessorList()),
          vertexNumber(graph->getVertexes()),
          edgeNumber(graph->getEdges()),
          source(src), destination(dst)
    {
        predecessor = new int[vertexNumber];
        distance = nullptr;
    }

    ~BellmanFord() {
        if (distance) delete[] distance;
        delete[] predecessor;
    }

    std::string getPathString() const {
        if (!distance || distance[destination] == INT_MAX) return "No path found.";

        int current = destination;
        while (current != source) {
            if (predecessor[current] == -1) return "No path found.";
            current = predecessor[current];
        }

        std::string path;
        buildPathString(destination, path);
        return path;
    }




    void pathIncidenceMatrix(int src, int dst) {
        source = src;
        destination = dst;
        if (distance) delete[] distance;
        distance = new int[vertexNumber];
        for (int i = 0; i < vertexNumber; i++) {
            distance[i] = INT_MAX;
            predecessor[i] = -1;
        }
        distance[source] = 0;

        for (int i = 0; i < vertexNumber - 1; i++) {
            bool updated = false;
            for (int e = 0; e < edgeNumber; e++) {
                int u = -1, v = -1, w = 0;
                for (int k = 0; k < vertexNumber; k++) {
                    if (incidenceMatrix[k][e] > 0) { u = k; w = incidenceMatrix[k][e]; }
                    else if (incidenceMatrix[k][e] < 0) v = k;
                }
                if (u != -1 && v != -1 && distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                    predecessor[v] = u;
                    updated = true;
                }
            }
            if (!updated) break;
        }

        for (int e = 0; e < edgeNumber; e++) {
            int u = -1, v = -1, w = 0;
            for (int k = 0; k < vertexNumber; k++) {
                if (incidenceMatrix[k][e] > 0) { u = k; w = incidenceMatrix[k][e]; }
                else if (incidenceMatrix[k][e] < 0) v = k;
            }
            if (u != -1 && v != -1 && distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                std::cout << "Negative cycle detected.\n";
                return;
            }
        }
    }

    void pathSuccessorList(int src, int dst) {
        source = src;
        destination = dst;
        if (distance) delete[] distance;
        distance = new int[vertexNumber];
        for (int i = 0; i < vertexNumber; i++) {
            distance[i] = INT_MAX;
            predecessor[i] = -1;
        }
        distance[source] = 0;

        for (int i = 0; i < vertexNumber - 1; i++) {
            bool updated = false;
            for (int u = 0; u < vertexNumber; u++) {
                auto* current = successorList[u].getHead();
                while (current) {
                    int v = current->data.vertex, w = current->data.weight;
                    if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                        distance[v] = distance[u] + w;
                        predecessor[v] = u;
                        updated = true;
                    }
                    current = current->next;
                }
            }
            if (!updated) break;
        }

        for (int u = 0; u < vertexNumber; u++) {
            auto* current = successorList[u].getHead();
            while (current) {
                int v = current->data.vertex, w = current->data.weight;
                if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                    std::cout << "Negative cycle detected.\n";
                    return;
                }
                current = current->next;
            }
        }
    }

private:
    void buildPathString(int current, std::string& path) const {
        if (current == source) {
            path = std::to_string(source);
            return;
        }
        if (predecessor[current] == -1) {
            path = "[path broken]";
            return;
        }
        buildPathString(predecessor[current], path);
        int u = predecessor[current], v = current, w = 0;
        for (int e = 0; e < edgeNumber; e++) {
            if (incidenceMatrix[u][e] > 0 && incidenceMatrix[v][e] < 0) {
                w = incidenceMatrix[u][e];
                break;
            }
        }
        path += " -(" + std::to_string(w) + ")-> " + std::to_string(current);
    }

    int** incidenceMatrix;
    LinkedList* successorList;
    int* distance;
    int* predecessor;
    int vertexNumber, edgeNumber, source, destination;
};
