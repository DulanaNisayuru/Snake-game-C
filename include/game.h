#ifndef GAME_H
#define GAME_H
#define MAX_OBSTACLES 20

#include "snake.h"

#define WIDTH 80
#define HEIGHT 20

typedef struct {
    int x;
    int y;
} Fruit;

typedef struct {
    int x;
    int y;
} Obstacle;

void setColor(int color);
void initGame(Snake *snake, Fruit *fruit);
void drawBoard(Snake *snake, Fruit *fruit, Obstacle obstacles[], int obstacleCount);
int checkCollision(Snake *snake);
void generateFruit(Fruit *fruit, Snake *snake);

void initObstacles(Obstacle obstacles[], int count);
int checkObstacleCollision(Snake *snake, Obstacle obstacles[], int count);

#endif
