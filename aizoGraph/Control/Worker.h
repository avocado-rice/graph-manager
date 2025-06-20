#pragma once
#include <"C:\Users\KatarzynaNowomiejska\Desktop\aizo_dwa\aizoGraph\Structures\Graph.h">

class Worker {
    public:
    virtual void work(Graph graph) = 0;
    virtual ~Worker() = default;
};