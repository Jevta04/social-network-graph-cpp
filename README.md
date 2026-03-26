# Social Network Graph Modeling (Adjacency Matrix)

C++ application that models a social network as a directed weighted graph using an **adjacency matrix** representation, with support for network analysis operations.

Developed as a homework assignment for the **Algorithms and Data Structures (ASP)** course at the **School of Electrical Engineering (ETF), University of Belgrade**, 2024.

---

## Problem Description

Social relationships and interactions are modeled as a directed weighted graph where:
- **Nodes** represent users
- **Directed edges** represent follow relationships
- **Edge weights** (range [0, 1]) represent the probability that a post from user B appears on user A's feed

For example, an edge A → B with weight 0.75 means there is a 75% chance that B's post will appear on A's homepage. When A likes B's post, the edge weight increases by 0.1 (capped at 1.0).

When analyzing indirect connections (A → B → C), edge weights are **multiplied** to compute the indirect connection strength.

## Graph Representation

**Adjacency matrix** — a 2D array of edge weights (`double tezina[MAX][MAX]`) with a separate array of node name strings.

## Features

**Graph manipulation (55 pts):**
- Load users and relationships from a text file
- Add / remove users (nodes)
- Add / remove interactions (edges)
- Display the graph (adjacency matrix)
- Clear the graph from memory

**Social network analysis (45 pts):**
- Like a post — increases edge weight by 0.1 (max 1.0)
- Find the **largest strongly connected component** (all users mutually reachable)
- Print all users on the **highest-probability path** between two users, in format:
  `user1 - (prob) -> user2 - (prob) -> user3 -> ...`
- Find the **k-th most influential user** — the user whose posts reach all others with the highest probability (modified Floyd-Warshall)

## Algorithms

| Algorithm | Purpose |
|---|---|
| Modified Dijkstra's | Highest-probability path (multiplies weights instead of summing) |
| Kosaraju's SCC (iterative DFS) | Largest strongly connected component |
| Modified Floyd-Warshall | All-pairs maximum influence for k-th influential user |

> Recursion is not used — all traversals are implemented iteratively with an explicit stack, per course requirements. STL containers are not used.

## Input File Format

```
<number of nodes n>
<number of edges e>
<user1> <user2> ... <userN>
<person1> <person2> <weight>
...
```

## Build

Open `j0230058/jo230058.sln` in Visual Studio and build, or compile manually:

```bash
g++ -std=c++11 j0230058/main.cpp j0230058/graf.cpp j0230058/drustvenamreza.cpp -o social_network
```

## Menu

```
1  - Load network from file
2  - Display graph (adjacency matrix)
3  - Add user
4  - Remove user
5  - Add interaction (edge)
6  - Remove interaction (edge)
7  - Clear graph
8  - Like post (increase edge weight by 0.1)
9  - Find largest strongly connected component
10 - Find highest-probability path between two users
11 - Find k-th most influential user
12 - Exit
```

## Course Info

| | |
|---|---|
| **Course** | Algorithms and Data Structures (13E112ASP) |
| **Department** | Computer Engineering and Informatics |
| **Institution** | School of Electrical Engineering (ETF), University of Belgrade |
| **Year** | 2024 |
