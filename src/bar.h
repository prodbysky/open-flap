#ifndef BAR_H
#define BAR_H

#include "square.h"
#include "window.h"

typedef struct {
    square_t rect;
    float offsetX;
    float offsetY;
    float speed;
} bar_t;

bar_t bar_new(int x, int y, int w, int h, float speed);
void bar_move(bar_t* bar, float x, float y);
void bar_update(bar_t* bar);

#endif // BAR_H
