#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <stdio.h>
using namespace std;
//screen Dimensions
const int WIDTH = 1280;
const int HEIGHT = 720;
int main(int argc,char* args[]){
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    if(SDL_Init(SDL_INIT_VIDEO) == -1){
        printf("Error during initialisation..:(...SDL_Error: %s\n",SDL_GetError());

    }
    else{
        //create Window
        window = SDL_CreateWindow("firstWindow",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,false);
        if(window == NULL){
            printf("Failed to Create Window...%s\n",SDL_GetError());
        }
        else{
            //create surface
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface,NULL,SDL_MapRGB(screenSurface->format,0xFF,0x00,0x00));
            //update the surface to show changes
            SDL_UpdateWindowSurface(window);
            //no keyboard input works during delay
            SDL_Delay(5000);
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}