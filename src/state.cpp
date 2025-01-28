#include "state.h"

BoardStateProperty cache[19683]{};

void State::make(Action const &action)
{
  boards[action.board] += action.offset();

  if (cache[boards[action.board]].isOver)
  {
    boards[9] += action.metaOffset();
  }

  if (cache[boards[action.position]].isOver)
  {
    boardToPlay = -1;
  }
  else
  {
    boardToPlay = action.position;
  }

  playerToMove ^= 1;
}

void State::unmake(Action const &action)
{
  playerToMove ^= 1;

  boardToPlay = action.lastBoardToPlay;

  if (cache[boards[action.board]].isOver)
  {
    boards[9] -= action.metaOffset();
  }

  boards[action.board] -= action.offset();
}

int State::generateMoves(Action *actions)
{
  int actionCount = 0;

  // First Move	or Closed Board choice
  if (boardToPlay < 0)
  {
    // Check all boards
    int metaBitBoard = cache[boards[9]].bitBoard();

    for (int board = 0, metaMask = 1; board < 9; ++board, metaMask <<= 1)
    {
      if (metaBitBoard & metaMask)
        continue;

      int bitBoard = cache[boards[board]].bitBoard();

      for (int position = 0, mask = 1; position < 9; ++position, mask <<= 1)
      {
        if (bitBoard & mask)
          continue;

        actions[actionCount++] = {board, position, playerToMove, -1};
      }
    }
  }
  else
  {
    int bitBoard = cache[boards[boardToPlay]].bitBoard();

    for (int position = 0, mask = 1; position < 9; ++position, mask <<= 1)
    {
      if (bitBoard & mask)
        continue;

      actions[actionCount++] = {boardToPlay, position, playerToMove, boardToPlay};
    }
  }
  return actionCount;
}
