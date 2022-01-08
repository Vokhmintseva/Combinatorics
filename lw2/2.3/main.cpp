// main.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include "BranchAndBound.h"

bool readGraphData(std::istream& input, int& vertexesNumber, std::vector<Edge>& edges) {
    int edgesNumber = 0;
    std::string line;
    getline(input, line);
    std::istringstream istrstr(line);

    if (!(istrstr >> vertexesNumber)) {
        return false;
    }

    int maxVertexesNumber = vertexesNumber * vertexesNumber - vertexesNumber;
    int stringsCounter = 0;
    while (getline(input, line)) {
        ++stringsCounter;
        std::stringstream istrstr(line);
        int vertex1, vertex2, weight = 0;
        if (istrstr >> vertex1 && istrstr >> weight && istrstr >> vertex2) {
            edges.push_back({ std::make_pair(vertex1, vertex2), weight });
        }
        else {
            return false;
        }
    }
    return stringsCounter <= maxVertexesNumber;
}

void printVertexesList(std::ostream& output, const std::list<int>& vertexesList) {
    copy(vertexesList.cbegin(), vertexesList.cend(), std::ostream_iterator<int>(std::cout, " "));
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Invalid argument count\nUsage: branchAndBound.exe <input file name>\n";
        return 1;
    }

    std::string inputFileName = argv[1];
    std::ifstream inputFile;
    inputFile.open(inputFileName);
    if (!inputFile.is_open()) {
        std::cout << "Failed to open '" << inputFileName << "' for reading\n";
        return 1;
    }

    std::vector<Edge> edges;
    int vertexesNumber = 0;
    if (!readGraphData(inputFile, vertexesNumber, edges)) {
        std::cout << "Incorrect input data\n";
        return 1;
    }

    BranchAndBound branchAndBound(vertexesNumber, edges);
    std::list<int> path = branchAndBound.findHamiltonCycle();
    printVertexesList(std::cout, path);
}