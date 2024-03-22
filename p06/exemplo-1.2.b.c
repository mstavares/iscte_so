#define SO_HIDE_DEBUG                        // Uncomment this line to hide all @DEBUG statements
#include "../include/so_utils.h"

int c = 4, d = 5;

void swap (int x, int y) {
    int temp;
    so_debug("&temp:%p; temp:%d | &x:%p; x:%d | &y:%p; y:%d", &temp, temp, &x, x, &y, y);
    temp = x;
    x = y;
    y = temp;
    so_debug("&temp:%p; temp:%d | &x:%p; x:%d | &y:%p; y:%d", &temp, temp, &x, x, &y, y);
}

int main () {
    int a = 2, b = 3;
    so_debug("&a:%p; a:%d | &b:%p; b:%d | &c:%p; c:%d | &d:%p; d:%d", &a, a, &b, b, &c, c, &d, d);
    printf("BEFORE SWAP: a = %d, b = %d, c = %d, d = %d\n", a, b, c, d);
    swap(a, b);
    swap(c, d);
    printf("AFTER  SWAP: a = %d, b = %d, c = %d, d = %d\n", a, b, c, d);
    so_debug("&a:%p; a:%d | &b:%p; b:%d | &c:%p; c:%d | &d:%p; d:%d", &a, a, &b, b, &c, c, &d, d);
}