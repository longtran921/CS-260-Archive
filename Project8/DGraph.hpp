//
// Created by ACER NITRO on 11/22/2023.
//

#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <stdexcept>
#include <algorithm>

struct Edge {
    char value;
    Edge* next;
};

struct Node {
    char value;
    bool visited;
    Edge* adjacencyList;
};

class DGraph {
private:
    Node G[20]{};
    int M[20][20]{};

    int numNodes;
    int maxSize = 20;

public:
    DGraph();
    void addNode(char value);
    int findNode(char value) ;
    void addEdge(char starts, char ends);
    std::string listNodes();
    std::string displayAdjacency();
    std::string displayMatrix();
    std::string breadthFirst(char value, bool edge = false, bool unreachable = true);
    std::string depthFirst(char value, bool edge = false, bool unreachable = true);
    std::string minTree(char value);
    std::string connectTable();

    inline void resetVisited() {
        for (int i = 0; i < numNodes; ++i) {
            G[i].visited = false;
        }
    }
};