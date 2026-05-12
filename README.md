## Overview

A performance analysis tool for graph algorithms, utilizing custom-built data structures to measure execution efficiency between two different graph representations.

## Structures

This project avoids standard library containers, utilizing custom-built data structures to provide low-level control over memory and performance.

### Graph Implementation

Every edge is simultaneously stored in both an Incidence Matrix and an Adjacency List:

- **Incidence Matrix:** Implemented as a dynamic 2D array. It maps vertices to edges, with support for both directed and undirected logic.

- **Adjacency List:** An array of self-made Linked Lists.

## Usage

The app operates in two modes via the command line - file and benchmark.

### Benchmark Mode

Generate random graphs based on user-defined parameters to measure performance.

``` shell
./aizoGraph test [problem] [algorithm] [size] [density] [count] [output_file]
```

- **Size:** Number of vertices.
    
- **Density:** Graph density (0.0 to 1.0)
    
- **Count:** Number of iterations

**Graph Generation Logic:** To ensure valid testing, the generator first creates a Minimum Spanning Tree to guarantee graph connectivity. Then, it randomly adds remaining edges until the target density is reached. Weights are assigned in the range from 0 to `INT_MAX`.

### File Mode

Load a graph from a text file to solve a given problem.

``` shell
./aizoGraph file [problem] [algorithm] [input_file] [output_file] [source] [destination]
```

- **Problem:** 0 (MST), 1 (Shortest Path)
    
- **Algorithm (MST):** 0 (Prim), 1 (Kruskal)
    
- **Algorithm (Shortest Path):** 0 (Dijkstra), 1 (Bellman-Ford)
  
#### File Input Format
The input text file must follow the following structure:

Header Line: Two integers repreenting the Total Number of Edges and the Total Number of Vertices.

Edge Lines: Each subsequent line must contain three integers: Source Vertex, Destination Vertex, and Weight.

Example (input.txt):

``` Plaintext
3 3
0 1 5
1 2 10
0 2 2
```
