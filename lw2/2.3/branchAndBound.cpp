// branchAndBound.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <utility>
#include "Graph.h"

bool readGraphData(std::istream& input, int& vertexesNumber, std::vector<Edge>& edges) {
    int edgesNumber = 0;
    std::string line;
    getline(input, line);
    std::istringstream istrstr(line);

    if (!(istrstr >> vertexesNumber)) {
        return false;
    }

    if (!(istrstr >> edgesNumber)) {
        return false;
    }

    int stringsCounter = 0;
    while (getline(input, line) && stringsCounter < edgesNumber) {
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

    return stringsCounter == edgesNumber;
}

void printCutPoints(std::ostream& output, const std::set<int>& cutPoints) {
    copy(cutPoints.cbegin(), cutPoints.cend(), std::ostream_iterator<int>(std::cout, " "));
}

int main(int argc, char* argv[]) {
    /*if (argc != 2) {
        std::cout << "Invalid argument count\nUsage: cutPoints.exe <input file name>\n";
        return 1;
    }

    std::string inputFileName = argv[1];*/
    std::ifstream inputFile;
    inputFile.open("file.txt");
    if (!inputFile.is_open()) {
        //std::cout << "Failed to open '" << inputFileName << "' for reading\n";
        std::cout << "Failed to open file\n";
        return 1;
    }

    std::vector<Edge> edges;
    int vertexesNumber = 0;
    if (!readGraphData(inputFile, vertexesNumber, edges)) {
        std::cout << "Incorrect input data\n";
        return 1;
    }

    Graph graph(vertexesNumber, edges);
    //graph.printMatrixСoefficients(std::cout);
    graph.findHamiltonCycle();
    //graph.printMinColumn(std::cout);
    //graph.printMinRow(std::cout);
}
