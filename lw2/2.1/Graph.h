#pragma once
#include <iostream>
#include <vector>

class Graph {
public:
	Graph(std::istream& input);
    void printMatrix�oeffs(std::ostream& output);
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
    
    //��� ������ ������� ������ timeIn ������ ����� �� ���������
    std::vector<int> timeIn;
    
    /* ��� ������ ������� ������ up ������:
    - ���������� �� ������ ��������� ����� ������, � ������� ���� �������� �����
      �� ���� ������� � ���� �� ��������;
    - ���� �������� ����� � ������� � �� �������� ���, �� ����� ��������� ���� ������� */
    std::vector<int> up;
    
    std::istream& input;
    std::vector<int> cutPoints;
    int time = 0;
};