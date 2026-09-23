#include "Board.h"
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>


int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    constexpr int width = 10, height = 10, mines = 10;

    Board board(width, height, mines);

    std::cout << "Сапер\n";
    std::cout << "Команды:\n";
    std::cout << "o (x, y) - открыть клетку\n";
    std::cout << "f (x, y) - поставить/снять флаг\n";
    std::cout << "q        - выйти\n";

    std::string line;
    while (board.getState() == GameState::Progress) {
        board.print();
        std::cout << "\nВведите команду: ";

        if (!std::getline(std::cin, line)) {
            break;
        }

        std::stringstream ss(line);
        std::string command;
        if (!(ss >> command)) {
            continue;
        }

        if (command == "q") {
            std::cout << "Игра прервана\n";
            return 0;
        }

        int x = 0;
        int y = 0;
        if (!(ss >> x >> y)) {
            std::cout << "Ошибка!\n";
            continue;
        }

        bool success = false;
        if (command == "o" || command == "r") {
            success = board.revealCell(x, y);
        } else if (command == "f") {
            success = board.toggleFlag(x, y);
        } else {
            std::cout << "Неизвестная команда\n";
            continue;
        }

        if (!success) {
            std::cout << "Некорректный ход!\n";
        }
    }

    std::cout << "\nФинальное поле:\n";
    board.print(true);

    if (board.getState() == GameState::Win) {
        std::cout << "\nВы победили!\n";
    } else if (board.getState() == GameState::Lost) {
        std::cout << "\nВы проиграли!\n";
    }
}
