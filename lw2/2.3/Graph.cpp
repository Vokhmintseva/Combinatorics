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
    adjacencyMatrix.assign(vertexesNumber + 1, std::vector<int>(vertexesNumber + 1, INT_MAX));
    for (const auto& e : edges) {
        adjacencyMatrix[e.edge.first][e.edge.second] = e.weight;
        adjacencyMatrix[e.edge.second][e.edge.first] = e.weight;
    }
    
    std::iota(adjacencyMatrix[0].begin(), adjacencyMatrix[0].end(), 0);
    for (int i = 0; i < adjacencyMatrix.size(); ++i) {
        adjacencyMatrix[i][0] = i;
    }
}

void Graph::printMatrixÑoefficients(const Matrix &m, std::ostream& output) {
    for (size_t i = 0; i < m.size(); ++i) {
        for (unsigned int j = 0; j < m[i].size(); j++) {
            if (m[i][j] == INT_MAX) {;
                output << "- ";
            } else {
                output << m[i][j] << " ";
            }
        }
        output << std::endl;
    }
}

int Graph::reduceMatrix(Matrix &m) {
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
    //std::copy(minRow.begin() + 1, minRow.end(), std::ostream_iterator<int>(std::cout, " "));
    //std::cout << std::endl;
    //std::copy(minColumn.begin() + 1, minColumn.end(), std::ostream_iterator<int>(std::cout, " "));
    //printMatrixÑoefficients(m, std::cout);
    //std::cout << std::endl;
    return std::accumulate(minColumn.cbegin() + 1, minColumn.cend(), 0) + std::accumulate(minRow.cbegin() + 1, minRow.cend(), 0);
    
}

int Graph::calculateFine(const Matrix& m, int rowNumber, int columnNumber) {
    //std::cout << rowNumber << " " << columnNumber << " ";
    int rowMin = INT_MAX;
    int columnMin = INT_MAX;
    for (size_t i = 1; i < m.size(); ++i) {
        if (i != rowNumber)
            rowMin = std::min(rowMin, m[i][columnNumber]);
        if (i != columnNumber)
            columnMin = std::min(columnMin, m[rowNumber][i]);
    }
    //std::cout << rowMin + columnMin << std::endl;
    return rowMin + columnMin;
}

Edge Graph::getZeroElementWithMaxFine(const Matrix &m) {
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

void Graph::deleteEdges(Matrix& m, const Edge& e) {
    m.erase(m.begin() + e.edge.first);
    for (size_t i = 0; i < m.size(); ++i) {
        m[i].erase(m[i].begin() + e.edge.second);
    }
}

int getRowIndex(const Graph::Matrix& m, int row) {
    for (int i = 1; i < m.size(); ++i) {
        if (m[i][0] == row) {
            return i;
        }
    }
    return INT_MAX;
}

int getColumnIndex(const Graph::Matrix& m, int column) {
    auto it = std::find(m[0].begin() + 1, m[0].end(), column);
    return it != m[0].end() ? *it : INT_MAX;
}

/*void Graph::preventCycle(Matrix& m, std::list<Edge> pathes) {
    std::list<Edge> l1(pathes);

    bool isCycleFound = true;
    std::list<Edge> cycledEdges;
    std::list<Edge> l2;

    while (isCycleFound) {
        cycledEdges.clear();
        l2.clear();

        for (Edge &edge2: l1) {

            // íåò ñìûñëà îáõîäèòü óæå äîáàâëåííûå
            if (std::find(cycledEdges.begin(), cycledEdges.end(), edge2) != cycledEdges.end()) {
                continue;
            }

            for (Edge& edge1 : l1) {
                // èãíîğèğóåì ñàìè ñåáÿ
                if (edge1.edge.first == edge2.edge.first && edge1.edge.second == edge2.edge.second) {
                    continue;
                }

                // íåò ñìûñëà îáõîäèòü óæå äîáàâëåííûå
                if (std::find(cycledEdges.begin(), cycledEdges.end(), edge1) != cycledEdges.end()) {
                    continue;
                }

                if (edge2.edge.first == edge1.edge.second) {
                    Edge e;
                    e.edge.first = edge1.edge.first;
                    e.edge.second = edge2.edge.second;
                    l2.push_back(e);
                    cycledEdges.push_back(edge1);
                    cycledEdges.push_back(edge2);
                    continue;
                }
            }

            // íåò ñìûñëà îáõîäèòü óæå äîáàâëåííûå
            if (std::find(cycledEdges.begin(), cycledEdges.end(), edge2) != cycledEdges.end()) {
                continue;
            }

            l2.push_back(edge2);
        }
        l1 = l2;
        isCycleFound = !cycledEdges.empty();
    }
}*/

void Graph::preventCycles(Matrix& m, std::list<Edge> pathes) {
    std::list<Edge> pathesCopy = pathes;
    auto it = std::begin(pathes);
    //foreach($paths as $row = > $column)
    for (Edge &path : pathes) {
        int row = path.edge.first;
        int column = path.edge.second;
        
        int rowIndex = getRowIndex(m, column);
        int columnIndex = getColumnIndex(m, row);
        if (rowIndex != INT_MAX && columnIndex != INT_MAX) {
            m[columnIndex][rowIndex] = INT_MAX;
        }
        //foreach($pathCopy as $rowCopy  != > $columnCopy)
        auto itCopy = std::begin(pathesCopy);
        for (Edge pathCopy : pathesCopy) {
            int rowCopy = pathCopy.edge.first;
            int columnCopy = pathCopy.edge.second;
            if (row == columnCopy) {
                //$paths[$rowCopy] = $column;
                //unset($paths[$row]);
                itCopy->edge.second = column;
                pathes.erase(it);
                m[rowCopy][column] = INT_MAX;
                m[column][rowCopy] = INT_MAX;
                preventCycles(m, pathes);
            }
            ++itCopy;
        }
        ++it;
    }
}

std::list<Edge> Graph::testPreventCycles(std::list<Edge> p) {
    std::list<Edge> pathes = p;
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
                    auto it = std::find_if(pathes.begin(), pathes.end(), [row1, column1](const Edge& e) {return (e.edge.first == row1 && e.edge.second == column1); });
                    pathes.erase(it);
                    break;
                }
            }
            if (isCycleFound) break;
        }
    }
    return pathes;
}

Edge Graph::getRealCoordinates(const Matrix& m, const Edge& e) {
    Edge realEdge;
    realEdge.edge.first = m[e.edge.first][0];
    realEdge.edge.second = m[0][e.edge.second];
    return realEdge;
}

void Graph::solve(Matrix m, std::list<Edge> pathes, int bound) {
    bound += reduceMatrix(m);
    Edge edge = getZeroElementWithMaxFine(m);
    Edge edgeReal = getRealCoordinates(m, edge);
    Matrix m1(m);
    deleteEdges(m1, edge);
    //printMatrixÑoefficients(m1, std::cout);
    std::list<Edge> pathes1 = pathes;
    pathes1.emplace_back(edgeReal);
    preventCycles(m1, pathes1);
    
    
    std::cout << "iter 2" << std::endl;
    bound += reduceMatrix(m1);
    //printMatrixÑoefficients(m1, std::cout);
    edge = getZeroElementWithMaxFine(m1);
    edgeReal = getRealCoordinates(m1, edge);
    pathes1.emplace_back(edgeReal);
    printMatrixÑoefficients(m1, std::cout);
    preventCycles(m1, pathes1);
}

void Graph::findHamiltonCycle() {
    std::list<Edge> path;
    int bound = 0;
    
    solve(adjacencyMatrix, path, bound);
}
