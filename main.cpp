#include <iostream>

bool win_check(bool matrix[10][10]) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (matrix[i][j]) return false;
        }
    }
    return true;
}

bool check_boundary(int x, int y) {
    if (x < 0 || x > 9 || y < 0 || y > 9) {
        return false;
    }
    return true;
}

bool check_input(bool matrix[10][10], int x1, int x2, int y1, int y2, int deck) {
    int result = abs(x2 - x1) + abs(y2 - y1);
    if (x1 > x2 || y1 > y2 || !check_boundary(x1, x2) || !check_boundary(y1, y2) || result != deck) {
        return false;
    }
    for (int i = x1; i <= x2; ++i) {
        for (int j = y1; j <= y2; ++j) {
            if (matrix[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void ships_init(bool matrix[10][10]) {
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    for (int i = 0; i < 4; ++i) {
        for (int k = 4 - i; k > 0; --k) {
            if (i == 0) {
                std::cout << "Input the position of the single-deck ship: ";
                std::cin >> x1 >> y1;
                x2 = x1;
                y2 = y1;
            } else {
                std::cout << "Input the position of the " << i + 1 << "-deck ship (x1, y1, x2, y2): ";
                std::cin >> x1 >> y1 >> x2 >> y2;
            }
            while (!check_input(matrix, x1, x2, y1, y2, i)) {
                std::cout << "Wrong input. Try again: ";
                if (i == 0) {
                    std::cin >> x1 >> y1;
                    x2 = x1;
                    y2 = y1;
                } else {
                    std::cin >> x1 >> x2 >> y1 >> y2;
                }
            }
            for (int l = x1; l <= x2; ++l) {
                for (int j = y1; j <= y2; ++j) {
                    matrix[l][j] = true;
                }
            }
        }
    }
}

void shot(bool matrix[10][10], int x, int y) {
    if (matrix[x][y]) {
        std::cout << "Hit it!" << std::endl;
        matrix[x][y] = false;
    } else {
        std::cout << "Missed!" << std::endl;
    }
}

int main() {
    bool players[2][10][10];
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 2; ++k) {
                players[k][i][j] = false;
                players[k][i][j] = false;
            }
        }
    }
    for (int i = 0; i < 2; ++i) {
        std::cout << "Player " << i + 1 << " set up the ships." << std::endl;
        ships_init(players[i]);
    }

    bool winner = false;
    int x, y;
    while (!winner) {
        for (int i = 0; i < 2; ++i) {
            std::cout << "Player " << i + 1 << " take the shot: ";
            std::cin >> x >> y;
            while (!check_boundary(x, y)) {
                std::cout << "Wrong input. Try again: ";
                std::cin >> x >> y;
            }
            shot(players[1 - i], x, y);
            winner = win_check(players[1 - i]);
            if (winner) {
                std::cout << "Winner is player " << i + 1;
                return 0;
            }
        }
    }
}