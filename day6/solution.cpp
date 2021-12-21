#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <numeric>
#include <boost/multiprecision/cpp_int.hpp>

template <class InputIterator>
void print(InputIterator start, InputIterator end)
{
    for(auto i = start; i != end; i++)
    {
        std::cout << *i << " ";
    }
    std::cout << "\n";
}

template<typename T>
T Task(std::vector<int> input, int days){
    std::array<T, 9> current_state = { 0 };
    std::array<T, 9> previous_state = { 0 };

    for (auto& i : input){
        current_state[i] += 1;
    }

    for (auto i = 0; i < days; i++){
        previous_state = current_state;
        current_state.fill(0);
        // handle normal case, just subtract 1 from everything
        for (auto j = 1; j < 9; j++){
            current_state[j - 1] += previous_state[j];
        }
        // handle case days == 0, set timer to 6 and add timers on 8
        current_state[6] += previous_state[0];
        current_state[8] += previous_state[0];
    }

    T total = 0;
    for (auto& i : current_state){
        total += i;
    }

    return total;
}

int main(){
    std::ifstream istrm("input.txt", std::ios::in);
    std::string buf;
    std::vector<int> v = {};
    while (std::getline(istrm, buf, ',')){
        int n = std::stoi(buf);
        v.push_back(n);
    }

    int task1 = Task<int>(v, 80);
    std::cout << "Task1: " << task1 << "\n";

    using namespace boost::multiprecision;

    // after some testing: unsigned long long is enough, but i'm keeping the
    // arbitrary precision anyways. Replace if you can't get boost
    cpp_int task2 = Task<cpp_int>(v, 256);
    std::cout << "Task2: " << task2 << "\n";

    return 0;
}
