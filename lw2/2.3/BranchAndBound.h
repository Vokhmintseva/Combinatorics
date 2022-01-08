#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <optional>

struct Edge {
    std::pair<int, int> edge;
    int weight;
};

class BranchAndBound {
public:
    using Matrix = std::vector<std::vector<int>>;
    BranchAndBound(int vertexesNumber, std::vector<Edge> edges);
    std::list<int> findHamiltonCycle();
private:
    void makeAdjacencyMatrix();
    void preventCycles(Matrix& m, std::list<Edge> pathes) const;
    Edge getZeroElementWithMaxFine(const Matrix& m) const;
    int calculateFine(const Matrix& m, int rowNumber, int columnNumber) const;
    std::optional<int> reduceMatrix(Matrix &m) const;
    void deleteEdges(Matrix& m, const Edge &edge) const;
    void solve(Matrix m, std::list<Edge> path, int bound);
    std::list<int> extractVertexesfromEdges() const;
    int vertexesNumber;
    std::vector<Edge> edges;
    Matrix adjacencyMatrix;
    int lowestBound = INT_MAX;
    std::list<Edge> bestPath;
};
