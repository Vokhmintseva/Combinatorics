// randomPermutation.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <algorithm>

int getRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void randomShuffle(std::vector<int>::iterator first, std::vector<int>::iterator last) {
    int min = *first;
    int max = *(last - 1);
    int n = last - first;
    for (int i = n - 1; i >= 0; --i) {
        std::swap(first[i], first[getRandomNumber(min, max)]);
    }
}

int main() {
    std::srand((unsigned int) time(NULL));
    std::vector<int> numbers;
    int number;
    while (std::cin >> number) {
        numbers.push_back(number);
    }

    //массив индексов в произвольном порядке
    std::vector<int>indexes(numbers.size());
    int x = 0;
    std::generate(indexes.begin(), indexes.end(), [&] { return x++; });
    randomShuffle(indexes.begin(), indexes.end());
    
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::swap(numbers[i], numbers[indexes[i]]);
    }

    for (int i: numbers) {
        std::cout << i << " ";
    }
}