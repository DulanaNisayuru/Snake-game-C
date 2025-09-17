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

// Move cursor to x,y in console
void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Change snake direction based on key input (arrow keys + WASD)
void changeDirection(Snake *snake) {
    if (!kbhit()) return;

    int ch = getch();

    if (ch == 0 || ch == 224) { // arrow keys
        ch = getch();
        switch (ch) {
            case 72: if (snake->direction != 'D') snake->direction = 'U'; break; // up
            case 80: if (snake->direction != 'U') snake->direction = 'D'; break; // down
            case 75: if (snake->direction != 'R') snake->direction = 'L'; break; // left
            case 77: if (snake->direction != 'L') snake->direction = 'R'; break; // right
        }
    } else { // WASD keys
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
    int score = 0;

    hideCursor();  
    initGame(&snake, &fruit);

    // Clear screen once and move cursor to top-left
    system("cls");
    gotoxy(0, 0);

    while (1) {
        changeDirection(&snake);  // read input

        moveSnake(&snake);

        // Check if fruit eaten
        if (snake.x[0] == fruit.x && snake.y[0] == fruit.y) {
            growSnake(&snake);
            generateFruit(&fruit, &snake);
            score += 10;
        }

        // Redraw board without clearing screen
        gotoxy(0, 0);  // move cursor to top-left
        printf("Score: %d\n", score);
        drawBoard(&snake, &fruit);

        // Check collision
        if (checkCollision(&snake)) {
            gotoxy(0, HEIGHT + 2); // move cursor below board
            printf("Game Over! Final Score: %d\n", score);
            break;
        }

        Sleep(150); // delay in ms
    }

    return 0;
}
