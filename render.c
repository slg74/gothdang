#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "render.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MOVE_SPEED 5.0f
#define TURN_SPEED 0.05f

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

typedef struct {
    float x;
    float y;
    float angle;
} Player;

Player player = { 400, 300, 0 }; 

void initialize_game() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Goth Hunter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void process_input(bool *quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            *quit = true;
        }
    }

    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    
    if (currentKeyStates[SDL_SCANCODE_W]) {
        player.x += cos(player.angle) * MOVE_SPEED;
        player.y += sin(player.angle) * MOVE_SPEED;
    }
    if (currentKeyStates[SDL_SCANCODE_S]) {
        player.x -= cos(player.angle) * MOVE_SPEED;
        player.y -= sin(player.angle) * MOVE_SPEED;
    }
    if (currentKeyStates[SDL_SCANCODE_A]) {
        player.angle -= TURN_SPEED;
    }
    if (currentKeyStates[SDL_SCANCODE_D]) {
        player.angle += TURN_SPEED;
    }
} 

void update_game_state() {
    // This function will be used for game logic updates
}

void render() {
    // Clear the screen with black (sky)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw green rectangle for land (bottom half of the screen)
    SDL_Rect land = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
    SDL_RenderFillRect(renderer, &land);

    // Draw a simple representation of the player's view
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 
                       SCREEN_WIDTH / 2 + cos(player.angle) * 50, 
                       SCREEN_HEIGHT / 2 + sin(player.angle) * 50);

    // Present the rendered frame
    SDL_RenderPresent(renderer);
}
 
void cleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
