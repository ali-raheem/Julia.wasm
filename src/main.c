#include <stdio.h>
#include <math.h>
#include <complex.h>

#include <SDL2/SDL.h>

#define WIDTH 1280
#define HEIGHT 960
#define SCALE 0.75

#define THRESH 10
#define ITERATIONS 255

#define C (-0.8 + 0.156 * I)

int isColoured(float x, float y) {
  float complex z;
  z = x + y * I;
  int i;
  for(i = 0; i < ITERATIONS; i++) {
    z = cpowf(z, 2) + C;
    if (cabs(z) > THRESH)
      return i;
  }
  return 255;    
}

int main() {
  SDL_Renderer *renderer;
  SDL_Window *window;
  
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  int x, y;
  puts("Ready to draw!");

  for(y = 0; HEIGHT > y; ++y) {
    for(x = 0; WIDTH > x; ++x) {
      float sx, sy;
      sx = SCALE * (WIDTH/2 - x) / (WIDTH/2);
      sy = SCALE * (HEIGHT/2 - y) / (HEIGHT/2);
      int col = isColoured(sx, sy);
      SDL_SetRenderDrawColor(renderer, col, col, col, 255);
      SDL_RenderDrawPoint(renderer, x, y);
    }
    SDL_RenderPresent(renderer);
    }
    printf("Done drawing!");
}
