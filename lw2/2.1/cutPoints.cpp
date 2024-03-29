﻿// flipbyte.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <utility>

bool readGraphData(std::istream& input, int& vertexesNumber, std::vector<std::pair<int, int>>& edges) {
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
        int vertex1, vertex2 = 0;
        if (istrstr >> vertex1 && istrstr >> vertex2) {
            edges.push_back(std::make_pair(vertex1, vertex2));
        } else {
            return false;
        }
    }
    
    return stringsCounter == edgesNumber;
}

void printCutPoints(std::ostream& output, const std::set<int> &cutPoints) {
    copy(cutPoints.cbegin(), cutPoints.cend(), std::ostream_iterator<int>(std::cout, " "));
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Invalid argument count\nUsage: cutPoints.exe <input file name>\n";
        return 1;
    }
    
    std::string inputFileName = argv[1];
    std::ifstream inputFile;
    inputFile.open(inputFileName);
    if (!inputFile.is_open()) {
        std::cout << "Failed to open '" << inputFileName << "' for reading\n";
        return 1;
    }
    
    std::vector<std::pair<int, int>> edges;
    int vertexesNumber = 0;
    if (!readGraphData(inputFile, vertexesNumber, edges)) {
        std::cout << "Incorrect input data\n";
        return 1;
    }

    Graph graph(vertexesNumber, edges);
    std::set<int> cutPoints = graph.getCutPoints();
    printCutPoints(std::cout, cutPoints);
}