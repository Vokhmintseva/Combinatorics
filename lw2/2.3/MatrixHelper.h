#pragma once
#include <algorithm>
#include "BranchAndBound.h"

class MatrixHelper {
public:
    //получить индекс строки матрицы, зная номер вершины
    static int getRowIndex(const BranchAndBound::Matrix& m, int row) {
        for (size_t i = 1; i < m.size(); ++i) {
            if (m[i][0] == row) {
                return i;
            }
        }
        return INT_MAX;
    }

    //получить индекс столбца матрицы, зная номер вершины
    static int getColumnIndex(const BranchAndBound::Matrix& m, int column) {
        auto it = std::find(m[0].begin() + 1, m[0].end(), column);
        return it != m[0].end() ? std::distance(m[0].begin(), it) : INT_MAX;
    }

    // получить номера вершин для ребра, зная индексы строки и столбца в матрице
    static Edge getVertexesNumbers(const BranchAndBound::Matrix& m, const Edge& e) {
        Edge realEdge;
        realEdge.edge.first = m[e.edge.first][0];
        realEdge.edge.second = m[0][e.edge.second];
        return realEdge;
    }

    static void printMatrixСoefficients(const BranchAndBound::Matrix& m, std::ostream& output) {
        for (size_t i = 0; i < m.size(); ++i) {
            for (unsigned int j = 0; j < m[i].size(); j++) {
                if (m[i][j] == INT_MAX) {
                    output << "- ";
                }
                else {
                    output << m[i][j] << " ";
                }
            }
            output << "\n";
        }
    }
};