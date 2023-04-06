#include <SDL2/SDL.h>
#include <stdio.h>





int main(int argc, char *argv[]) {

int grid_cell_size = 10;
int grid_width = 100;
int grid_height = 100;
int window_width = (grid_cell_size * grid_width)+1;
int window_height = (grid_cell_size * grid_height)+1;


//
SDL_Rect grid_cursor = {
    .x = (grid_width - 1) / 2 * grid_cell_size, 
    .y = (grid_height - 1) / 2 * grid_cell_size,
    .w = grid_cell_size,
    .h = grid_cell_size,
};
SDL_Rect grid_cursor_ghost = {grid_cursor.x, grid_cursor.y, grid_cell_size, grid_cell_size};
//

SDL_Color grid_cell_empty = {22, 22, 22, 255};
SDL_Color grid_line_color = {44, 44, 44, 255};
SDL_Color grid_cursor_ghost_color = {44, 44, 44, 255};
SDL_Color grid_cell_alive = {255, 0, 255, 255};


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s", SDL_GetError());
    }
SDL_Window *window;
SDL_Renderer *renderer;
if(SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer) < 0){
         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Create window and renderer: %s", SDL_GetError());   
}
 SDL_SetWindowTitle(window, "SDL Grid");

SDL_bool quit = SDL_FALSE;
SDL_bool mouse_active = SDL_FALSE;
SDL_bool mouse_hover = SDL_FALSE;
//
while (!quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_w:
            case SDLK_UP:
                grid_cursor.y -= grid_cell_size;
                break;
            case SDLK_s:
            case SDLK_DOWN:
                grid_cursor.y += grid_cell_size;
                break;
            case SDLK_a:
            case SDLK_LEFT:
                grid_cursor.x -= grid_cell_size;
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                grid_cursor.x += grid_cell_size;
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            grid_cursor.x = (event.motion.x / grid_cell_size) * grid_cell_size;
            grid_cursor.y = (event.motion.y / grid_cell_size) * grid_cell_size;
            break;
        case SDL_MOUSEMOTION:
            grid_cursor_ghost.x = (event.motion.x / grid_cell_size) * grid_cell_size;
            grid_cursor_ghost.y = (event.motion.y / grid_cell_size) * grid_cell_size;
            if (!mouse_active)
                mouse_active = SDL_TRUE;
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_ENTER && !mouse_hover)
                mouse_hover = SDL_TRUE;
            else if (event.window.event == SDL_WINDOWEVENT_LEAVE && mouse_hover)
                mouse_hover = SDL_FALSE;
            break;
        case SDL_QUIT:
            quit = SDL_TRUE;
            break;
        }
    }
//
    SDL_SetRenderDrawColor(renderer, grid_cell_empty.r, grid_cell_empty.g, grid_cell_empty.b, grid_cell_empty.a);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, grid_line_color.r, grid_line_color.g,grid_line_color.b, grid_line_color.a);

        for (int x = 0; x < 1 + grid_width * grid_cell_size;
             x += grid_cell_size) {
            SDL_RenderDrawLine(renderer, x, 0, x, window_height);
        }
        for (int y = 0; y < 1 + grid_height * grid_cell_size;
             y += grid_cell_size) {
            SDL_RenderDrawLine(renderer, 0, y, window_width, y);
        }
        //
        if (mouse_active && mouse_hover) {
            SDL_SetRenderDrawColor(renderer, grid_cursor_ghost_color.r, grid_cursor_ghost_color.g, grid_cursor_ghost_color.b, grid_cursor_ghost_color.a);
            SDL_RenderFillRect(renderer, &grid_cursor_ghost);
        }
        
        SDL_SetRenderDrawColor(renderer, grid_cell_alive.r, grid_cell_alive.g, grid_cell_alive.b, grid_cell_alive.a);
        SDL_RenderFillRect(renderer, &grid_cursor);
        SDL_RenderPresent(renderer);
        //
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
return 0;
}