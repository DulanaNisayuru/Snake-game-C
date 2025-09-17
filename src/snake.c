#include "snake.h"

void initSnake(Snake *s) {
    s->length = 3;
    s->x[0] = 10; s->y[0] = 10; // head
    s->x[1] = 9; s->y[1] = 10;
    s->x[2] = 8; s->y[2] = 10;
    s->direction = 'R';
}

void moveSnake(Snake *s) {
    // Move body
    for (int i = s->length - 1; i > 0; i--) {
        s->x[i] = s->x[i-1];
        s->y[i] = s->y[i-1];
    }

    // Move head
    switch (s->direction) {
        case 'U': s->y[0]--; break;
        case 'D': s->y[0]++; break;
        case 'L': s->x[0]--; break;
        case 'R': s->x[0]++; break;
    }
}

void growSnake(Snake *s) {
    if (s->length < MAX_SNAKE) {
        s->length++;
        // The new tail will follow last position naturally
    }
}
