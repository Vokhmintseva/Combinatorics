#pragma once
#include <iostream>
#include <vector>
#include <set>

struct Edge {
    std::pair<int, int> edge;
    int weight;
};

class Graph {
public:
    Graph(int vertexesNumber, std::vector<Edge> edges);
    void printMatrix—oefficients(std::ostream& output);
    std::vector<int> findHamiltonCycle();
    void printMinRow(std::ostream& output);
    void printMinColumn(std::ostream& output);
    void findMinRowValues();
    void findMinColumnValues();
    int countBound();
    std::vector<std::vector<int>> countFines();
    void printFines(std::ostream& output, std::vector<std::vector<int>> fines);

private:
    void makeAdjacencyMatrix();
    int reduceMatrix();
    int vertexesNumber = 0;
    std::vector<Edge> edges;
    using Matrix = std::vector<std::vector<int>>;
    Matrix adjacencyMatrix;
    Matrix fines;
    int bottomLimit = 0;
    int record = 0;
    std::vector<int> minRow;
    std::vector<int> minColumn;

};
