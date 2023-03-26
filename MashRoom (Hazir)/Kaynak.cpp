#include<iostream>
#include<Windows.h>
#include<time.h>
#include<conio.h>
using namespace std;
void mysetcolor(int fg, int bg) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, fg | (bg << 4));
}
int X = 0;
int Y = 0;
const int s = 12;
int game[s][s] = {};
int live = 3;
bool hasStoped = false;
int score = 0;
int counter = 0;
int counterstar = 0;
void ResetMushrooms() {
    for (size_t i = 0; i < s; i++)
    {
        for (size_t k = 0; k < s; k++)
        {
            if (game[i][k] == 9) {
                game[i][k] = 0;
            }
        }
    }
}
void SetTeleport();
void SetStar();
void SetWalls();
void SetFruits();
void ShowGame() {
    SetWalls();
    SetTeleport();
    for (size_t i = 0; i < s; i++)
    {
        for (size_t k = 0; k < s; k++)
        {
            if (i == 0 || i == s - 1) {

                cout << "- ";

            }
            else if (k == 0) {

                cout << "| ";

            }
            else if (k == s - 1) {

                cout << "|";

            }
            else if (game[i][k] == 1) {
                mysetcolor(2, 0);
                cout << (char)2 << " ";
                mysetcolor(7, 0);
            }
            else if (game[i][k] == 2) {
                mysetcolor(6, 0);
                cout << "O" << " ";
                mysetcolor(7, 0);
            }
            else if (game[i][k] == 9) {
                mysetcolor(3, 0);
                cout << (char)3 << " ";
                mysetcolor(7, 0);
            }
            else if (game[i][k] == 5) {
                mysetcolor(4, 0);
                cout << (char)209 << " ";
                mysetcolor(7, 0);
            }
            else if (game[i][k] == 8) {
                mysetcolor(8, 0);
                cout << (char)17 << " ";
                mysetcolor(7, 0);
            }
            else if (game[i][k] == 4) {
                mysetcolor(9, 0);
                cout << (char)34 << " ";
                mysetcolor(7, 0);
            }
            else {
                cout << "  ";
            }
        }cout << endl;
    }
    cout << "SCORE : " << score << endl;
    for (size_t i = 0; i < live; i++)
    {
        mysetcolor(4, 0);
        cout << (char)3 << " ";
        mysetcolor(7, 0);
    }
}
void SetMushrooms();
void SetFruits() {
    while (true)
    {
        int rX = 1 + rand() % (9);
        int rY = 1 + rand() % (9);
        if (game[rY][rX] == 0) {
            game[rY][rX] = 2;
            break;
        }
    }
    SetMushrooms();
    SetMushrooms();
}
void SetMushrooms() {
    while (true)
    {
        int rX = 1 + rand() % (9);
        int rY = 1 + rand() % (9);
        if (game[rY][rX] == 0) {
            game[rY][rX] = 9;
            break;
        }
    }
}
void SetStar() {
    while (true)
    {
        int rX = 1 + rand() % (9);
        int rY = 1 + rand() % (9);
        if (game[rY][rX] == 0) {
            game[rY][rX] = 8;
            break;
        }
    }
}
void SetTeleport() {
    game[1][4] = 4;
    game[1][5] = 4;
    game[1][6] = 4;
    game[4][1] = 4;
    game[5][1] = 4;
    game[6][1] = 4;
    game[4][10] = 4;
    game[5][10] = 4;
    game[6][10] = 4;
    game[10][4] = 4;
    game[10][5] = 4;
    game[10][6] = 4;
}
void SetWalls() {
    game[4][3] = 5;
    game[5][3] = 5;
    game[6][3] = 5;
    game[8][3] = 5;
    game[8][4] = 5;
    game[8][5] = 5;
    game[8][6] = 5;
    game[2][7] = 5;
    game[2][8] = 5;
    game[2][9] = 5;
    game[5][8] = 5;
    game[6][8] = 5;
    game[7][8] = 5;
}
bool hasEaten = false;
void ResetFruits();
bool isEmpty(int x, int y) {
    ++counter;
    if (counter % 10 == 0 && hasEaten == false) {
        ResetFruits();
        SetFruits();
    }
    hasEaten = false;
    if (x == 0 || y == 0 || x == s - 1 || y == s - 1) {
        --live;
        cout << "\a";
        if (live == 0) {
            hasStoped = true;
            mysetcolor(4, 0);
        }
        return false;
    }
    else if (game[y][x] == 9) {
        score -= 10;
        cout << "\a";
    }
    else if (game[y][x] == 5) {
        return false;
    }
    else if (game[y][x] == 4) {
        return false;
    }
    else if (game[y][x] == 8) {
        score -= 20;
        counterstar += 1;
        if (counterstar == 1) {
            SetStar();
            SetStar();
            SetStar();
            SetStar();
            SetStar();
        }
    }
    else if (game[y][x] == 2) {
        counter = 0;
        hasEaten = true;
        score += 10;
        SetFruits();
        if (score == 50) {
            ResetMushrooms();
        }
    }
    return true;
}
void ResetFruits() {
    for (size_t i = 0; i < s; i++)
    {
        for (size_t k = 0; k < s; k++)
        {
            if (game[i][k] == 2) {
                game[i][k] = 0;
            }
        }
    }
}
void ResetPlayer() {
    for (size_t i = 0; i < s; i++)
    {
        for (size_t k = 0; k < s; k++)
        {
            if (game[i][k] == 1) {
                game[i][k] = 0;
            }
        }
    }
}
void StartLoop() {
    enum Directions { UP = 72, DOWN = 80, RIGHT = 77, LEFT = 75 };
    while (true)
    {
        system("cls");
        ShowGame();
        if (hasStoped) {
            return;
        }
        char symbol = _getch();
        if (symbol == -32) {
            symbol = _getch();
            int no = symbol;
            if (no == UP) {
                if (!isEmpty(X, Y - 1)) {
                    if (game[1][4] == 4 && game[1][5] == 4 && game[1][6] == 4) {
                        game[Y][X] = 0;
                        Y = s - 3;
                        game[Y][X] = 1;
                        continue;
                    }
                }
                game[Y][X] = 0;
                Y--;
            }
            else if (no == DOWN) {
                if (!isEmpty(X, Y + 1)) {
                    if (game[10][4] == 4 && game[10][5] == 4 && game[10][6] == 4) {
                        game[Y][X] = 0;
                        Y = s - (s - 2);
                        game[Y][X] = 1;
                        continue;
                    }
                }
                game[Y][X] = 0;
                Y++;
            }
            else if (no == LEFT) {
                if (!isEmpty(X - 1, Y)) {
                    if (game[4][1] == 4 && game[5][1] == 4 && game[6][1] == 4) {
                        game[Y][X] = 0;
                        X = s - 3;
                        game[Y][X] = 1;
                        continue;
                    }
                }
                game[Y][X] = 0;
                X--;
            }
            else if (no == RIGHT) {
                if (!isEmpty(X + 1, Y)) {
                    if (game[4][10] == 4 && game[5][10] == 4 && game[6][10] == 4) {
                        game[Y][X] = 0;
                        X = s - (s - 2);
                        game[Y][X] = 1;
                        continue;
                    }
                }
                game[Y][X] = 0;
                X++;
            }
            game[Y][X] = 1;
        }
    }
}
void main() {
    srand(time(0));
    X = 5;
    Y = 5;
    game[Y][X] = 1;
    SetStar();
    SetFruits();
    ShowGame();
    StartLoop();
}