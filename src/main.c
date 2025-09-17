#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "snake.h"
#include "game.h"

void changeDirection(Snake *snake, char key) {
    switch(key) {
        case 'w': if (snake->direction != 'D') snake->direction = 'U'; break;
        case 's': if (snake->direction != 'U') snake->direction = 'D'; break;
        case 'a': if (snake->direction != 'R') snake->direction = 'L'; break;
        case 'd': if (snake->direction != 'L') snake->direction = 'R'; break;
    }
}

int main() {
    Snake snake;
    Fruit fruit;
    int score = 0;

    initGame(&snake, &fruit);

    while (1) {
        if (kbhit()) {
            char ch = getch();
            changeDirection(&snake, ch);
        }

        moveSnake(&snake);

        // Check if fruit eaten
        if (snake.x[0] == fruit.x && snake.y[0] == fruit.y) {
            growSnake(&snake);
            generateFruit(&fruit, &snake);
            score += 10;
        }

        system("cls");
        printf("Score: %d\n", score);
        drawBoard(&snake, &fruit);

        if (checkCollision(&snake)) {
            printf("Game Over! Final Score: %d\n", score);
            break;
        }

        Sleep(150); // delay in ms
    }

    return 0;
}
