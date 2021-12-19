#include "Graph.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

Graph::Graph(int vertexesNumber, std::vector<Edge> edges)
    : vertexesNumber(vertexesNumber),
    edges(std::move(edges)) {
    makeAdjacencyMatrix();
}


void Graph::makeAdjacencyMatrix() {
    adjacencyMatrix.assign(vertexesNumber + 1, std::vector<int>(vertexesNumber + 1, INT_MAX));
    
    for (const auto& e : edges) {
        adjacencyMatrix[e.edge.first][e.edge.second] = e.weight;
        adjacencyMatrix[e.edge.second][e.edge.first] = e.weight;
    }
}

void Graph::printMatrix—oefficients(std::ostream& output) {
    for (size_t i = 1; i < adjacencyMatrix.size(); ++i) {
        for (unsigned int j = 1; j < adjacencyMatrix[i].size(); j++) {
            output << adjacencyMatrix[i][j] << " ";
        }
        output << std::endl;
    }
}

void Graph::printFines(std::ostream& output, std::vector<std::vector<int>> fines) {
    for (size_t i = 1; i < fines.size(); ++i) {
        for (unsigned int j = 1; j < fines[i].size(); j++) {
            output << fines[i][j] << " ";
        }
        output << std::endl;
    }
}


void Graph::findMinRowValues() {
    minRow.assign(vertexesNumber + 1, INT_MAX);
    for (size_t i = 1; i < adjacencyMatrix.size(); ++i) {
        std::vector<int>::iterator minRowElement = std::min_element(adjacencyMatrix[i].begin(), adjacencyMatrix[i].end());
        minRow[i] = *minRowElement;
    }
}

int Graph::reduceMatrix() {
    int costOfReduction = 0;
    for (size_t i = 1; i < adjacencyMatrix.size(); ++i) {
        std::vector<int>::iterator minRowIt = std::min_element(adjacencyMatrix[i].begin(), adjacencyMatrix[i].end());
        int minRowValue = *minRowIt;
        minRow[i] = minRowValue;
        std::for_each(adjacencyMatrix[i].begin(), adjacencyMatrix[i].end(), [minRowValue](int& elem) {
            if (elem != INT_MAX) {
                elem -= minRowValue;
            }
        });
        //auto print = [](const int& n) { if (n == INT_MAX) { std::cout << " -"; } else { std::cout << " " << n; } };
        //std::for_each(adjacencyMatrix[i].cbegin(), adjacencyMatrix[i].cend(), print);
        //std::cout << "\n";
        for (size_t j = 1; j < adjacencyMatrix.size(); ++j) {
            if (adjacencyMatrix[i][j] < minColumn[j]) {
               
                minColumn[j] = adjacencyMatrix[i][j];
            }
        }
    }
    for (size_t i = 1; i < adjacencyMatrix.size(); ++i) {
        for (size_t j = 1; j < adjacencyMatrix.size(); ++j) {
            if (adjacencyMatrix[i][j] != INT_MAX) {
                adjacencyMatrix[i][j] -= minColumn[j];
            }
        }
    }
    return std::accumulate(minColumn.cbegin() + 1, minColumn.cend(), 0) + std::accumulate(minRow.cbegin() + 1, minRow.cend(), 0);
}



void Graph::findMinColumnValues() {
    minColumn.assign(vertexesNumber + 1, INT_MAX);
    for (size_t i = 1; i < adjacencyMatrix.size(); ++i) {
        for (size_t j = 1; j < adjacencyMatrix.size(); ++j) {
            if (adjacencyMatrix[i][j] < minColumn[j]) {
                minColumn[j] = adjacencyMatrix[i][j];
            }
        }
    }
}

int Graph::countBound() {
    return std::accumulate(minColumn.cbegin() + 1, minColumn.cend(), 0) + std::accumulate(minRow.cbegin() + 1, minRow.cend(), 0);
}

std::vector<std::vector<int>> Graph::countFines() {
    std::vector<std::vector<int>> fines(vertexesNumber + 1, std::vector<int>(vertexesNumber + 1, -1));
    for (size_t i = 1; i < adjacencyMatrix.size(); ++i) {
        for (size_t j = 1; j < adjacencyMatrix.size(); ++j) {
            if (adjacencyMatrix[i][j] == 0) {
                fines[i][j] = minColumn[j] + minRow[i];
            }
        }
    }
    return fines;
}

std::vector<int> Graph::findHamiltonCycle() {
    minRow.assign(vertexesNumber + 1, INT_MAX);
    minColumn.assign(vertexesNumber + 1, INT_MAX);
    bottomLimit += reduceMatrix();
    if (bottomLimit > record) {
        return;
    }
    std::vector<std::vector<int>> fines = countFines();
    //printMatrix—oefficients(std::cout);
    printFines(std::cout, fines);
    std::vector<int> v;
    return v;
}

void Graph::printMinRow(std::ostream& output) {
    for (size_t i = 1; i < minRow.size(); ++i) {
        int a;
        if (minRow[i] == INT_MAX) {
            a = -1;
        } else {
            a = minRow[i];
        }
        output << a << " ";
    }
    output << std::endl;
}

void Graph::printMinColumn(std::ostream& output) {
    for (size_t i = 1; i < minColumn.size(); ++i) {
        int a;
        if (minColumn[i] == INT_MAX) {
            a = -1;
        } else {
            a = minColumn[i];
        }
        output << a << " ";
    }
    output << std::endl;
}