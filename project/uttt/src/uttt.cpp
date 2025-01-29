#include <chrono>

using namespace std::chrono;

#include "action.h"
#include "agent.h"
#include "globals.h"

const int INIT_TIMEOUT_MILLISECONDS = 850;
constexpr int MOVE_TIMEOUT_MILLISECONDS = 100;

int _toBoard(int row, int col) { return (row) / 3 * 3 + (col) / 3; }

int _toPosition(int row, int col) { return (row) % 3 * 3 + (col) % 3; }

int main() {
  // First Turn
  Agent agent{};
  agent.init(steady_clock::now(), INIT_TIMEOUT_MILLISECONDS);

  // game loop
  while (true) {
    agent.readTurn();
    Action best = agent.selectAction(steady_clock::now(), MOVE_TIMEOUT_MILLISECONDS);
    agent.playAction(best);
  }

  return 0;
}
