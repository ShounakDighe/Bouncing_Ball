#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

int main() {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    int quit = 0;
    int x = 20, y = 380, r = 20;
    int high = 300, j = 0;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Bouncing Ball", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the road
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, 0, 401, 639, 401);

        // Draw the bouncing ball
        if (high > 0) {
            for (int i = 0; i <= high; i++) {
                if (i % 4 == 0) {
                    j++;
                }
                x = 20 + j;
                y = 380 - i;

                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

                // Approximate ellipse with a series of small circles
                for (int angle = 0; angle < 360; angle++) {
                    double radians = angle * (M_PI / 180);
                    int ex = x + (r * cos(radians));
                    int ey = y + (r * sin(radians));
                    SDL_RenderDrawPoint(renderer, ex, ey);
                }
            }
            high -= 40;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(100); // Increase the delay to slow down the animation
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
