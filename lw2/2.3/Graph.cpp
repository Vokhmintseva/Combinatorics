#include "Graph.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <list>

Graph::Graph(int vertexesNumber, std::vector<Edge> edges)
    : vertexesNumber(vertexesNumber),
    edges(std::move(edges)) {
    makeAdjacencyMatrix();    
}

void Graph::makeAdjacencyMatrix() {
    for (size_t i = 1; i <= vertexesNumber; ++i) {
        for (size_t j = 1; j <= vertexesNumber; ++j) {
            adjacencyMatrix[i][j] = INT_MAX;
        }
    }
    for (const auto& e : edges) {
        adjacencyMatrix[e.edge.first][e.edge.second] = e.weight;
        adjacencyMatrix[e.edge.second][e.edge.first] = e.weight;
    }
}

void Graph::printMatrix�oefficients(std::ostream& output) {
    for (size_t i = 1; i <= adjacencyMatrix.size(); ++i) {
        for (unsigned int j = 1; j <= adjacencyMatrix[i].size(); j++) {
            output << adjacencyMatrix[i][j] << " ";
        }
        output << std::endl;
    }
}

int Graph::reduceMatrix(Matrix &m) {
    //���������� ��� �������� ����� ���������� ������� �� �������
    int rowReduction = 0;

    //�������� ������ ��� �������� ������������ �������� �� �������, �������� ��� ������� INT_MAX;
    std::map<int, int> minColumn;
    std::for_each(m.begin(), m.end(), [&minColumn](std::pair<const int, std::map<int, int>>& row) {
        minColumn[row.first] = INT_MAX;
    });

    //��������� ������ ������ �������;
    for (auto& pair: m) {
        const int rowNumber = pair.first;
        std::map<int, int> row = pair.second;
        std::map<int, int>::iterator minRowIt = std::min_element(row.begin(), row.end(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });
        int minRowValue = (*minRowIt).second;
        
        // ���� �� �����-�� ������� ��� ����, �� ���� ���� ������ �� �������������;
        if (minRowValue == INT_MAX) return -1;

        rowReduction += minRowValue;
        
        //�� ������� �������� ������ ������ ����������� �������� �� ������;
        std::for_each(row.begin(), row.end(), [minRowValue](std::pair<const int, int>& elem) {
            if (elem.second != INT_MAX) {
                elem.second -= minRowValue;
            }
        });
        
        //� ������ minColumn �������� ����������� �������� �� ������� ������� �������
        std::for_each(row.begin(), row.end(), [&minColumn](std::pair<const int, int>& elem) {
            int columnNumber = elem.first;
            if (elem.second < minColumn[columnNumber]) {
                minColumn[columnNumber] = elem.second;
            }
        });
    }

    /*auto print = [](const std::map<int, int>::value_type& elem) { if (elem.second == INT_MAX) { std::cout << " -"; } else { std::cout << " " << elem.second; } };
    std::for_each(minColumn.cbegin(), minColumn.cend(), print);
    std::cout << "\n";*/

    // ������ ��������� ��� ������� � �� ������� �������� ������� ������ ��� �������;
    for (auto& pair : m) {
        const int rowNumber = pair.first;
        std::map<int, int> row = pair.second;
        for (auto& elem : row) {
            const int columnNumber = pair.first;
            if (m[rowNumber][columnNumber] != INT_MAX) {
                // ���� ����������� �������� INT_MAX, �� ���� ��� ������� ���, ������ ���� ���� �� �������������
                if (minColumn[columnNumber] == INT_MAX) return -1;
                m[rowNumber][columnNumber] -= minColumn[columnNumber];
            }
        }
    }
    
    //������ ����� ���������� �� ��������;
    int columnReduction = std::accumulate(minColumn.cbegin(), minColumn.cend(), 0, [](int value, const std::map<int, int>::value_type& elem) {
        return value + elem.second; 
    });

    return rowReduction + columnReduction;
}

/*std::vector<std::vector<int>> Graph::countFines() {
    std::vector<std::vector<int>> fines(vertexesNumber + 1, std::vector<int>(vertexesNumber + 1, -1));
    for (size_t i = 1; i < adjacencyMatrix.size(); ++i) {
        for (size_t j = 1; j < adjacencyMatrix.size(); ++j) {
            if (adjacencyMatrix[i][j] == 0) {
                fines[i][j] = minColumn[j] + minRow[i];
            }
        }
    }
    return fines;
}*/

int getCoefficient(const Matrix& m, int row, int Column) {
    int rowMin = INT_MAX;
    int columnMin = INT_MAX;
    
    for (size_t i = 0; i < m.size(); ++i) {
        if (i != r)
            rmin = std::min(rmin, m(i, c));
        if (i != c)
            cmin = std::min(cmin, m(r, i));
    }

    return rmin + cmin;
}

std::vector<int> Graph::findHamiltonCycle() {
    bottomLimit += reduceMatrix(adjacencyMatrix);
    if (bottomLimit > record) {
        return;
    }
    // ������ ��������� ������� ���������
    std::list<std::pair<int, int>> zeroVertexes;
    // ������ �� �������������
    std::list<int> coefficientsList;

    // ������������ �����������
    int maxCoeff = 0;
    // ����� ������� ���������
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i)
        for (size_t j = 0; j < matrix.size(); ++j)
            // ���� ����� ����
            if (!matrix(i, j)) {
                // ���������� � ������ ���������
                zeros.emplace_back(i, j);
                // ������ ����������� � ���������� � ������
                coeffList.push_back(getCoefficient(matrix, i, j));
                // ��������� � ������������
                maxCoeff = std::max(maxCoeff, coeffList.back());
            }
    std::vector<int> v;
    return v;
}
