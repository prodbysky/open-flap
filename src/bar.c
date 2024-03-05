#include "bar.h"
#include "square.h"

bar_t bar_new(int x, int y, int w, int h, float speed) {
    bar_t bar;
    
    bar.rect = square_new(x, y, w, h);
    bar.offsetX = 0;
    bar.offsetY = 0;
    bar.speed = -speed;

    return bar;
}

void bar_move(bar_t* bar, float x, float y) {
    bar->offsetX += x;
    bar->offsetY += y;
    square_move(&bar->rect, x, y);
}

void bar_update(bar_t* bar) {
    bar_move(bar, bar->speed, 0);
}
