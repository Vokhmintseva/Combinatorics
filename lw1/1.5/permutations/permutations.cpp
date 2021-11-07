// lexicographicalCombinations.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/timer.hpp>

void generatePermutations(std::vector<int>& range) {
    do {
        //copy(range.begin() + 1, range.end(), std::ostream_iterator<size_t>(std::cout, " "));
        //std::cout << std::endl;
    } while (std::next_permutation(range.begin() + 1, range.end()));
}

int main() {
    int n = 100;
    int k = 5;
    boost::timer t;
    t.restart();
    std::vector<int> range;
    range.push_back(-1);
    for (int i = 1; i <= k; ++i) {
        range.push_back(i);
    }
    int m = 1;
    while (m != 0) {
        generatePermutations(range);
        m = k;
        while (range[m] == n - k + m) {
            m--;
        }
        range[m]++;
        for (int i = m + 1; i <= k; ++i) {
            range[i] = range[i - 1] + 1;
        }
    }
    double duration = t.elapsed();
    std::cout << duration << std::endl;
}