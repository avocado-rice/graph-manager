cmake_minimum_required(VERSION 3.31)
project(aizoGraph)

set(CMAKE_CXX_STANDARD 20)

add_executable(aizoGraph main.cpp
        Structures/Graph.h
        Structures/LinkedList.h
        Control/FileHandler.h
        Timer/Timer.h
        Timer/Timer.cpp
        Algorithms/ShortestPath.h
        Algorithms/Prim.h
        Algorithms/Kruskal.h
        Control/Manager.h)
