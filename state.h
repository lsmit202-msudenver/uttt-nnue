#pragma once

#include "action.h"

struct BoardStateProperty {

  int winnablePositions;
  int losablePositions;
  int possiblePositions;

  // nth bit is set if position n is filled.
  int filledPositions;

  // 0 == Opponent, 1 == Player, 2 == Tie, 3 == In Progress
  int boardWinner;

  int isOver() const { return boardWinner < 2; }
};

struct State {
  int boards[10] = {9841, 9841, 9841, 9841, 9841, 9841, 9841, 9841, 9841, 9841};
  int playerToMove = 0;
  int boardToPlay = -1;
  bool isOver = false;
  void make(Action const &);
  void unmake(Action const &);
  int generateMoves(Action *);
};

extern BoardStateProperty propertyCache[19683];
