#pragma once
#include <limits.h>
#include <../Graph.h>

class Prim {
public:
    Prim(Graph g) {
        graph = g;
        vertexNumber = g.getVertexes();
        visited = new bool[vertexNumber];
        key = new int[vertexNumber];
        parent = new int[vertexNumber];

        for (int i = 0; i < vertexNumber; i++) {
            visited[i] = false;
            key[i] = INT_MAX;
            parent[i] = -1;
        }
    }

    void calculateMST() {
        key[0] = 0;

        for (int i = 0; i < vertexNumber; i++) {
            int m = extractMin(key, visited, vertexNumber);
            visited[m] = true;

            LinkedList::Node* currentNode = graph.getSuccessorList(m);
            while (currentNode != nullptr) {
                int v = currentNode -> data.vertex;
                int weight = currentNode -> data.weight;

                if (!visited[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = m;
                }

                currentNode = currentNode -> next;
            }
        }
    }

private:
    Graph graph;
    int vertexNumber;
    bool* visited;
    int* key;
    int* parent;

    int extractMin(int* key, bool* visited, int vertexNumber) {
        int min = 2147483647;
        int minIndex = -1;

        for (int i = 0; i < vertexNumber; i++) {
            if (!visited[i] && key[i] < min) {
                min = key[i];
                minIndex = i;
            }
        }
        return minIndex;
    }
};
