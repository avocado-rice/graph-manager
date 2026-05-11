#pragma once
#include "Worker.h"

class WorkerFactory {
public:
    static Worker* createMstWorker(int a) {
        switch (a) {
            case 0:
                return new Kruskal();
            case 1:
                return new Prim();
            default:
                return nullptr;
        }
    };

    static Worker* createPathWorker(int a) {
        switch (a) {
            case 0:
                return new Dijkstra();
            case 1:
                return new FordBellman();
            default:
                return nullptr;
        }
    };
};