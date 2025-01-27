#include "state.h"

BoardStateProperty propertyCache[19683]{};

void State::make(Action const &action) {
  boards[action.board] += action.offset();

  if (propertyCache[boards[action.board]].isOver()) {
    boards[9] += action.metaOffset();
  }

  if (propertyCache[boards[action.position]].isOver()) {
    boardToPlay = -1;
  } else {
    boardToPlay = action.position;
  }

  playerToMove ^= 1;
}

void State::unmake(Action const &action) {
  playerToMove ^= 1;

  boardToPlay = action.lastBoardToPlay;

  if (propertyCache[boards[action.board]].isOver()) {
    boards[9] -= action.metaOffset();
  }

  boards[action.board] -= action.offset();
}

int State::generateMoves(Action *actions) {
  int actionCount = 0;

  // First Move	or Closed Board choice
  if (boardToPlay < 0) {
    // Check all boards
    int boardsFilled = propertyCache[boards[9]].filledPositions;

    for (int board = 0, boardMask = 1; board < 9; board++, boardMask <<= 1) {
      if (boardsFilled & boardMask)
        continue;

      int positionsFilled = propertyCache[boards[board]].filledPositions;

      for (int position = 0, positionMask = 1; position < 9;
           position++, positionMask <<= 1) {
        if (positionsFilled & positionMask)
          continue;

        actions[actionCount++] = {board, position, playerToMove, -1};
      }
    }
  } else {
    int positionsFilled = propertyCache[boards[boardToPlay]].filledPositions;

    for (int position = 0, positionMask = 1; position < 9;
         ++position, positionMask <<= 1) {
      if (positionsFilled & positionMask)
        continue;

      actions[actionCount++] = {boardToPlay, position, playerToMove,
                                boardToPlay};
    }
  }

  return actionCount;
}
