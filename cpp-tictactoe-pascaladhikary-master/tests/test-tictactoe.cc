#include <tictactoe/tictactoe.h>

#include <catch2/catch.hpp>
#include <string>

using tictactoe::Board;
using tictactoe::BoardState;

TEST_CASE("Invalid string provided to constructor") {
  SECTION("String is empty") {
    REQUIRE_THROWS_AS(Board(""), std::invalid_argument);
  }

  SECTION("String is too short") {
    REQUIRE_THROWS_AS(Board("xxoooxoo"), std::invalid_argument);
  }

  SECTION("String is too long") {
    REQUIRE_THROWS_AS(Board("xxXOooxXxo"), std::invalid_argument);
  }
}

TEST_CASE("Boards with no winner") {
  SECTION("Empty board with no winner") {
    REQUIRE(Board("---------").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("Full board with no winner") {
    REQUIRE(Board("xXoOoxxXo").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("Game in progress, X moved last with no winner") {
    REQUIRE(Board("XoXoXXo--").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("Game in progress, O moved last with no winner") {
    REQUIRE(Board("xxooxo---").EvaluateBoard() == BoardState::NoWinner);
  }
}

TEST_CASE("Unreachable state") {
  SECTION("numX < numO") {
    REQUIRE(Board("xxoooooxx").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("numX > numO + 1") {
    REQUIRE(Board("xoxOxxoxx").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("numX == numO when X has three-in-a-row") {
    REQUIRE(Board("xoXxoOxo-").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("numX == numO + 1 when O has three-in-a-row") {
    REQUIRE(Board("oXooxXoxx").EvaluateBoard() == BoardState::UnreachableState);
  }
}

TEST_CASE("X wins") {
  SECTION("Vertical win") {
    REQUIRE(Board("xoxxooxxo").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("Horizontal win") {
    REQUIRE(Board("xxXOxooxo").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("Diagonal win") {
    REQUIRE(Board("xoOoXxoxx").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("X has two three in a rows") {
    REQUIRE(Board("xooxXoxoX").EvaluateBoard() == BoardState::Xwins);
  }
}

TEST_CASE("O wins") {
  SECTION("Vertical win") {
    REQUIRE(Board("oxxoxoo-x").EvaluateBoard() == BoardState::Owins);
  }

  SECTION("Horizontal win") {
    REQUIRE(Board("ooo-xxxxo").EvaluateBoard() == BoardState::Owins);
  }

  SECTION("Diagonal win") {
    REQUIRE(Board("oxxoo-xxo").EvaluateBoard() == BoardState::Owins);
  }

  SECTION("O has two three in a rows") {
    REQUIRE(Board("oxo-oxxxo").EvaluateBoard() == BoardState::Owins);
  }
}