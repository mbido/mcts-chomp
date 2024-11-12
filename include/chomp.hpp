#ifndef CHOMP_HPP
#define CHOMP_HPP

#include <iostream>
#include <memory>
#include <random>
#include <utility>
#include <vector>

class Chomp {
public:
  // we put everything in public. Not good ? I don't care, it's faster to code
  int m_height;
  int m_width;

  // doubling the data for simpler computations
  std::vector<int> m_data_heights;
  std::vector<int> m_data_widths;

  // basic constructor
  Chomp(int height, int width)
      : m_height(height), m_width(width),
        m_data_heights(std::vector(width, height)),
        m_data_widths(std::vector(height, width)) {}

  Chomp(const Chomp &other)
      : m_height(other.m_height), m_width(other.m_width),
        m_data_heights(other.m_data_heights),
        m_data_widths(other.m_data_widths) {}

  Chomp() { Chomp(2, 2); }

  bool taken(int r, int c);
  bool take(int r, int c);
  bool is_game_over();
  std::vector<std::pair<int, int>> get_legal_moves();
  void display();
};

#endif // CHOMP_HPP