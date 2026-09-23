#include "Board.h"
#include <iostream>
#include <cstdlib>


Board::Board(int width, int height, int totalMines)
    : _width(width),
      _height(height),
      _grid(height, std::vector<Cell>(width)) {
    placeMines(totalMines);
}


GameState Board::getState() const {
    return _state;
}


bool Board::isInBounds(int x, int y) const {
    return x >= 0 && x < _width && y >= 0 && y < _height;
}


void Board::placeMines(int totalMines) {
    int placed = 0;
    while (placed < totalMines) {
        int x = rand() % _width;
        int y = rand() % _height;

        if (!_grid[y][x].isMine) {
            _grid[y][x].isMine = true;
            ++placed;

            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0) {
                        continue;
                    }
                    int nx = x + dx;
                    int ny = y + dy;
                    if (isInBounds(nx, ny)) {
                        ++_grid[ny][nx].adjacentMines;
                    }
                }
            }
        }
    }
}


bool Board::revealCell(int x, int y) {
    if (!isInBounds(x, y) || _state != GameState::Progress) {
        return false;
    }

    Cell& cell = _grid[y][x];
    if (cell.isRevealed || cell.isFlagged) {
        return true;
    }

    cell.isRevealed = true;

    if (cell.isMine) {
        _state = GameState::Lost;
        return true;
    }

    // Если вокруг нет мин, рекурсивно открываем соседей
    if (cell.adjacentMines == 0) {
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                revealCell(x + dx, y + dy);
            }
        }
    }

    checkWin();
    return true;
}


bool Board::toggleFlag(int x, int y) {
    if (!isInBounds(x, y) || _state != GameState::Progress) {
        return false;
    }

    Cell& cell = _grid[y][x];
    if (!cell.isRevealed) {
        cell.isFlagged = !cell.isFlagged;
    }
    return true;
}


void Board::checkWin() {
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            if (!_grid[y][x].isMine && !_grid[y][x].isRevealed) {
                return;
            }
        }
    }
    _state = GameState::Win;
}


void Board::print(bool revealAll) const {
    std::cout << "  ";
    for (int x = 0; x < _width; ++x) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    for (int y = 0; y < _height; ++y) {
        std::cout << y << ' ';
        for (int x = 0; x < _width; ++x) {
            const Cell& cell = _grid[y][x];
            if (revealAll && cell.isMine) {
                std::cout << "* ";
            } else if (cell.isFlagged) {
                std::cout << "F ";
            } else if (!cell.isRevealed) {
                std::cout << ". ";
            } else if (cell.isMine) {
                std::cout << "* ";
            } else if (cell.adjacentMines > 0) {
                std::cout << cell.adjacentMines << ' ';
            } else {
                std::cout << "  ";
            }
        }
        std::cout << '\n';
    }
}
