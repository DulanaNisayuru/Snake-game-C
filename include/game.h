#ifndef GAME_H
#define GAME_H

#include "snake.h"

#define WIDTH 80
#define HEIGHT 20

typedef struct {
    int x;
    int y;
} Fruit;

void initGame(Snake *snake, Fruit *fruit);
void drawBoard(Snake *snake, Fruit *fruit);
int checkCollision(Snake *snake);
void generateFruit(Fruit *fruit, Snake *snake);

#endif
