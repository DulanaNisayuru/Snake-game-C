#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

void initGame(Snake *snake, Fruit *fruit) {
    initSnake(snake);
    srand(time(NULL));
    generateFruit(fruit, snake);
}

void drawBoard(Snake *snake, Fruit *fruit) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int printed = 0;
            if (x == 0 || x == WIDTH-1 || y == 0 || y == HEIGHT-1) {
                printf("#"); // wall
                printed = 1;
            } else if (x == fruit->x && y == fruit->y) {
                printf("*"); // fruit
                printed = 1;
            } else {
                for (int i = 0; i < snake->length; i++) {
                    if (x == snake->x[i] && y == snake->y[i]) {
                        printf(i == 0 ? "O" : "o"); // head vs body
                        printed = 1;
                    }
                }
            }
            if (!printed) printf(" ");
        }
        printf("\n");
    }
}

int checkCollision(Snake *snake) {
    // Wall collision
    if (snake->x[0] <= 0 || snake->x[0] >= WIDTH-1 || snake->y[0] <= 0 || snake->y[0] >= HEIGHT-1)
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
