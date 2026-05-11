#pragma once

#include "Graph.h"
#include "LinkedList.h"

class Kruskal {
public:
    struct Edge {
        int u, v, weight;
    };

    explicit Kruskal(const Graph* graph) {
        vertexNumber = graph->getVertexes();
        edgeNumber = graph->getEdges();
        incidenceMatrix = graph->getIncidenceMatrix();
        successorList = graph->getSuccessorList();

        parent = new int[vertexNumber];
        rank = new int[vertexNumber];

        mstEdgeNumber = 0;
        mstResult = 0;
    }

    ~Kruskal() {
        delete[] parent;
        delete[] rank;
        delete[] mstEdges;
    }

    void mstIncidenceMatrix() {
        createSet();

        edges = new Edge[edgeNumber];

        int edgeCount = 0;
        for (int j = 0; j < edgeNumber; j++) {
            int u = -1, v = -1;
            int weight = 0;

            for (int i = 0; i < vertexNumber; i++) {
                if (incidenceMatrix[i][j] != 0) {
                    if (u == -1) {
                        u = i;
                        weight = incidenceMatrix[i][j];
                    } else {
                        v = i;
                    }
                }
            }

            if (u != -1 && v != -1) {
                edges[edgeCount++] = {u, v, weight};
            }
        }

        mstResult = kruskalMST(edgeCount);
        delete[] edges;
    }


    void mstSuccessorList() {
        createSet();

        edges = new Edge[2 * edgeNumber];

        int edgeCount = 0;

        for (int u = 0; u < vertexNumber; u++) {
            LinkedList::Node* current = successorList[u].getHead();
            while (current) {
                int v = current->data.vertex;
                int w = current->data.weight;

                if (u < v) {
                    edges[edgeCount++] = {u, v, w};
                }

                current = current->next;
            }
        }

        mstResult = kruskalMST(edgeCount);
        delete[] edges;
    }

    std::string getMSTstring() const {
        std::string s;
        s = std::to_string(mstResult);
        s = "MST: " + s;
        return s;
    }

    void print() {
        for (int i = 0; i < mstEdgeNumber; i++) {
            std::cout << "( " << mstEdges[i].u << ", " << mstEdges[i].v << " ) : " << mstEdges[i].weight << std::endl;
        }

        std::cout << "TOTAL MST: " << mstResult << std::endl << std::endl;
    }

private:
    void createSet() {
        for (int i = 0; i < vertexNumber; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int i) {
        if (parent[i] != i) {
            parent[i] = find(parent[i]);
        }
        return parent[i];
    }

    void uniteSets(int x, int y) {
        int xRoot = find(x);
        int yRoot = find(y);

        if (xRoot == yRoot) return;

        if (rank[xRoot] < rank[yRoot]) {
            parent[xRoot] = yRoot;
        } else if (rank[xRoot] > rank[yRoot]) {
            parent[yRoot] = xRoot;
        } else {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }
    }

    int kruskalMST(int edgeCount) {
        mstEdges = new Edge[vertexNumber - 1];
        mstEdgeNumber = 0;

        for (int i = 0; i < edgeCount - 1; i++) {
            for (int j = 0; j < edgeCount - i - 1; j++) {
                if (edges[j].weight > edges[j + 1].weight) {
                    Edge temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }

        int mst = 0;
        for (int i = 0; i < edgeCount; i++) {
            int u = edges[i].u;
            int v = edges[i].v;
            if (find(u) != find(v)) {
                uniteSets(u, v);
                mst += edges[i].weight;
                mstEdges[mstEdgeNumber] = edges[i];
                mstEdgeNumber++;
            }
        }

        return mst;
    }

    int** incidenceMatrix;
    LinkedList* successorList;

    int* parent;
    int* rank;

    Edge* edges;
    Edge* mstEdges;

    int vertexNumber, edgeNumber, mstResult, mstEdgeNumber;
};
