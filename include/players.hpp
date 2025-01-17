#ifndef PLAYERS_H
#define PLAYERS_H

#include "chomp.hpp"

/**
 * @brief This is the most basic player that plays at random.
 * The player ask for every legal moves and takes one with an uniform proba.
 */
namespace plyrdm {
std::pair<int, int> get_move(Chomp *game);
}

/**
 * @brief This is a player that plays with heuristics only.
 *
 */
namespace plyhrstc {
std::pair<int, int> get_move(Chomp *game);
}

#endif // PLAYERS_H