#pragma once

#include "action.h"

struct BoardStateProperty
{

  int wins = 0;
  int losses = 0;
  int draws = 0;
  int possible = 0;

  int playerBoard = 0;
  int opponentBoard = 0;

  int bitBoard() const { return playerBoard | opponentBoard; }

  bool isOver = false;
};

struct State
{
  int boards[10] = {9841, 9841, 9841, 9841, 9841, 9841, 9841, 9841, 9841, 9841};
  int playerToMove = 0;
  int boardToPlay = -1;
  bool isOver = false;
  void make(Action const &);
  void unmake(Action const &);
  int generateMoves(Action *);
};

extern BoardStateProperty cache[19683];
