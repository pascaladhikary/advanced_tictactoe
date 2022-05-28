#include "tictactoe/tictactoe.h"

#include <stdexcept>
#include <string>
#include <vector>

namespace tictactoe {

using std::string;

Board::Board(const string& board) {
  this->board = board;
  boardSize = 3;
  if (board.size() != boardSize * boardSize) {
    throw std::invalid_argument("The string provided is not a valid board.");
  }

  for (int i = 0; i < boardSize; i++) {
    string row = board.substr(boardSize * i, boardSize);
    transform(row.begin(), row.end(), row.begin(), ::tolower);
    std::vector<char> data(row.begin(), row.end());
    grid.emplace_back(data);
  }
}

/*
 * Checks the state of the board (unreachable, no winner, X wins, or O wins)
 *
 * @return an enum value corresponding to the board evaluation
 */
auto Board::EvaluateBoard() const -> BoardState {
  char piece1 = 'x';
  char piece2 = 'o';
  int countX = findCountOfPiece(piece1);
  int countO = findCountOfPiece(piece2);

  if (abs(countX - countO) > 1 || countO > countX ||
      (checkWinner(piece1) && countX == countO) ||
      (checkWinner(piece2) && countX == countO + 1)) {
    return BoardState::UnreachableState;
  } else if (checkWinner(piece1)) {
    return BoardState::Xwins;
  } else if (checkWinner(piece2)) {
    return BoardState::Owins;
  } else {
    return BoardState::NoWinner;
  }
}

/*
 * Counts for occurrences of a piece
 *
 * @param piece The piece searched , typically x or o
 * @return an int, count of the piece
 */
auto Board::findCountOfPiece(char piece) const -> int {
  int count = 0;
  for (size_t i = 0; i < board.size(); i++) {
    if (equalsIgnoreCase(board.substr(i, 1), std::string(1, piece))) {
      count++;
    }
  }
  return count;
}

/*
 * Checks if two strings are equal ignoring case
 * Taken vicariously from
 * https://stackoverflow.com/questions/11635/case-insensitive-string-comparison-in-c/4119881#4119881
 *
 * @return a boolean true if equal, false otherwise
 */
auto Board::equalsIgnoreCase(const string& a, const string& b) const -> bool {
  size_t sz = a.size();
  if (b.size() != sz) {
    return false;
  }
  for (size_t i = 0; i < sz; ++i) {
    if (tolower(a[i]) != tolower(b[i])) {
      return false;
    }
  }
  return true;
}

/*
 * Checks for a winner in TicTacToe across rows, columns, and diagonals.
 *
 * @param position The character value corresponding to the desired
 * representation i.e X or O
 * @return a boolean, true if a win has been found
 */
auto Board::checkWinner(char piece) const -> bool {
  // row & column
  int rowCount = 0, columnCount = 0;
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      if (grid[i][j] == piece) {
        rowCount++;
      }
      if (grid[j][i] == piece) {
        columnCount++;
      }
      if (rowCount == boardSize || columnCount == boardSize) {
        return true;
      }
    }
    rowCount = 0;
    columnCount = 0;
  }

  // downDiagonal
  int diagonalCount = 0;
  for (int k = 0; k < boardSize; k++) {
    if (grid[k][k] == piece) {
      diagonalCount++;
    }
  }
  if (diagonalCount == boardSize) {
    return true;
  }

  // upDiagonal
  diagonalCount = 0;
  for (int k = 0; k < boardSize; k++) {
    if (grid[k][boardSize - k - 1] == piece) {
      diagonalCount++;
    }
  }
  return diagonalCount == boardSize;
}

}  // namespace tictactoe
