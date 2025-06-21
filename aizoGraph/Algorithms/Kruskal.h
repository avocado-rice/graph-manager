#pragma once
class Kruskal {
    public:
    struct Edge {
        int u, v, weight;
    };

    void work(Graph graph) {
        createSet();

        for (int j = 0; j < E; ++j) {
            int u = -1, v = -1;
            for (int i = 0; i < V; ++i) {
                if (incidenceMatrix[i][j] > 0) {
                    u = i;
                } else if (incidenceMatrix[i][j] < 0) {
                    v = i;
                }
            }

            edges[j].u = u;
            edges[j].v = v;
            edges[j].weight = weights[j];
        }

        for (int i = 0; i < E - 1; ++i) {
            for (int j = 0; j < E - i - 1; ++j) {
                if (edges[j].weight > edges[j + 1].weight) {
                    Edge temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }

        int mstWeight = 0;
        for (int i = 0; i < E; ++i) {
            int u = edges[i].u;
            int v = edges[i].v;
            int w = edges[i].weight;

            if (find(u) != find(v)) {
                uniteSets(u, v);
                mstWeight += w;
            }
        }
    }

    private:
    createSet() {
        for (int i = 0; i < V; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int i) {
        if (i != parent[i])
            parent[i] = find(parent[i]);
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

    int* parent[] = nullptr;
    Edge* edges[] = nullptr;
    int** incidenceMatrix = nullptr;
};