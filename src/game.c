#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include <windows.h>

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void initObstacles(Obstacle obstacles[], int count) {
    for (int i = 0; i < count; i++) {
        obstacles[i].x = rand() % WIDTH;
        obstacles[i].y = rand() % HEIGHT;
    }
}

void initGame(Snake *snake, Fruit *fruit) {
    initSnake(snake);
    srand(time(NULL));
    generateFruit(fruit, snake);
}

int checkObstacleCollision(Snake *snake, Obstacle obstacles[], int count) {
    for (int i = 0; i < count; i++) {
        if (snake->x[0] == obstacles[i].x && snake->y[0] == obstacles[i].y) {
            return 1; // collision
        }
    }
    return 0;
}

void drawBoard(Snake *snake, Fruit *fruit, Obstacle obstacles[], int obstacleCount) {
    // Draw top border
    for (int x = 0; x < WIDTH + 2; x++) {
        printf("#");
    }
    printf("\n");

    for (int y = 0; y < HEIGHT; y++) {
        printf("#"); // Left border
        for (int x = 0; x < WIDTH; x++) {
            int printed = 0;

            // Fruit
            if (x == fruit->x && y == fruit->y) {
                setColor(10); // Green
                printf("F");
                setColor(7);
                printed = 1;
            }

            // Snake
            for (int i = 0; i < snake->length; i++) {
                if (snake->x[i] == x && snake->y[i] == y) {
                    setColor(14); // Yellow
                    printf("O");
                    setColor(7);
                    printed = 1;
                }
            }

            // Obstacles
            for (int i = 0; i < obstacleCount; i++) {
                if (obstacles[i].x == x && obstacles[i].y == y) {
                    setColor(12); // Red
                    printf("X");
                    setColor(7);
                    printed = 1;
                }
            }

            if (!printed) printf(" ");
        }
        printf("#\n"); // Right border
    }

    // Draw bottom border
    for (int x = 0; x < WIDTH + 2; x++) {
        printf("#");
    }
    printf("\n");
}


int checkCollision(Snake *snake) {
    // Wall collision (with border)
    if (snake->x[0] < 0 || snake->x[0] >= WIDTH || snake->y[0] < 0 || snake->y[0] >= HEIGHT)
        return 1;

    // Self collision
    for (int i = 1; i < snake->length; i++) {
        if (snake->x[0] == snake->x[i] && snake->y[0] == snake->y[i])
            return 1;
    }
    return 0;
}


void generateFruit(Fruit *fruit, Snake *snake) {
    int valid = 0;
    while (!valid) {
        fruit->x = rand() % (WIDTH-2) + 1;
        fruit->y = rand() % (HEIGHT-2) + 1;
        valid = 1;
        for (int i = 0; i < snake->length; i++) {
            if (fruit->x == snake->x[i] && fruit->y == snake->y[i]) {
                valid = 0;
                break;
            }
        }
    }
}
