#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

static std::map<char, int> corrupted_LUT{{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
static std::map<char, int> missing_LUT{{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};

int check_corrupted(std::string line) {
  std::vector<char> stack{};
  for (auto& ch : line) {
    switch (ch) {
      case '(':
        stack.push_back(')');
        break;
      case '[':
        stack.push_back(']');
        break;
      case '{':
        stack.push_back('}');
        break;
      case '<':
        stack.push_back('>');
        break;
      case ')':
      case ']':
      case '}':
      case '>': {
        if (ch == stack.back()) {
          stack.pop_back();
        } else {
          return corrupted_LUT[ch];
        }
      }; break;
      default:
	std::cout << "Encountered non-brace character: " << ch << "\n";
        throw std::runtime_error("Input contains non-brace character");
    }
  }
  return 0;
}

int Task1(std::vector<std::string> input) {
  int points{0};
  for (auto& s : input) {
    points += check_corrupted(s);
  }
  return points;
}

int64_t check_missing(std::string line) {
  std::vector<char> stack{};
  for (auto& ch : line) {
    switch (ch) {
      case '(':
        stack.push_back(')');
        break;
      case '[':
        stack.push_back(']');
        break;
      case '{':
        stack.push_back('}');
        break;
      case '<':
        stack.push_back('>');
        break;
      case ')':
      case ']':
      case '}':
      case '>': {
        if (ch == stack.back()) {
          stack.pop_back();
        } else {
          // line corrupted
          return -1;
        }
      }; break;
      default:
	    std::cout << "Encountered non-brace character: " << ch << "\n";
        throw std::runtime_error("Input contains non-brace character");
    }
  }
  int64_t score { 0 };
  for (auto i = stack.rbegin(); i < stack.rend(); i++){
      score *= 5;
      score += missing_LUT[*i];
  }
  return score;
}

int64_t Task2(std::vector<std::string> input) { 
  std::vector<int64_t> scores {};
  for (auto& s : input) {
    scores.push_back(check_missing(s));
  }
  // remove all corrupted lines
  auto removed = std::remove(scores.begin(), scores.end(), -1);
  scores.erase(removed, scores.end());
  std::sort(scores.begin(), scores.end());
  for (auto& s : scores){
      std::cout << s << " ";
  }
  std::cout << "\n";
  return scores[scores.size() / 2];
}

int main() {
  std::ifstream istrm("input.txt", std::ios::in);
  std::string buf = "";
  std::vector<std::string> input{};
  while (std::getline(istrm, buf)) {
    input.push_back(buf);
  }

  int solution1 = Task1(input);
  std::cout << "Task1: " << solution1 << "\n";

  int64_t solution2 = Task2(input);
  std::cout << "Task2: " << solution2 << "\n";

  return 0;
}
