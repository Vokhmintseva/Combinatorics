#include "SpanningTreesCountAlgorithm.h"
#include "MatrixHelper.h"
#include <numeric>

SpanningTreesCountAlgorithm::SpanningTreesCountAlgorithm(int vertexesNumber, std::vector<Edge> edges)
    : vertexesNumber(vertexesNumber),
    edges(std::move(edges)) {
    makeAdjacencyMatrix();
    makeKirchhoffMatrix();
}

void SpanningTreesCountAlgorithm::makeAdjacencyMatrix() {
    adjacencyMatrix.assign(vertexesNumber, std::vector<int>(vertexesNumber, 0));
    for (const auto& e : edges) {
        adjacencyMatrix[e.edge.first - 1][e.edge.second - 1] = 1;
        adjacencyMatrix[e.edge.second - 1][e.edge.first - 1] = 1;
    }
}

void SpanningTreesCountAlgorithm::makeKirchhoffMatrix() {
    kirchhoffMatrix = adjacencyMatrix;
    for (size_t i = 0; i < kirchhoffMatrix.size(); ++i) {
        for (size_t j = 0; j < kirchhoffMatrix.size(); ++j) {
            kirchhoffMatrix[i][j] *= -1;
        }
        kirchhoffMatrix[i][i] = -1 * std::accumulate(kirchhoffMatrix[i].cbegin(), kirchhoffMatrix[i].cend(), 0);
    }
}

int SpanningTreesCountAlgorithm::countGaussDeterminant(Matrix& matrix) {
    int n = matrix.size();

    for (int col = 0; col < n; ++col) {
        bool found = false;
        for (int row = col; row < n; ++row) {
            if (matrix[row][col]) {
                if (row != col) {
                    matrix[row].swap(matrix[col]);
                }
                found = true;
                break;
            }
        }
        
        //на главной диагонали есть 0, поэтому определитель равен 0
        if (!found) {
            return 0;
        }

        for (int row = col + 1; row < n; ++row) {
            while (true) {
                int del = matrix[row][col] / matrix[col][col];
                for (int j = col; j < n; ++j) {
                    matrix[row][j] -= del * matrix[col][j];
                }
                if (matrix[row][col] == 0) {
                    break;
                } else {
                    //переставим строки, чтобы коэффициент, на который будем домножать строку, был целым числом, не равным 0
                    matrix[row].swap(matrix[col]);
                }
            }
        }
    }
       
    int result = 1;

    for (int i = 0; i < n; ++i) {
        result *= matrix[i][i];
    }
    return abs(result);
}

int SpanningTreesCountAlgorithm::countSpanningTrees() {
    //минор для матрицы Кирхгофа
    Matrix M(vertexesNumber - 1, std::vector<int>(vertexesNumber - 1));
    for (size_t i = 1; i < kirchhoffMatrix.size(); ++i) {
        for (size_t j = 1; j < kirchhoffMatrix.size(); ++j) {
            M[i - 1][j - 1] = kirchhoffMatrix[i][j];
        }
    }
    return countGaussDeterminant(M);
}
