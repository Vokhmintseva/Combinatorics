#include "Graph.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

Graph::Graph(std::istream& input): input(input) {
	getVertexesAndEdgesNumber();
    adjacencyMatrix.assign(vertexesNumber + 1, std::vector<int>(vertexesNumber + 1));
    visited.assign(vertexesNumber + 1, false);
    timeIn.assign(vertexesNumber + 1, 0);
    up.assign(vertexesNumber + 1, 0);
    readAdjacencyMatrix();
    getCutPoints();
}

void Graph::getVertexesAndEdgesNumber() {
    std::string line;
    getline(input, line);
    std::stringstream iss(line);
    iss >> vertexesNumber >> edgesNumber;
}

void Graph::readAdjacencyMatrix() {
    std::string line;
    int strCounter = 0;
    while (getline(input, line) && strCounter < edgesNumber) {
        ++strCounter;
        std::istringstream iss(line);
        int vertex1 = 0;
        int vertex2 = 0;
        iss >> vertex1 >> vertex2;
        adjacencyMatrix[vertex1][vertex2] = 1;
        adjacencyMatrix[vertex2][vertex1] = 1;
    }

    if (strCounter < edgesNumber) {
        throw std::invalid_argument("Incorrect number of edges");
    }
}

void Graph::deepFirstSearch(int v, int p) {
    time++;
    timeIn[v] = time;
    up[v] = time;
    visited[v] = true;
    int children = 0;
    for (int to = 1; to < adjacencyMatrix[v].size(); ++to) {
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
                cutPoints.push_back(v);
            }
            ++children;
        }
    }
    if (p == -1 && children > 1) {
        cutPoints.push_back(v);
    }
}

void Graph::getCutPoints() {
    for (int n = 1; n <= vertexesNumber; ++n) {
        if (!visited[n]) {
            deepFirstSearch(n, -1);
        }
    }
}

void Graph::printCutPoints(std::ostream& output) {
    for (std::vector<int>::const_iterator i = cutPoints.cbegin(); i != cutPoints.cend(); ++i)
        std::cout << *i << " ";
}

void Graph::printMatrixСoeffs(std::ostream& output) {
    for (size_t i = 1; i < adjacencyMatrix.size(); ++i) {
        for (unsigned int j = 1; j < adjacencyMatrix[i].size(); j++) {
            std::cout << adjacencyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}