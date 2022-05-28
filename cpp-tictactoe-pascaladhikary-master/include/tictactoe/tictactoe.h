#pragma once

#include <string>
#include <vector>

namespace tictactoe {

/**
 * This enumeration specifies the possible results of the evaluation of a
 * Tic-Tac-Toe board.
 */
enum class BoardState {
  NoWinner,
  Xwins,
  Owins,
  UnreachableState,
};

/**
 * This class can store a Tic-Tac-Toe board and evaluate its state.
 */
class Board {
 public:
  /**
   * Constructs a Board from a string consisting of 9 characters in row-major
   * order (i.e. the first three characters specify the first row).
   *
   * An 'X' or 'x' represents that the corresponding square is filled with an X,
   * an 'O' or 'o' represents that the corresponding square is filled with an O,
   * and any other character represents that the corresponding square is empty.
   *
   * This method throws a std::invalid_argument exception if the string provided
   * is not a valid board.
   */
  explicit Board(const std::string& board);

  /**
   * Evaluates the state of the board.
   */
  auto EvaluateBoard() const -> BoardState;

 private:
  int boardSize;
  std::string board;
  std::vector<std::vector<char>> grid;
  auto findCountOfPiece(char piece) const -> int;
  auto equalsIgnoreCase(const std::string& a, const std::string& b) const
      -> bool;
  auto checkWinner(char piece) const -> bool;
};

}  // namespace tictactoe
