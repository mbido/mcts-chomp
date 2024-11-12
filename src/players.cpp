#include "../include/players.hpp"

namespace plyrdm {
// first player -> player-random

std::pair<int, int> get_move(Chomp *game) {
  auto legal_moves = game->get_legal_moves();
  int index_max = legal_moves.size();

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, index_max - 1);

  return legal_moves[dis(gen)];
}

} // namespace plyrdm