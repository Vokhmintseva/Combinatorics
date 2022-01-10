#pragma once
#include <iostream>
#include <vector>

struct Edge {
    std::pair<int, int> edge;
    int weight;
};

class SpanningTreesCountAlgorithm {
public:
    using Matrix = std::vector<std::vector<int>>;
    SpanningTreesCountAlgorithm(int vertexesNumber, std::vector<Edge> edges);
    int countSpanningTrees();
private:
    void makeAdjacencyMatrix();
    void makeKirchhoffMatrix();
    int countGaussDeterminant(Matrix& matrix);
    int vertexesNumber;
    std::vector<Edge> edges;
    Matrix adjacencyMatrix;
    Matrix kirchhoffMatrix;
};
