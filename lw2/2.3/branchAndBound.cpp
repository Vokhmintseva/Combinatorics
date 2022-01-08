#include "BranchAndBound.h"
#include "MatrixHelper.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <list>
#include <optional>

BranchAndBound::BranchAndBound(int vertexesNumber, std::vector<Edge> edges)
    : vertexesNumber(vertexesNumber),
    edges(std::move(edges)) {
    makeAdjacencyMatrix();
}

void BranchAndBound::makeAdjacencyMatrix() {
    adjacencyMatrix.assign(vertexesNumber + 1, std::vector<int>(vertexesNumber + 1, INT_MAX));
    for (const auto& e : edges) {
        adjacencyMatrix[e.edge.first][e.edge.second] = e.weight;
    }
    /* adjacencyMatrix - это вектор векторов
        в векторе под индексом 0 (adjacencyMatrix[0]) будут храниться номера вершин для столбцов матрицы,
        а в каждом их векторов под нулевым индексом будут храниться номера вершин для строк матрицы
        (чтобы после удаления строк и столбцов сохранились номера вершин):
    */
    std::iota(adjacencyMatrix[0].begin(), adjacencyMatrix[0].end(), 0);
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
        adjacencyMatrix[i][0] = i;
    }
}

std::optional<int> BranchAndBound::reduceMatrix(Matrix &m) const {
    std::vector<int> minRow(m.size(), INT_MAX);
    std::vector<int> minColumn(m.size(), INT_MAX);
    for (size_t i = 1; i < m.size(); ++i) {
        std::vector<int>::iterator minRowIt = std::min_element(m[i].begin() + 1, m[i].end());
        int minRowValue = *minRowIt;
        minRow[i] = minRowValue;
        std::for_each(m[i].begin() + 1, m[i].end(), [minRowValue](int& elem) {
            if (elem != INT_MAX) {
                elem -= minRowValue;
            }
        });

        for (size_t j = 1; j < m.size(); ++j) {
            if (m[i][j] < minColumn[j]) {
                minColumn[j] = m[i][j];
            }
        }
    }
    for (size_t i = 1; i < m.size(); ++i) {
        for (size_t j = 1; j < m.size(); ++j) {
            if (m[i][j] != INT_MAX) {
                m[i][j] -= minColumn[j];
            }
        }
    }
    /*если хотя бы для одной строки / столбца матрицы не найден мин.элемент, значит из этой вершины / в эту вершину
    нет пути, и далее эту матрицу не рассматриваем */
    if (std::find(minRow.cbegin() + 1, minRow.cend(), INT_MAX) != minRow.cend() || std::find(minColumn.cbegin() + 1, minColumn.cend(), INT_MAX) != minColumn.cend()) {
        return std::nullopt;
    }
    return std::accumulate(minColumn.cbegin() + 1, minColumn.cend(), 0) + std::accumulate(minRow.cbegin() + 1, minRow.cend(), 0);
}

int BranchAndBound::calculateFine(const Matrix& m, int rowNumber, int columnNumber) const {
    int rowMin = INT_MAX;
    int columnMin = INT_MAX;
    for (size_t i = 1; i < m.size(); ++i) {
        if (i != rowNumber)
            rowMin = std::min(rowMin, m[i][columnNumber]);
        if (i != columnNumber)
            columnMin = std::min(columnMin, m[rowNumber][i]);
    }
    if (rowMin == INT_MAX || columnMin == INT_MAX) return INT_MAX;
    return rowMin + columnMin;
}

Edge BranchAndBound::getZeroElementWithMaxFine(const Matrix &m) const {
    std::list<Edge> zeroEdges;
    std::list<std::pair<int, int>> zeroVertexes;
    std::list<int> coefficients;
    int maxCoefficient = 0;
    for (size_t i = 1; i < m.size(); ++i) {
        for (size_t j = 1; j < m.size(); ++j) {
            if (m[i][j] == 0) {
                int weight = calculateFine(m, i, j);
                Edge e = { { i, j }, weight };
                zeroEdges.emplace_back(std::move(e));
            }
        }
    }
    auto edgeWithMaxFine = std::max_element(zeroEdges.cbegin(), zeroEdges.cend(), [](Edge const lhs, Edge const rhs) {
        return lhs.weight < rhs.weight;
    });
    return *edgeWithMaxFine;
}

