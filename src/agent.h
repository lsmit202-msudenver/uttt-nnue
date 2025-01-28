#pragma once

#include <chrono>

using namespace std::chrono;
constexpr steady_clock::time_point now;

const unsigned int MAX_DEPTH = 5;

#include "action.h"
#include "state.h"

/* Why opponent as player "0"?
        - Arena input assumes opponent played first as default.
        - To set up endgame, and NNUE where 1 = we win. 0 = we lose.
 */

#define OPPONENT 0
#define PLAYER 1

struct Agent {
  State gameState;

  Action actions[MAX_DEPTH + 1][81] = {};

  int gamePly = 0;

  Agent();

  void init(steady_clock::time_point, int);
  void readTurn();
  Action selectAction(steady_clock::time_point, int);
  void playAction(Action const &);

  int _traverse(int);
  int _evaluate();
};

