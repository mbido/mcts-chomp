#include "../include/players.hpp"

namespace plyrdm {
std::pair<int, int> get_move(Chomp *game) {
  auto legal_moves = game->get_legal_moves();
  int index_max = legal_moves.size();

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, index_max - 1);

  return legal_moves[dis(gen)];
}
} // namespace plyrdm

namespace plyhrstc {
/**
 * @brief checks if the game is contained in a square.
 *
 * @param game
 * @return true
 * @return false
 */
bool is_square_contained(Chomp *game) {
  return game->m_data_heights[0] == game->m_data_widths[0];
}

/**
 * @brief checks if the game looks like a symetrical L.
 *
 * @param game
 * @return true
 * @return false
 */
bool is_symetrical_L(Chomp *game) {
  return is_square_contained(game) && game->m_data_heights[1] == 1;
}

bool is_none_symetrical_L(Chomp *game) {
  return !is_square_contained(game) && game->m_data_heights[1] == 1;
}

/**
 * @brief checks if the game is composed of only two lines of same size.
 *
 * @param game
 * @return true
 * @return false
 */
bool two_lines_same_size(Chomp *game) {
  return game->m_data_heights[0] == 2 &&
         game->m_data_widths[0] == game->m_data_widths[1];
}

/**
 * @brief checks if the game is composed of only two columns of same size.
 *
 * @param game
 * @return true
 * @return false
 */
bool two_columns_same_size(Chomp *game) {
  return game->m_data_widths[0] == 2 &&
         game->m_data_heights[0] == game->m_data_heights[1];
}

bool is_truck_pos(Chomp *game) {
  bool horizontal = game->m_data_heights[0] == 2 &&
                    game->m_data_widths[0] == game->m_data_widths[1] + 1;

  bool vertical = game->m_data_widths[0] == 2 &&
                  game->m_data_heights[0] == game->m_data_heights[1] + 1;

  return horizontal || vertical;
}

bool is_one_line_or_column(Chomp *game) {
  return game->m_data_heights[0] == 1 || game->m_data_widths[0] == 1;
}

bool only_last_piece(Chomp *game) {
  return game->m_data_widths[0] == 1 && game->m_data_heights[0] == 1;
}

/**
 * @brief evaluate a move  -> plays the move and figure if it's a winning move ?
 * a loosing move ?
 *
 * @param move the move to be perform
 * @param game the current game
 * @return int -> -1 if loosing ; 1 if winning ; 0 if we don't know
 */
int eval_move(std::pair<int, int> move, Chomp *game) {
  Chomp eval_game = *game;
  eval_game.take(move.first, move.second);

  // if the move make the game end, this is a lose !
  if (eval_game.is_game_over())
    return -2;

  // if only the last piece remainds, this is a win !
  if (only_last_piece(&eval_game))
    return 1;

  // if we have a symetrical L shape, this is a win !
  if (is_symetrical_L(&eval_game))
    return 1;

  // not symetrical L is a lose !
  if (is_none_symetrical_L(&eval_game))
    return -1;

  // if no symetrical L shape is found and the game in contained in a
  // square, that is a loose !
  if (is_square_contained(&eval_game))
    return -1;

  // two lines or two columns of same size is a lose !
  if (two_lines_same_size(&eval_game) || two_columns_same_size(&eval_game))
    return -1;

  // one line or one columns only is a lose !
  if (is_one_line_or_column(&eval_game))
    return -1;

  // a truck posisition is winning
  if (is_truck_pos(&eval_game))
    return 1;

  return 0;
}

std::pair<int, int> get_move(Chomp *game) {
  auto legal_moves = game->get_legal_moves();

  // ------------ We know easy winning moves ------------------
  // if (is_square_contained(game) && game->m_data_heights[1] > 1) {
  //   return std::make_pair<int, int>(1, 1);
  // }

  // if (game->m_data_heights[0] == 1) { // one line
  //   return std::make_pair<int, int>(0, 1);
  // }

  // if (game->m_data_widths[0] == 1) { // one line
  //   return std::make_pair<int, int>(1, 0);
  // }

  // if (two_lines_same_size(game)) {
  //   return std::make_pair<int, int>(1, game->m_data_widths[1] - 1);
  // }

  // if (two_columns_same_size(game)) {
  //   return std::make_pair<int, int>(game->m_data_heights[1] - 1, 1);
  // }

  // ------ We evaluate moves to get one of the best one ------
  auto rd = std::random_device{};
  auto rng = std::default_random_engine{rd()};

  // we shuffle the available moves
  std::shuffle(std::begin(legal_moves), std::end(legal_moves), rng);

  auto move = legal_moves[0];

  // game->display();

  // std::cout << "New thinking..." << std::endl;

  int prev_eval = -12;

  for (size_t i = 0; i < legal_moves.size(); i++) {
    auto temp_move = legal_moves[i];

    int eval = eval_move(temp_move, game);
    // std::cout << "eval : " << eval << " ; temp_move : (" << temp_move.first
    //           << ", " << temp_move.second << ")" << std::endl;

    if (eval == 1) {
      // std::cout << "plays  : (" << temp_move.first << ", " <<
      // temp_move.second
      //           << ")" << std::endl;
      return temp_move;
    }
    if (eval > prev_eval) { // we don't want losing moves
      move = temp_move;
      prev_eval = eval;
    }
  }

  // std::cout << "plays  : (" << move.first << ", " << move.second << ")"
  //           << std::endl;
  return move;
}
} // namespace plyhrstc