#pragma once
#include <iostream>
#include <vector>

class Graph {
public:
	Graph(std::istream& input);
    void printMatrixСoeffs(std::ostream& output);
    void printCutPoints(std::ostream& output);
private: 
    void getVertexesAndEdgesNumber();
    void readAdjacencyMatrix();
    void getCutPoints();
    void deepFirstSearch(int v, int p);
    int vertexesNumber = 0;
    int edgesNumber = 0;
    using Matrix = std::vector<std::vector<int>>;
    Matrix adjacencyMatrix;
    std::vector<bool> visited;
    
    //для каждой вершины вектор timeIn хранит время ее посещения
    std::vector<int> timeIn;
    
    /* для каждой вершины вектор up хранит:
    - наименьшее из времен посещения среди вершин, в которые есть обратные ребра
      из этой вершины и всех ее потомков;
    - если обратных ребер у вершины и ее потомков нет, то время посещения этой вершины */
    std::vector<int> up;
    
    std::istream& input;
    std::vector<int> cutPoints;
    int time = 0;
};