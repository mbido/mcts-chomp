#include "../include/chomp.hpp"
#include "../include/players.hpp"
#include <fstream>

void displayDoubles(const std::vector<double> &values) {
  for (const auto &value : values) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
}

void displayPairs(const std::vector<std::pair<int, int>> &pairs) {
  for (const auto &p : pairs) {
    std::cout << "(" << p.first << ", " << p.second << ") ";
  }
  std::cout << std::endl;
}

bool start_game(std::pair<int, int> (*get_move_p0)(Chomp *),
                std::pair<int, int> (*get_move_p1)(Chomp *), Chomp *game) {
  // returns true if player 0 won

  auto our_game = *game; // coping so does not change the real game
  int current_player = 0;
  while (!our_game.is_game_over()) {
    if (current_player) {
      auto move = get_move_p1(&our_game);
      our_game.take(move.first, move.second);
    } else {
      auto move = get_move_p0(&our_game);
      our_game.take(move.first, move.second);
    }
    current_player ^= 1;
  }

  return !current_player;
}

double win_rate(std::pair<int, int> (*get_move_p0)(Chomp *),
                std::pair<int, int> (*get_move_p1)(Chomp *), Chomp *game,
                int repeat) {
  double res = 0;

#pragma omp parallel for schedule(dynamic)
  for (int i = 0; i < repeat; i++) {
    if (start_game(get_move_p0, get_move_p1, game)) {
      res++;
    }
  }
  return res / repeat;
}

std::vector<double> map_games(std::pair<int, int> (*get_move_p0)(Chomp *),
                              std::pair<int, int> (*get_move_p1)(Chomp *),
                              int max_size) {
  auto res = std::vector<double>();
  int n = 10000;
  for (int height = 2; height < max_size; height++) {
    for (int width = 1; width < height; width++) {
      Chomp game(height, width);
      auto wr = win_rate(get_move_p0, get_move_p1, &game, n);
      std::cout << "for game of size " << height << "x" << width << " : "
                << wr * 100 << "%\n";
      res.push_back(wr);
    }
  }
  return res;
}

void saveToFile(const std::vector<double> &values, const std::string &filename,
                const std::string &games_name) {
  std::ofstream outFile(filename);
  if (outFile.is_open()) {
    outFile << games_name << ";";
    for (const auto &value : values) {
      outFile << value << ";";
    }
    outFile << std::endl;
    outFile.close();
  } else {
    std::cerr << "Unable to open file";
  }
}

int main() {
  // auto map = map_games(&plyrdm::get_move, &plyrdm::get_move, 20);
  // saveToFile(map, "output.txt", "plyrdm");

  int width = 15;
  int height = 20;

  int repeat = 50000;

  double rate;

  Chomp game(height, width);
  rate = win_rate(&plyrdm::get_move, &plyrdm::get_move, &game, repeat);
  std::cout << "R begin vs R : " << rate * 100 << "%\n";

  game.reset(height, width);
  rate = win_rate(&plyhrstc::get_move, &plyrdm::get_move, &game, repeat);
  std::cout << "H begin vs R : " << rate * 100 << "%\n";

  game.reset(height, width);
  rate = win_rate(&plyrdm::get_move, &plyhrstc::get_move, &game, repeat);
  std::cout << "R begin vs H : " << rate * 100 << "%\n";

  game.reset(height, width);
  rate = win_rate(&plyhrstc::get_move, &plyhrstc::get_move, &game, repeat);
  std::cout << "H begin vs H : " << rate * 100 << "%\n";

  // game.take(2, 1);
  // // game.display();
  // auto move = plyhrstc::get_move(&game);
  // game.take(move.first, move.second);
  // // std::cout << "plays  : (" << move.first << ", " << move.second << ")"
  // //           << std::endl;
  // game.display();
  // std::cout << "m_data_widths[0] : " << game.m_data_widths[0]
  //           << " ; m_data_heights[0] : " << game.m_data_heights[0] <<
  //           std::endl;
  // if (game.m_data_widths[0] == 1 || game.m_data_heights[0] == 1) {
  //   printf("BAD MOVE !\n");
  // } else {
  //   printf("not a bad move\n");
  // }

  return 0;
}