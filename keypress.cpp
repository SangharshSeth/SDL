#include <SDL2/SDL.h>
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

//RESOLUTIONS
const int WIDTH = 1366;
const int HEIGHT = 768;

//KEY PRESS CONSTANTS
enum keyPressSurfaces{
    DEFAULT,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    TOTAL
};

//FUNCTIONS DECLARATIONS
//initialisation
bool init();
//take s a image path and renders it in a surface returns itspointer
SDL_Surface* loadSurface(string path);
//load and draw on screen
bool loadMedia();
//close sdl and clean memory
void close();


//GLOBALS
SDL_Window* gwindow = NULL;
//surface contained by the window
SDL_Surface* gsurface = NULL;
//current displayed image
SDL_Surface* gCurrentSurface = NULL;
//images corresponding to key Pressed
//its like int arr[x] this contains pointers to every image surfaces
SDL_Surface* gallSurfaces[TOTAL];

bool init(){
    bool status = true;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("Error:%s\n",SDL_GetError());
        status = false;
    }
    else{
        gwindow = SDL_CreateWindow(
            "title",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WIDTH,
            HEIGHT,
            false
        );
        if(gwindow == NULL){
            printf("Error:%s\n",SDL_GetError());
            status = false;
        }
        else{
            gsurface = SDL_GetWindowSurface(gwindow);
        }
    }
    return status;
}
//this function loads a image onto a surface and returns the surface pointer
SDL_Surface* loadSurface(string path){
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == NULL){
        printf("Error:%s\n",SDL_GetError());
    }
    return loadedSurface;
}

//loadMedia function
bool loadMedia(){
    bool status = true;
    gallSurfaces[DEFAULT] = loadSurface("assets/prompt.bmp");
    if(gallSurfaces[DEFAULT] == NULL){
        printf("Error during image Loading:%s\n",SDL_GetError());
        status = false;
    }
    gallSurfaces[UP] = loadSurface("assets/UP.bmp");
    if(gallSurfaces[UP] == NULL){
        printf("Error during image Loading:%s\n",SDL_GetError());
        status = false;
    }
    gallSurfaces[DOWN] = loadSurface("assets/down.bmp");
    if(gallSurfaces[DOWN] == NULL){
        printf("Error during image Loading:%s\n",SDL_GetError());
        status = false;
    }
    gallSurfaces[LEFT] = loadSurface("assets/left.bmp");
    if(gallSurfaces[LEFT] == NULL){
        printf("Error during image Loading:%s\n",SDL_GetError());
        status = false;
    }
    gallSurfaces[RIGHT] = loadSurface("assets/right.bmp");
    if(gallSurfaces[RIGHT] == NULL){
        printf("Error during image Loading:%s\n",SDL_GetError());
        status = false;
    }
    return status;
}
//
void close(){
    SDL_DestroyWindow(gwindow);
    gwindow = NULL;
    for(int i = 0; i < TOTAL; i++){
        SDL_FreeSurface(gallSurfaces[i]);
        gallSurfaces[i] = NULL;
    }
    SDL_Quit();
}
//main function
int main(int argc,char* args[]){
    bool quit = false;
    SDL_Event e;
    if(!init()){
        printf("Error during Initialisation:%s\n",SDL_GetError());
        return -1;
    }
    if(!loadMedia()){
        printf("Error:%s\n",SDL_GetError());
        return -1;
    }
    //set current surface to default
    gCurrentSurface = gallSurfaces[DEFAULT];
    while(!quit){
        //handle event queue
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT)
                quit = true;
            else if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        gCurrentSurface = gallSurfaces[UP];
                        break;
                    case SDLK_DOWN:
                        gCurrentSurface = gallSurfaces[DOWN];
                        break;
                    case SDLK_LEFT:
                        gCurrentSurface = gallSurfaces[LEFT];
                        break;
                    case SDLK_RIGHT:
                        gCurrentSurface = gallSurfaces[RIGHT];
                        break;

                }
            }
        }
              SDL_BlitSurface(gCurrentSurface,NULL,gsurface,NULL);
              SDL_UpdateWindowSurface(gwindow);
    }
    close();
    return 0;
}
