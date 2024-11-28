#ifndef PLAYERS_H
#define PLAYERS_H

#include "chomp.hpp"

namespace plyrdm {
std::pair<int, int> get_move(Chomp *game);
std::pair<int, int> get_move_glouton(Chomp *game);
}

#endif // PLAYERS_H
