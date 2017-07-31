#ifndef GAME_H
#define GAME_H

#include<SDL2/SDL.h>
#include<string>
#include<iostream>

extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;
extern int FRAME_RATE;
extern int ANIMATION_RATE;

extern SDL_Window* window;
extern SDL_Renderer* windowRenderer;
extern SDL_Joystick* controller;

void mainLoop();

#endif
