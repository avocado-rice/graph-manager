#pragma once
#include <"Graph.h">

class Worker {
public:
    virtual void work(Graph graph) = 0;
    virtual ~Worker() = default;
};