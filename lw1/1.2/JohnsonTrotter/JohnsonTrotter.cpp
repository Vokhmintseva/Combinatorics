// JohnsonTrotter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <boost/timer.hpp>

int findMaxMobileElement(const std::vector<int>& pi, const std::map<int, int> &directions) {
    int index = -1;
    for (size_t i = 0; i < pi.size(); ++i) {
        size_t nextIndex = i + directions.at(pi[i]);
        if (nextIndex >= 0 && nextIndex < pi.size()) {
            //если элемент мобильный (по направлению стрелки стоит элемент меньше его)
            if (pi[i] > pi[nextIndex]) {
                // если еще ни один мобильный элемент не был найден
                if (index == -1) {
                    index = i;
                }
                // иначе, если предыдущий мобильный элемент меньше вновь найденного
                else {
                    if (pi[i] > pi[index]) {
                        index = i;
                    }
                }
            }
        }
    }
    return index;
}

void changeDirections(const std::vector<int>& pi, std::map<int, int>& directions, int mobileElement) {
    for (size_t i = 0; i < pi.size(); ++i) {
        if (pi[i] > mobileElement) {
            directions[pi[i]] *= (-1);
        }
    }
}

void printPermutation(const std::vector<int>& pi) {
    for (size_t i = 0; i < pi.size(); ++i) {
        std::cout << pi[i] << " ";
    }
    std::cout << std::endl;
}

void makePermutations(std::vector<int>& pi) {
    std::sort(pi.begin(), pi.end());
    std::map<int, int> directions;
    for (size_t i = 0; i < pi.size(); ++i) {
        directions.insert(std::pair<int, int>(pi[i], -1));
    }
    int mobileElementIndex = findMaxMobileElement(pi, directions);
    while (mobileElementIndex != -1) {
        int mobileElement = pi[mobileElementIndex];
        int nextIndex = mobileElementIndex + directions[pi[mobileElementIndex]];
        std::swap(pi[mobileElementIndex], pi[nextIndex]);
        changeDirections(pi, directions, mobileElement);
        //printPermutation(pi);
        mobileElementIndex = findMaxMobileElement(pi, directions);
    }
}

int main() {
    std::vector<int> pi;
    int number;
    while (std::cin >> number) {
        pi.push_back(number);
    }
    boost::timer t;
    t.restart();
    makePermutations(pi);
    std::cout << t.elapsed() << std::endl;
}