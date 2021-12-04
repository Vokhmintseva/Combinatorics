// flipbyte.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

bool readGraphData(std::istream& input, int& vertexesNumber, std::vector<std::pair<int, int>>& edges) {
    int edgesNumber = 0;
    std::string line;
    getline(input, line);
    std::stringstream istrstr(line);
    
    if (!istrstr >> vertexesNumber) {
        return false;
    }
    
    if (!istrstr >> edgesNumber) {
        return false;
    }
    
    int stringsCounter = 0;
    while (getline(input, line) && stringsCounter < edgesNumber) {
        ++stringsCounter;
        std::stringstream istrstr(line);
        int vertex1, vertex2 = 0;
        //int vertex2 = 0;
        if (istrstr >> vertex1 && istrstr >> vertex2) {
            edges.push_back(std::make_pair(vertex1, vertex2));
        } else {
            return false;
        }
    }
    
    return stringsCounter == edgesNumber;
}

int main() {
    std::ifstream inputFile;
    inputFile.open("graph-data.txt");
    if (!inputFile.is_open()) {
        std::cout << "Failed to open \"graph-data.txt\" for reading\n";
        return 1;
    }
    
    std::vector<std::pair<int, int>> edges;
    int vertexesNumber = 0;
    if (!readGraphData(std::cin, vertexesNumber, edges)) {
        std::cout << "Incorrect input data\n";
        return 1;
    }

    Graph graph(vertexesNumber, edges);
    graph.printMatrixСoeffs(std::cout);
    graph.printCutPoints(std::cout);
}