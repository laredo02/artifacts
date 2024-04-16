#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Create an SDL window
    SDL_Window* window = SDL_CreateWindow(
        "SDL Texture Example",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480,
        SDL_WINDOW_OPENGL
    );
    if (!window) {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        return 1;
    }

    // Create a texture for a rendering context
    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        640, 480
    );
    if (!texture) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        fprintf(stderr, "Could not create texture: %s\n", SDL_GetError());
        return 1;
    }

    // Create an array filled with pixel data
    Uint32 pixels[640 * 480];
    for (int i = 0; i < 640 * 480; ++i) {
        pixels[i] = 0xFFFF00FF; // Magenta with full opacity
    }

    // Update the texture using the pixels array
    SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(Uint32));

    // Main loop flag
    int quit = 0;
    SDL_Event event;

    // Main loop
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Clear screen
        SDL_RenderClear(renderer);
        // Render texture to screen
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Free resources and close SDL
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

