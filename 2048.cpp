#include <iostream>
#include <vector>
#include <random>

using namespace std;

const int BOARD_SIZE = 4;

class Game2048{
private:
    vector<vector<int>> board;

public:
    Game2048() {
        board = vector<vector<int>>(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
        add_random_tile();
        add_random_tile();
    }

    void print_board() {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    void add_random_tile() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, 2);

        int i = dist(gen);
        int j = dist(gen);

        while (board[i][j] != 0) {
            i = dist(gen);
            j = dist(gen);
        }

        board[i][j] = 2;
    }

    void move_up() {
        for (int i = 1; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] != 0) {
                    int k = i - 1;
                    while (k >= 0 && board[k][j] == 0) {
                        board[k][j] = board[i][j];
                        board[i][j] = 0;
                        k--;
                    }
                }
            }
        }
    }

    void move_down() {
        for (int i = BOARD_SIZE - 2; i >= 0; i--) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] != 0) {
                    int k = i + 1;
                    while (k < BOARD_SIZE && board[k][j] == 0) {
                        board[k][j] = board[i][j];
                        board[i][j] = 0;
                        k++;
                    }
                }
            }
        }
    }

    void move_left() {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 1; j < BOARD_SIZE; j++) {
                if (board[i][j] != 0) {
                    int k = j - 1;
                    while (k >= 0 && board[i][k] == 0) {
                        board[i][k] = board[i][j];
                        board[i][j] = 0;
                        k--;
                    }
                }
            }
        }
    }

    void move_right() {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = BOARD_SIZE - 2; j >= 0; j--) {
                if (board[i][j] != 0) {
                    int k = j + 1;
                    while (k < BOARD_SIZE && board[i][k] == 0) {
                        board[i][k] = board[i][j];
                        board[i][j] = 0;
                        k++;
                    }
                }
            }
        }
    }

    bool is_game_over() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                return false;
            } else if (j > 0 && board[i][j] == board[i][j - 1]) {
                return false;
            } else if (i > 0 && board[i][j] == board[i - 1][j]) {
                return false;
            }
        }
    }

    return true;
}
int main() {
    Game2048 game;

    while (!game.is_game_over()) {
        game.print_board();

        char move;
        cout << "Enter move (W, A, S, D): ";
        cin >> move;

        switch (move) {
            case 'W':
                game.move_up();
                break;
            case 'A':
                game.move_left();
                break;
            case 'S':
                game.move_down();
                break;
            case 'D':
                game.move_right();
                break;
            default:
                cout << "Invalid move!" << endl;
        }

        game.add_random_tile();
    }

    game.print_board();
    cout << "Game over!" << endl;

    return 0;
}
};