void BranchAndBound::deleteEdges(Matrix& m, const Edge& e) const {
    m.erase(m.begin() + e.edge.first);
    for (size_t i = 0; i < m.size(); ++i) {
        m[i].erase(m[i].begin() + e.edge.second);
    }
}

/* запретить преждевременные циклы. Например, уже построен фрагмент пути 1-2, 2-3. Если далее выбрать путь
3-1, то получится цикл, поэтому надо проставить бесконечность в матрице для ребра 3-1 */
void BranchAndBound::preventCycles(Matrix& m, std::list<Edge> pathes) const {
    if (vertexesNumber - pathes.size() <= 1) return;
    bool isCycleFound = true;
    while (isCycleFound) {
        isCycleFound = false;
        for (Edge& path1 : pathes) {
            int row1 = path1.edge.first;
            int column1 = path1.edge.second;
            for (Edge& path2 : pathes) {
                int row2 = path2.edge.first;
                int column2 = path2.edge.second;
                if (row1 == column2) {
                    isCycleFound = true;
                    path2.edge.second = column1;
                    auto it = std::find_if(pathes.begin(), pathes.end(), [row1, column1](const Edge& e) {
                        return (e.edge.first == row1 && e.edge.second == column1); 
                    });
                    pathes.erase(it);
                    break;
                }
            }
            if (isCycleFound) break;
        }
    }

    for (auto& path : pathes) {
        int row = path.edge.first;
        int column = path.edge.second;
        int rowIndex = MatrixHelper::getRowIndex(m, column);
        int columnIndex = MatrixHelper::getColumnIndex(m, row);
        if (rowIndex != INT_MAX && columnIndex != INT_MAX) {
            m[rowIndex][columnIndex] = INT_MAX;
        }
    }
}

void BranchAndBound::solve(Matrix m, std::list<Edge> path, int bound) {
    
    if (bound >= lowestBound) return;
    
    if (m.size() == 1) {
        if (bound < lowestBound) {
            lowestBound = bound;
            bestPath = path;
        }
        return;
    }
    
    Edge edge = getZeroElementWithMaxFine(m);
    
    std::list<Edge> path1(path);
    Matrix m1(m);

    //идем по ребру с максимальным штрафом
    path.emplace_back(MatrixHelper::getVertexesNumbers(m, edge));
    deleteEdges(m, edge);
    preventCycles(m, path);
    if (auto reduction = reduceMatrix(m)) {
        bound += *reduction;
        solve(m, path, bound);
    }

    // не идем по ребру с максимальным штрафом
    m1[edge.edge.first][edge.edge.second] = INT_MAX;
    if (auto reduction = reduceMatrix(m1)) {
        bound += *reduction;
        solve(m1, path1, bound);
    }
}

std::list<int> BranchAndBound::extractVertexesfromEdges() const {
    std::list<int> vertexesList;
    if (!bestPath.empty()) {
        vertexesList.push_back(bestPath.front().edge.first);
    }
    for (Edge e : bestPath) {
        int lastElement = vertexesList.back();
        auto it = std::find_if(bestPath.begin(), bestPath.end(), [lastElement](const Edge& e) {
            return (e.edge.first == lastElement);
        });
        vertexesList.push_back((*it).edge.second);
    }
    return vertexesList;
} 

std::list<int> BranchAndBound::findHamiltonCycle() {
    std::list<Edge> path;
    int bound = 0;
    if (auto reduction = reduceMatrix(adjacencyMatrix)) {
        bound += *reduction;
        solve(adjacencyMatrix, path, bound);
    }
    //std::cout << "final bound is " << lowestBound << "\n";
    return extractVertexesfromEdges();
}
