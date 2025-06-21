#pragma once
class Dijkstra {
public:
    Dijkstra(int v, int e, int** matrix) {
        incidenceMatrix = matrix;
        vertexes = v;
        edges = e;
    };

    void work(int src) {
        int* distance = new int[vertexes];
        bool* visited = new bool[vertexes];

        for (int i = 0; i < vertexes; i++) {
            distance[i] = 100000;
            visited[i] = false;
        }

        distance[src] = 0;

        for (int c = 0; c < vertexes - 1; c++) {
            int d = minDistance(distance, visited);

            if (d == -1) break;
            visited[d] = true;

            for (int j = 0; j < edges; j++) {
                if (incidenceMatrix[d][j] > 0) { // Krawędź wychodzi z u
                    int weight = incidenceMatrix[d][j];
                    int v = -1;

                    for (int i = 0; i < vertexes; i++) {
                        if (incidenceMatrix[i][j] < 0) {
                            v = i;
                            break;
                        }
                    }

                    if (v != -1 && !visited[v] && distance[d] != 100000 &&
                        distance[d] + weight < distance[v]) {
                        distance[v] = distance[d] + weight;
                        }
                }
            }
        }
        delete[] distance;
        delete[] visited;
    }

private:
    int minDistance(int* distance, bool* visited) {
        int min = 100000;
        int min_index = -1;

        for (int i = 0; i < vertexes; i++) {
            if (!visited[i] && distance[i] <= min) {
                min = distance[i];
                min_index = i;
            }
        }

        return min_index;
    }

    int** incidenceMatrix;
    int vertexes, edges;
};