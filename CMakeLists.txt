cmake_minimum_required(VERSION 4.2)
project(graph_manager)

set(CMAKE_CXX_STANDARD 14)

include_directories(aizoGraph/Algorithms)
include_directories(aizoGraph/Control)
include_directories(aizoGraph/Structures)
include_directories(aizoGraph/Timer)

add_executable(graph_manager
        aizoGraph/Algorithms/Dijkstra.h
        aizoGraph/Algorithms/Kruskal.h
        aizoGraph/Algorithms/Prim.h
        aizoGraph/Control/FileHandler.h
        aizoGraph/Control/Manager.h
        aizoGraph/Control/Worker.h
        aizoGraph/Control/WorkerFactory.h
        aizoGraph/Structures/Graph.h
        aizoGraph/Structures/LinkedList.h
        aizoGraph/Timer/Timer.cpp
        aizoGraph/Timer/Timer.h
        aizoGraph/main.cpp
        aizoGraph/Algorithms/BellmanFord.h)
