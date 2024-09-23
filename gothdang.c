#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "render.h"

// Function prototypes
void process_input(bool *quit);
void update_game_state();

int main() {
    bool quit = false;
    
    initialize_game();
    
    while (!quit) {
        process_input(&quit);
        update_game_state();
        render();
        
        // Add a small delay to control frame rate
        SDL_Delay(16); // Roughly 60 FPS
    }
    
    cleanup();
    return 0;
}