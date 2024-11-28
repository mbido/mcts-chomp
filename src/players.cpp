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

std::pair<int, int> get_move_glouton(Chomp *game) {
  auto legal_moves = game->get_legal_moves();
  for (const auto &move : legal_moves) {
    Chomp temp_game = *game;
    temp_game.take(move.first, move.second);
    if (temp_game.is_game_over()) {
      return move;
    }
  }
  return legal_moves[0];
}

} // namespace plyrdm
