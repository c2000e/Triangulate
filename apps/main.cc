#include "SDL.h"

#include "Triangulate/mesh.h"

#include <iostream>

template<>
void draw(const Mesh& m, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0,255);
    for (const Vertex& v : m.vertices)
    {
        SDL_RenderDrawPoint(renderer, v.position.x, v.position.y);
    }
}

int main(int argc, char* arv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "ERROR INITIALIZING SD:" << SDL_GetError()
            << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Triangulate",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    Mesh m;

    SDL_Event event;
    bool running = true;
    bool redraw = true;
    while (running)
    {
        if (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        m.addVertex(x, y);
                        redraw = true;
                    }
                    break;
            }
        }

        if (redraw)
        {
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            SDL_RenderClear(renderer);

            draw(m, renderer);

            SDL_RenderPresent(renderer);
        }
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
