#include "action.h"

#include "globals.h"

const int playerIndex[2] = {-1, 1};

int Action::row() const { return (board) / 3 * 3 + (position) / 3; }

int Action::col() const { return (board) % 3 * 3 + (position) % 3; }

int Action::offset() const { return moveIndex[position] * playerIndex[playerToMove]; }

int Action::metaOffset() const { return moveIndex[board] * playerIndex[playerToMove]; }
