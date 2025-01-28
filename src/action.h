#pragma once

struct Action {
  int board;
  int position;
  int playerToMove;
  int lastBoardToPlay;

  int row() const;
  int col() const;
  int offset() const;
  int metaOffset() const;
};
