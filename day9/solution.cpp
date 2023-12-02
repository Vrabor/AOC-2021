#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

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

int walk_basin(std::vector<std::string>& input, int x, int y) {
  if (input[x][y] == '9') {
	// 9s do not belong to the basin
	return 0;
  }
  // own point is part of basin
  int size = 1;

  // don't count current point anymore
  input[x][y] = '9';

  size += walk_basin(input, x - 1, y);
  size += walk_basin(input, x, y - 1); 
  size += walk_basin(input, x + 1, y);
  size += walk_basin(input, x, y + 1);

  return size;
}

std::vector<int> get_basins(std::vector<std::string>& input) {
  std::vector<int> basins {};
  for (auto i = 1; i < input.size() - 1; i++){
    for (auto j = 1; j < input[i].size() - 1; j ++){
      if (is_lowpoint(input, i, j)){
		basins.push_back(walk_basin(input, i, j));
      }
    }
  }
  return basins;
}

int Task2(std::vector<std::string>& input) {
    auto basins = get_basins(input);
    std::sort(basins.begin(), basins.end(), std::greater<int>());

    return basins[0] * basins[1] * basins[2];
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

  int solution2 = Task2(input);
  std::cout << "Task2: " << solution2 << "\n";

  return 0;
}
