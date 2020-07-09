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
    for (const HalfEdge& e : m.edges)
    {
        SDL_RenderDrawLine(renderer, e.origin->position.x,
            e.origin->position.y, e.twin->origin->position.x,
            e.twin->origin->position.y);
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
    bool addEdges = false;
    double firstX, firstY, lastX, lastY;

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
                        if (addEdges)
                        {
                            m.addEdge(x, y, lastX, lastY);
                        }
                        else
                        {
                            m.addVertex(x, y);
                            firstX = x;
                            firstY = y;
                            addEdges = true;
                        }
                        lastX = x;
                        lastY = y;
                        redraw = true;
                    }
                    else if (event.button.button == SDL_BUTTON_RIGHT)
                    {
                        if (addEdges)
                        {
                            m.addEdge(lastX, lastY, firstX, firstY);
                            addEdges = false;
                            redraw = true;
                        }
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
            redraw = false;
        }
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
