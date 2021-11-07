// lexicographicalCombinations.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/timer.hpp>

void printSubset(std::vector<int>& range) {
    for (size_t i = 0; i < range.size(); ++i) {
        if (range[i] == 1) {
            std::cout << i + 1 << " ";
        }
    }
    std::cout << "\n";
}

int main() {
    int n = 20;
    boost::timer t;
    t.restart();
    std::vector<int> range;
    for (int i = 0; i <= n; ++i) {
        range.push_back(0);
    }
    while (range[n] != 1) {
        //printSubset(range);
        int i = 0;
        while (range[i] == 1) {
            range[i] = 0;
            i++;
        }
        range[i] = 1;
    }
    double duration = t.elapsed();
    std::cout << duration << std::endl;
}