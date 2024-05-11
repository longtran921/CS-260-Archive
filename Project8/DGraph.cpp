//
// Created by ACER NITRO on 11/22/2023.
//

#include "DGraph.hpp"

DGraph::DGraph() {
    numNodes = 0;
    for (int i = 0; i < maxSize; ++i) {
        for (int j = 0; j < maxSize; ++j) {
            M[i][j] = 0;
        }
    }
}

void DGraph::addNode(char value) {
    if (numNodes >= maxSize) {
        throw std::overflow_error("Graph is full");
    }

    G[numNodes].value = value;
    G[numNodes].visited = false;
    G[numNodes].adjacencyList = nullptr;
    numNodes++;
}

int DGraph::findNode(char value) {
    for (int i = 0; i < numNodes; ++i) {
        if (G[i].value == value) {
            return i;
        }
    }
    return -1; //Indicate not present
}

void DGraph::addEdge(char starts, char ends) {
    int startsIdx = findNode(starts);
    int endsIdx = findNode(ends);

    if (startsIdx == -1 || endsIdx == -1 || starts == ends) {
        throw std::invalid_argument("Invalid nodes for edge, caught a -1 or same node");
    }

    Edge *newEdge = new Edge();
    newEdge->value = ends;
    newEdge->next = G[startsIdx].adjacencyList;
    G[startsIdx].adjacencyList = newEdge;
    M[startsIdx][endsIdx] = 1;
}

std::string DGraph::listNodes() {
    std::string nodeList;
    for (int i = 0; i < numNodes; ++i) {
        nodeList += G[i].value;
        nodeList += " ";
    }
    return nodeList;
}

std::string DGraph::displayAdjacency() {
    std::string adjacencyOutput;
    for (int i = 0; i < numNodes; ++i) {
        adjacencyOutput += G[i].value;
        adjacencyOutput += ": ";
        Edge *current = G[i].adjacencyList;
        while (current != nullptr) {
            adjacencyOutput += current->value;
            adjacencyOutput += " ";
            current = current->next;
        }
        adjacencyOutput += "\n";
    }
    return adjacencyOutput;
}

std::string DGraph::displayMatrix() {
    std::string matrixOutput = "    ";

    for (int i = 0; i < numNodes; ++i) {
        matrixOutput += G[i].value;
        matrixOutput += "   ";
    }
    matrixOutput += "\n";

    for (int i = 0; i < numNodes; ++i) {
        matrixOutput += G[i].value; //
        matrixOutput += "   ";
        for (int j = 0; j < numNodes; ++j) {
            if (M[i][j] == 1) {
                matrixOutput += "1   ";
            } else {
                matrixOutput += ".   ";
            }
        }
        matrixOutput += "\n";
    }
    return matrixOutput;
}
std::string DGraph::breadthFirst(char value, bool edge, bool unreachable) {
    bool firstValue = true;
    int idx = findNode(value);
    if (idx == -1) {
        throw std::invalid_argument("Node not found");
    }

    std::string traversal;
    resetVisited();

    std::queue<int> queue;
    queue.push(idx);
    G[idx].visited = true;

    while (!queue.empty()) {
        int currIdx = queue.front();
        queue.pop();

        traversal += G[currIdx].value;
        if (firstValue) {
            traversal += ":";
            firstValue = false;
        }
        traversal += " ";
        Edge *current = G[currIdx].adjacencyList;

        while (current != nullptr) {
            int neighborIdx = findNode(current->value);
            if (!G[neighborIdx].visited) {
                G[neighborIdx].visited = true;
                queue.push(neighborIdx);
            }
            current = current->next;
        }
    }

    if (unreachable) {
        traversal += "with ";
        for (int i = 0; i < numNodes; ++i) {
            if (!G[i].visited) {
                traversal += G[i].value;
                traversal += " ";
            }
        }
        traversal += "unreachable";
    }

    return traversal;
}

std::string DGraph::depthFirst(char value, bool edge, bool unreachable) {
    bool firstValue = true;
    int idx = findNode(value);
    if (idx == -1) {
        throw std::invalid_argument("Node not found");
    }

    std::string traversal;
    resetVisited();

    std::stack<int> stack;
    stack.push(idx);

    while (!stack.empty()) {
        int currIdx = stack.top();
        stack.pop();

        if (!G[currIdx].visited) {
            traversal += G[currIdx].value;
            if (firstValue) {
                traversal += ":";
                firstValue = false;
            }
            traversal += " ";
            G[currIdx].visited = true;

            Edge *current = G[currIdx].adjacencyList;
            std::vector<int> neighbors;

            while (current != nullptr) {
                int neighborIdx = findNode(current->value);
                if (!G[neighborIdx].visited) {
                    neighbors.push_back(neighborIdx);
                }
                current = current->next;
            }

            for (int i = neighbors.size() - 1; i >= 0; --i) {
                stack.push(neighbors[i]);
            }
        }
    }

    if (unreachable) {
        traversal += "with ";
        for (int i = 0; i < numNodes; ++i) {
            if (!G[i].visited) {
                traversal += G[i].value;
                traversal += " ";
            }
        }
        traversal += "unreachable";
    }

    return traversal;
}

std::string DGraph::minTree(char value) {
    bool firstValue = true;
    int idx = findNode(value);
    if (idx == -1) {
        throw std::invalid_argument("Node not found");
    }

    std::string minTreeOutput;
    resetVisited();

    std::stack<int> stack;
    stack.push(idx);

    while (!stack.empty()) {
        int currIdx = stack.top();
        stack.pop();

        if (!G[currIdx].visited) {
            G[currIdx].visited = true;

            Edge *current = G[currIdx].adjacencyList;
            std::vector<int> neighbors;

            while (current != nullptr) {
                int neighborIdx = findNode(current->value);
                if (!G[neighborIdx].visited) {
                    neighbors.push_back(neighborIdx);
                }
                current = current->next;
            }

            std::sort(neighbors.begin(), neighbors.end(), [&](int a, int b) {
                return G[a].value < G[b].value;
            });

            for (int neighbor: neighbors) {
                stack.push(neighbor);
                if (G[neighbor].visited) {
                    continue;
                }
                if (firstValue) {
                    minTreeOutput += G[currIdx].value;
                    minTreeOutput += ": ";
                    firstValue = false;
                }
                minTreeOutput += G[currIdx].value;
                minTreeOutput += "-";
                minTreeOutput += G[neighbor].value;
                minTreeOutput += " ";
            }
        }
    }

    return minTreeOutput;
}

std::string DGraph::connectTable() {
    std::string connectTableOutput;

    for (int i = 0; i < numNodes; ++i) {
        std::queue<int> queue;
        std::vector<bool> visited(numNodes, false);

        connectTableOutput += breadthFirst(G[i].value, false, false);
        connectTableOutput += "\n";
    }

    return connectTableOutput;
}