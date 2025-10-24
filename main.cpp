#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int W = 20;
const int H = 20;

bool gameOver;
int headX, headY;
int foodX, foodY;
int score;
int tailX[100], tailY[100];
int tailLength;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

void Setup() {
    gameOver = false;
    dir = STOP;
    headX = W / 2;
    headY = H / 2;
    foodX = 1 + rand() % (W - 2);
    foodY = 1 + rand() % (H - 2);
    score = 0;
    tailLength = 0;

    cout << "=== SNAKE GAME ===" << endl;
    cout << "Usa WASD para moverte, Q para salir." << endl;
    cout << "Presiona cualquier tecla para comenzar..." << endl;
    _getch();
}

void Draw() {
    system("cls");
    for (int i = 0; i < W + 2; i++) cout << "#";
    cout << endl;

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (x == 0) cout << "#";

            if (x == headX && y == headY)
                cout << "O";
            else if (x == foodX && y == foodY)
                cout << "F";
            else {
                bool printTail = false;
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == x && tailY[k] == y) {
                        cout << "o";
                        printTail = true;
                        break;
                    }
                }
                if (!printTail) cout << " ";
            }

            if (x == W - 1) cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < W + 2; i++) cout << "#";
    cout << endl;

    cout << "Puntuacion: " << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a': if (dir != RIGHT) dir = LEFT; break;
        case 'd': if (dir != LEFT)  dir = RIGHT; break;
        case 'w': if (dir != DOWN)  dir = UP; break;
        case 's': if (dir != UP)    dir = DOWN; break;
        case 'q': gameOver = true; break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = headX;
    tailY[0] = headY;

    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    if (dir != STOP) {
        switch (dir) {
        case LEFT:  headX--; break;
        case RIGHT: headX++; break;
        case UP:    headY--; break;
        case DOWN:  headY++; break;
        default: break;
        }
    }

    if (headX >= W || headX < 0 || headY >= H || headY < 0)
        gameOver = true;

    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == headX && tailY[i] == headY)
            gameOver = true;
    }

    if (headX == foodX && headY == foodY) {
        score += 10;
        foodX = 1 + rand() % (W - 2);
        foodY = 1 + rand() % (H - 2);
        tailLength++;
    }
}

int main() {
    srand(time(0));
    Setup();

    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }

    cout << "Juego terminado. Puntuacion final: " << score << endl;
    system("pause");
    return 0;
}