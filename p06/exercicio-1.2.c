#include <stdio.h>
#include <string.h>

void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

/*
void swap(int x, int y) {
  int temp = x;
  x = y;
  y = temp;
}
*/

int main(int argc, char *argv[]) {
  int x = 1, y = 2;
  swap(&x, &y);
  printf("x: %d y: %d \n", x, y);

}