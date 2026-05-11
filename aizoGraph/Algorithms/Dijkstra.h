#pragma once

#include "Graph.h"
#include <iostream>
#include <climits>
#include <string>

class Dijkstra {
public:
    explicit Dijkstra(const Graph* graph, int src, int dst)
        : incidenceMatrix(graph->getIncidenceMatrix()),
          successorList(graph->getSuccessorList()),
          vertexNumber(graph->getVertexes()),
          edgeNumber(graph->getEdges()),
          source(src),
          destination(dst)
    {
        distance = new int[vertexNumber];
        visited = new bool[vertexNumber];
        predecessor = new int[vertexNumber];
    }

    ~Dijkstra() {
        delete[] distance;
        delete[] visited;
        delete[] predecessor;
    }

    void pathIncidenceMatrix() {
        for (int i = 0; i < vertexNumber; i++) {
            distance[i] = INT_MAX;
            visited[i] = false;
            predecessor[i] = -1;
        }
        distance[source] = 0;

        for (int c = 0; c < vertexNumber - 1; c++) {
            int u = minDistance();
            if (u == -1) break;
            visited[u] = true;

            for (int j = 0; j < edgeNumber; j++) {
                if (incidenceMatrix[u][j] > 0) {
                    int weight = incidenceMatrix[u][j];
                    int v = -1;

                    for (int i = 0; i < vertexNumber; i++) {
                        if (incidenceMatrix[i][j] < 0) {
                            v = i;
                            break;
                        }
                    }

                    if (v != -1 && !visited[v] && distance[u] != INT_MAX &&
                        distance[u] + weight < distance[v]) {
                        distance[v] = distance[u] + weight;
                        predecessor[v] = u;
                    }
                }
            }
        }
    }

    void pathSuccessorList() {
        for (int i = 0; i < vertexNumber; i++) {
            distance[i] = INT_MAX;
            visited[i] = false;
            predecessor[i] = -1;
        }
        distance[source] = 0;

        for (int c = 0; c < vertexNumber - 1; c++) {
            int u = minDistance();
            if (u == -1) break;
            visited[u] = true;

            LinkedList::Node* current = successorList[u].getHead();
            while (current) {
                int v = current->data.vertex;
                int weight = current->data.weight;

                if (!visited[v] && distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    predecessor[v] = u;
                }
                current = current->next;
            }
        }
    }

    void print() const {
        for (int i = 0; i < vertexNumber; i++) {
            std::cout << source << " -> " << i << " : ";
            if (distance[i] == INT_MAX) {
                std::cout << "unreachable" << std::endl;
            } else {
                std::cout << distance[i] << std::endl;
            }
        }
        std::cout << std::endl;
    }

    void printPath() const {
        if (distance[destination] == INT_MAX) {
            std::cout << "No path found from " << source << " to " << destination << "." << std::endl;
            return;
        }
        printPathRec(destination);
        std::cout << std::endl;
    }

    std::string getPathString() const {
        if (distance[destination] == INT_MAX) return "No path found.";

        std::string path;
        buildPathString(destination, path);
        return path;
    }

private:
    int minDistance() const {
        int min = INT_MAX;
        int min_index = -1;

        for (int i = 0; i < vertexNumber; i++) {
            if (!visited[i] && distance[i] <= min) {
                min = distance[i];
                min_index = i;
            }
        }

        return min_index;
    }

    void printPathRec(int current) const {
        if (current == source) {
            std::cout << source;
            return;
        }
        if (predecessor[current] == -1) {
            std::cout << "[path broken]";
            return;
        }
        printPathRec(predecessor[current]);
        std::cout << " -> " << current;
    }

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

        int u = predecessor[current];
        int v = current;
        int weight = 0;
        for (int e = 0; e < edgeNumber; e++) {
            if (incidenceMatrix[u][e] > 0 && incidenceMatrix[v][e] < 0) {
                weight = incidenceMatrix[u][e];
                break;
            }
        }

        path += " -(" + std::to_string(weight) + ")-> " + std::to_string(current);
    }


    int** incidenceMatrix;
    LinkedList* successorList;

    int* distance;
    bool* visited;
    int* predecessor;

    int vertexNumber, edgeNumber, source, destination;
};
