#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "snake.h"
#include "game.h"

void hideCursor() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = FALSE; // hide cursor
    SetConsoleCursorInfo(console, &cursorInfo);
}


void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void changeDirection(Snake *snake) {
    if (!kbhit()) return;

    int ch = getch();

    if (ch == 0 || ch == 224) { // arrow keys
        ch = getch();
        switch (ch) {
            case 72: if (snake->direction != 'D') snake->direction = 'U'; break;
            case 80: if (snake->direction != 'U') snake->direction = 'D'; break;
            case 75: if (snake->direction != 'R') snake->direction = 'L'; break;
            case 77: if (snake->direction != 'L') snake->direction = 'R'; break;
        }
    } else { // WASD
        switch (ch) {
            case 'w': if (snake->direction != 'D') snake->direction = 'U'; break;
            case 's': if (snake->direction != 'U') snake->direction = 'D'; break;
            case 'a': if (snake->direction != 'R') snake->direction = 'L'; break;
            case 'd': if (snake->direction != 'L') snake->direction = 'R'; break;
        }
    }
}

int main() {
    Snake snake;
    Fruit fruit;
    Obstacle obstacles[MAX_OBSTACLES];
    int score = 0;
    int gameOver = 0;
    int obstacleCount = 5;

    hideCursor();
    initGame(&snake, &fruit);
    initObstacles(obstacles, obstacleCount);

    system("cls");
    gotoxy(0, 0);

    while (!gameOver) {
        changeDirection(&snake);
        moveSnake(&snake);

        // Check if fruit eaten
        if (snake.x[0] == fruit.x && snake.y[0] == fruit.y) {
            growSnake(&snake);
            generateFruit(&fruit, &snake);
            score += 10;

            // Add new obstacle every 30 points
            if (score % 30 == 0 && obstacleCount < MAX_OBSTACLES) {
                initObstacles(&obstacles[obstacleCount], 1);
                obstacleCount++;
            }
        }

        gotoxy(0, 0);
        printf("Score: %d\n", score);
        drawBoard(&snake, &fruit, obstacles, obstacleCount);

        if (checkCollision(&snake) || checkObstacleCollision(&snake, obstacles, obstacleCount)) {
            gotoxy(0, HEIGHT + 2);
            printf("Game Over! Final Score: %d\n", score);
            gameOver = 1;
        }

        Sleep(250);
    }

    return 0;
}
