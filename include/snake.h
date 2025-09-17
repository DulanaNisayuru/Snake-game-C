#ifndef SNAKE_H
#define SNAKE_H

#define MAX_SNAKE 100

typedef struct {
    int x[MAX_SNAKE];
    int y[MAX_SNAKE];
    int length;
    char direction; // 'U', 'D', 'L', 'R'
} Snake;

void initSnake(Snake *s);
void moveSnake(Snake *s);
void growSnake(Snake *s);

#endif
