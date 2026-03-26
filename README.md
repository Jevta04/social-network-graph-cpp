# Social Network Graph Analysis

C++ application that models a social network as a directed weighted graph and provides tools for analyzing user interactions, influence, and connectivity.

Developed as a project for the **Algorithms and Data Structures (ASP)** course at the **School of Electrical Engineering, University of Belgrade**, 2024.

---

## Description

The application represents users as graph nodes and their interactions (likes, follows) as directed weighted edges (probabilities in range [0, 1]). It supports loading network data from a file and offers several graph analysis operations through an interactive CLI menu.

## Features

- Load social network from a file
- Add / remove users (nodes) and interactions (edges)
- Like a post — increments the interaction weight by 0.1 (max 1.0)
- Find the **largest strongly connected component** (Kosaraju's algorithm)
- Find the **highest-probability path** between two users (modified Dijkstra's algorithm)
- Find the **k-th most influential user** by total reachability (modified Floyd-Warshall algorithm)

## Algorithms & Data Structures

| Algorithm | Purpose |
|---|---|
| Adjacency matrix | Graph representation (up to 50 nodes) |
| Modified Dijkstra's | Highest-probability path (multiplies edge weights) |
| Kosaraju's SCC | Largest strongly connected component |
| Modified Floyd-Warshall | All-pairs maximum influence paths |
| Iterative DFS (stack) | Graph traversal |

## Build

Open `j0230058/jo230058.sln` in Visual Studio and build the solution, or compile manually:

```bash
g++ -std=c++11 main.cpp graf.cpp drustvenamreza.cpp -o social_network
```

## Usage

Run the executable and use the numbered menu:

```
1  - Load network from file
2  - Display graph (adjacency matrix)
3  - Add user
4  - Remove user
5  - Add interaction
6  - Remove interaction
7  - Clear graph
8  - Like post (increase interaction weight)
9  - Find largest connected component
10 - Find highest-probability path between two users
11 - Find k-th most influential user
12 - Exit
```

## Course Info

- **Course:** Algorithms and Data Structures (ASP)
- **Institution:** School of Electrical Engineering (ETF), University of Belgrade
- **Year:** 2024
