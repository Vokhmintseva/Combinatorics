#include "Graph.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

Graph::Graph(int vertexesNumber, std::vector<std::pair<int, int>> edges)
    : vertexesNumber(vertexesNumber),
    edges(std::move(edges))
{}


void Graph::makeAdjacencyMatrix() {
    for (const auto &edge : edges) {
        adjacencyMatrix[edge.first][edge.second] = 1;
        adjacencyMatrix[edge.second][edge.first] = 1;
    }
}

void Graph::deepFirstSearch(int v, int p) {
    time++;
    timeIn[v] = time;
    up[v] = time;
    visited[v] = true;
    int children = 0;
    for (size_t to = 1; to < adjacencyMatrix[v].size(); ++to) {
        if (to == p || adjacencyMatrix[v][to] == 0) continue;
        if (visited[to])
            //найдено обратное ребро, сохраняем наименьшее время посещения вершины на обратном ребре
            up[v] = std::min(up[v], timeIn[to]);
        else {
            deepFirstSearch(to, v);
            up[v] = std::min(up[v], up[to]);
            /* если среди всех потомков вершина с минимальным временем посещения,
            доступная по обратному ребру, - это текущая вершина, или вершина, посещенная после текущей, то
            текущая вершина - точка сочленения (пути, ведущего выше нее по обратному ребру из потомков, нет) */
            if (up[to] >= timeIn[v] && p != -1) {
                cutPoints.insert(v);
            }
            ++children;
        }
    }
    if (p == -1 && children > 1) {
        cutPoints.insert(v);
    }
}

std::set<int> Graph::getCutPoints() {
    adjacencyMatrix.assign(vertexesNumber + 1, std::vector<int>(vertexesNumber + 1));
    visited.assign(vertexesNumber + 1, false);
    timeIn.assign(vertexesNumber + 1, 0);
    up.assign(vertexesNumber + 1, 0);
    makeAdjacencyMatrix();
    for (int n = 1; n <= vertexesNumber; ++n) {
        if (!visited[n]) {
            deepFirstSearch(n, -1);
        }
    }
    return cutPoints;
}

/*void Graph::printMatrixСoeffs(std::ostream& output) {
    for (size_t i = 1; i < adjacencyMatrix.size(); ++i) {
        for (unsigned int j = 1; j < adjacencyMatrix[i].size(); j++) {
            std::cout << adjacencyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}*/