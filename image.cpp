#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <stdio.h>
using namespace std;
//screen Dimensions
const int WIDTH = 700;
const int HEIGHT = 533;
SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
SDL_Surface *image = NULL;
//initialise SDL
bool init()
{
    bool status = true;
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        printf("Error..%s\n", SDL_GetError());
        status = false;
    }
    else
    {
        window = SDL_CreateWindow("image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);
        if (window == NULL)
        {
            printf("Window could not be created..%s\n", SDL_GetError());
            status = false;
        }
        else
        {
            surface = SDL_GetWindowSurface(window);
        }
    }
    return status;
}
//load Image
bool loadMedia()
{
    bool status = true;
    image = SDL_LoadBMP("./assets/image.bmp");
    if (image == NULL)
    {
        printf("Error loading image..%s\n", SDL_GetError());
        status = false;
    }
    return status;
}
//close SDL
void close()
{
    SDL_FreeSurface(image);
    image = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

int main(int argc, char *args[])
{
    bool quit = false;
    SDL_Event event;

    if (!init())
    {
        printf("Failed to Initialise..");
    }
    else
    {
        if (!loadMedia())
        {
            printf("Failed to load Media...");
        }
        else
        {
            while (!quit)
            {
                while (SDL_PollEvent(&event) != 0)
                {
                    if (event.type == SDL_QUIT)
                        quit = true;
                }
                SDL_BlitSurface(image, NULL, surface, NULL);
                SDL_UpdateWindowSurface(window);
                SDL_Delay(100);
            }
        }
    }
    close();
    return 0;
}