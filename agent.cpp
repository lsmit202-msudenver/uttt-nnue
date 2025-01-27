#include "globals.h"
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

Agent::Agent() { visit(9841); }

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

void visit(int state) {


  int cells[9] = {};
  bool inProgress = false;
  BoardStateProperty &cache = propertyCache[state];
  if (cache.possiblePositions > 0) {
    return;
  }

  cache = {0, 0, 1, 0, 0};

  // Load cell values + fillPosition bits
  int temp = state, fillBit = 1;
  for (int i = 0; i < 9; ++i) {
    cells[i] = (temp % 3) - 1;
    if (cells[i] == 0) {
      inProgress = true;
    } else {
      cache.filledPositions |= fillBit;
    }

    temp /= 3;
    fillBit <<= 1;
  }

  for (int combo = 0; combo < 8; ++combo) {
    if (cells[wins[combo][0]] == -1 && cells[wins[combo][1]] == -1 &&
        cells[wins[combo][2]] == -1) {
      cache.boardWinner = 0;
      cache.losablePositions = 1;
      return;
    }

    if (cells[wins[combo][0]] == 1 && cells[wins[combo][1]] == 1 &&
        cells[wins[combo][2]] == 1) {
      cache.boardWinner = 1;
      cache.winnablePositions = 1;
      return;
    }
  }

  if (inProgress) {
    cache.boardWinner = 3;
    for (int i = 0; i < 9; ++i) {
      if (cells[i] == 0) {

        state += moveIndex[i];

        visit(state);
        cache.losablePositions += propertyCache[state].losablePositions;
        cache.winnablePositions += propertyCache[state].winnablePositions;
        cache.possiblePositions += propertyCache[state].possiblePositions;

        state -= 2 * moveIndex[i];

        visit(state);
        cache.losablePositions += propertyCache[state].losablePositions;
        cache.winnablePositions += propertyCache[state].winnablePositions;
        cache.possiblePositions += propertyCache[state].possiblePositions;

        state += moveIndex[i];
      }
    }
  } else {
    cache.boardWinner = 2;
  }
}