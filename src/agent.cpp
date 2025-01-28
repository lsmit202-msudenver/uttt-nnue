#include "globals.h"
#include "data.h"
#include <chrono>
#include <iostream>

using namespace std;

#include "agent.h"
#include "state.h"

#define TIME_LEFT                                                              \
  duration_cast<milliseconds>(steady_clock::now() - start).count()

const int INF = -16535;

const int wins[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6},
                        {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

void visit(int);
void loadPrecomputed();

Agent::Agent() { 

  loadPrecomputed();

  visit(9841);
}

void Agent::init(steady_clock::time_point start, int timeout) {}

void Agent::readTurn() {
  int row, col;
  cin >> row >> col;

  int board, position;
  if ((row < 0) || (col < 0)) {
    // First turn, and Player is first to move
    gameState.playerToMove = PLAYER;

  } else {
    board = _toBoard(row, col), position = _toPosition(row, col);
    Action action{board, position, OPPONENT, -1};
    gameState.make(action);
  }
}

void Agent::playAction(Action const &action) {
  gameState.make(action);
  cout << action.row() << " " << action.col() << " " << endl;
}

Action Agent::selectAction(steady_clock::time_point start, int timeout) {
  int actionCount = gameState.generateMoves(actions[0]);

  int bestActionIndex = 0;
  int bestScore = -INF;

  for (int i = 0; i < actionCount /* && TIME_LEFT < timeout */; ++i) {
    gameState.make(actions[0][i]);
    int score = _traverse(MAX_DEPTH);
    gameState.unmake(actions[0][i]);

    if (score > bestScore) {
      bestScore = score;
      bestActionIndex = i;
    }
  }

  return actions[0][bestActionIndex];
}

int Agent::_traverse(int depth) {
  if (depth == 0 || gameState.isOver)
    return _evaluate();

  int actionCount = gameState.generateMoves(actions[depth]);

  int bestScore = -INF;
  for (int i = 0; i < actionCount; ++i) {
    gameState.make(actions[depth][i]);
    int score = _traverse(depth - 1);
    gameState.unmake(actions[depth][i]);

    if (score > bestScore) {
      bestScore = score;
    }
  }

  return bestScore;
}

int Agent::_evaluate() { return 1; }

void loadPrecomputed() {
  for(auto &state : endGames) {
    cache[state].isOver = true;
  }
}

void visit(int state) {
  auto &entry = cache[state];
}