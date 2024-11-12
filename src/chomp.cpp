#include "../include/chomp.hpp"

bool Chomp::taken(int r, int c) {
  if (r >= m_height || c >= m_width)
    return false;
  return m_data_heights[c] <= r;
}

bool Chomp::take(int r, int c) {
  if (taken(r, c))
    return false;

  // update m_data_heights
  for (int i = c; i < m_width; i++) {
    if (m_data_heights[i] <= r) {
      // std::cout << "hello1\n";
      break;
    }
    m_data_heights[i] = r;
  }

  // update m_data_widths
  for (int i = r; i < m_height; i++) {
    if (m_data_widths[i] <= c) {
      // std::cout << "hello2\n";
      break;
    }
    m_data_widths[i] = c;
  }
  return true;
}

bool Chomp::is_game_over() { return m_data_heights[0] == 0; }

std::vector<std::pair<int, int>> Chomp::get_legal_moves() {
  auto res = std::vector<std::pair<int, int>>();
  for (int r = 0; r < m_height; r++) {
    for (int c = 0; c < m_data_widths[r]; c++) {
      res.push_back(std::make_pair(r, c));
    }
  }
  return res;
}

void Chomp::display() {
  for (int r = 0; r < m_height; r++) {
    for (int c = 0; c < m_width; c++) {
      if (taken(r, c))
        std::cout << ".";
      else
        std::cout << "X";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}