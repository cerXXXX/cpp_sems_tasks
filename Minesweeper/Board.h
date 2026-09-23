#pragma once
#include <vector>


enum class GameState {
    Progress,
    Win,
    Lost
};


struct Cell {
    bool isMine = false;
    bool isRevealed = false;
    bool isFlagged = false;
    int adjacentMines = 0;
};


class Board {
public:
    Board(int width, int height, int totalMines);

    GameState getState() const;
    bool revealCell(int x, int y);
    bool toggleFlag(int x, int y);
    void print(bool revealAll = false) const;

private:
    int _width;
    int _height;
    GameState _state = GameState::Progress;

    std::vector<std::vector<Cell>> _grid;

    bool isInBounds(int x, int y) const;
    void placeMines(int totalMines);
    void checkWin();
};
