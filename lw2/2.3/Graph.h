#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <list>

struct Edge {
    std::pair<int, int> edge;
    int weight;
};

class Graph {
public:
    using Matrix = std::vector<std::vector<int>>;
    Graph(int vertexesNumber, std::vector<Edge> edges);
    void printMatrix—oefficients(const Matrix& m, std::ostream& output);
    void findHamiltonCycle();
    std::list<Edge> testPreventCycles(std::list<Edge> p);

private:
    void makeAdjacencyMatrix();
    Edge getZeroElementWithMaxFine(const Matrix& m);
    void preventCycle(Matrix& m, std::list<Edge> pathes);
    void preventCycles(Matrix& m, std::list<Edge> pathes);
    Edge getRealCoordinates(const Matrix& m, const Edge &e);
    Edge getCoordinatesInMatrix(const Matrix& m, const Edge& realE);
    int calculateFine(const Matrix& m, int rowNumber, int columnNumber);
    int reduceMatrix(Matrix &m);
    void deleteEdges(Matrix& m, const Edge &edge);
    void solve(Matrix m, std::list<Edge> path, int bound);
    int vertexesNumber = 0;
    std::vector<Edge> edges;
    Matrix adjacencyMatrix;
    int bestBound = 0;
    std::list<Edge> bestPath;
};
