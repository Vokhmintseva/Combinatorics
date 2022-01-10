// spanningTreesAmount.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "SpanningTreesCountAlgorithm.h"

bool readGraphData(std::istream& input, int& vertexesNumber, std::vector<Edge>& edges) {
    int edgesNumber = 0;
    std::string line;
    getline(input, line);
    std::istringstream istrstr(line);

    if (!(istrstr >> vertexesNumber)) {
        return false;
    }

    while (getline(input, line)) {
        std::stringstream istrstr(line);
        int vertex1, vertex2, weight = 0;
        if (istrstr >> vertex1 && istrstr >> weight && istrstr >> vertex2) {
            edges.push_back({ std::make_pair(vertex1, vertex2), weight });
        }
        else {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Invalid argument count\nUsage: spanningTreesAmount.exe <input file name>\n";
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

    SpanningTreesCountAlgorithm algorithm(vertexesNumber, edges);
    int count = algorithm.countSpanningTrees();
    std::cout << count;
}
