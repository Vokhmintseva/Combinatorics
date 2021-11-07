// Narayana.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/timer.hpp>

int main()
{
    std::vector<size_t> v = { 7, 1, 12, 5, 9, 20, 15, 2, 18, 10 };
    boost::timer t;
    t.restart();
    std::sort(v.begin(), v.end());
    do
    {
        //copy(v.begin(), v.end(), std::ostream_iterator<size_t>(std::cout, " "));
        //std::cout << std::endl;
    } while (std::next_permutation(v.begin(), v.end()));
    double duration = t.elapsed();
    std::cout << duration << std::endl;
    return 0;
}
