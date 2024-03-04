#include "bar.h"

bar_t bar_new(int x, int y, int w, int h, float speed) {
    bar_t bar;
    
    bar.rect = square_new(x, y, w, h);
    bar.offsetX = 0;
    bar.offsetY = 0;
    bar.speed = -speed;

    return bar;
}

void bar_update(bar_t* bar) {
    bar->offsetX += bar->speed;
    square_move(&bar->rect, bar->speed, 0);
}
