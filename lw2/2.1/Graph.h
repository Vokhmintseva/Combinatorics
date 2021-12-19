#pragma once
#include <iostream>
#include <vector>
#include <set>

class Graph {
public:
	Graph(int vertexesNumber, std::vector<std::pair<int, int>> edges);
    //void printMatrixСoeffs(std::ostream& output);
    std::set<int> getCutPoints();
private: 
    void makeAdjacencyMatrix();
    void deepFirstSearch(int v, int p);
    int vertexesNumber = 0;
    std::vector<std::pair<int, int>> edges;
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
    std::set<int> cutPoints;
    int time = 0;
};