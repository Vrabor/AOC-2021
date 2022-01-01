#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool is_lowpoint(std::vector<std::string>& arr, int x, int y){
  return arr[x][y] < arr[x][y - 1] && arr[x][y] < arr[x][y + 1]
    && arr[x][y] < arr[x + 1][y] && arr[x][y] < arr[x - 1][y];
}

void pad_input(std::vector<std::string>& input){
  std::string pad(input[0].size(), '9');
  auto begin = input.begin();
  // pad at first and last line
  input.insert(begin, pad);
  input.push_back(pad);
  // pad at beginning and end of each line
  for (std::string& s : input){
    s.insert(0, "9");
    s.push_back('9');
  }
  
}

int Task1(std::vector<std::string>& input) {
  int low_sum = 0;
  for (auto i = 1; i < input.size() - 1; i++){
    for (auto j = 1; j < input[i].size() - 1; j ++){
      if (is_lowpoint(input, i, j)){
        // +1 because risk level is 1 higher than number displayed
    	low_sum += input[i][j] - '0' + 1;
      }
    }
  }
  return low_sum;
}

int main() {
  std::ifstream istrm("input.txt", std::ios::in);
  std::string buf = "";
  std::vector<std::string> input = {};
  while (std::getline(istrm, buf)) {
    input.push_back(buf);
  }

  pad_input(input);

  int solution1 = Task1(input);
  std::cout << "Task1: " << solution1 << "\n";

  return 0;
}
