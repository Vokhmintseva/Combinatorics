#pragma once
#include <iostream>
#include <vector>
#include <set>

class Graph {
public:
	Graph(int vertexesNumber, std::vector<std::pair<int, int>> edges);
    //void printMatrix�oeffs(std::ostream& output);
    std::set<int> getCutPoints();
private: 
    void makeAdjacencyMatrix();
    void deepFirstSearch(int v, int p);
    int vertexesNumber = 0;
    std::vector<std::pair<int, int>> edges;
    using Matrix = std::vector<std::vector<int>>;
    Matrix adjacencyMatrix;
    std::vector<bool> visited;
    
    //��� ������ ������� ������ timeIn ������ ����� �� ���������
    std::vector<int> timeIn;
    
    /* ��� ������ ������� ������ up ������:
    - ���������� �� ������ ��������� ����� ������, � ������� ���� �������� �����
      �� ���� ������� � ���� �� ��������;
    - ���� �������� ����� � ������� � �� �������� ���, �� ����� ��������� ���� ������� */
    std::vector<int> up;
    std::set<int> cutPoints;
    int time = 0;
};