#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "structs.h"
#include "lists.h"

void InitEverything(int , int, int, int , TTF_Font **, SDL_Surface **, SDL_Window ** , SDL_Renderer **);
void InitSDL();
void InitFont();
SDL_Window* CreateWindow(int , int, int, int);
SDL_Renderer* CreateRenderer(int , int , SDL_Window *);
void RenderTexture( SDL_Surface **, TTF_Font *, SDL_Renderer *);
void filledCircleRGBA(SDL_Renderer *, int, int, int, int , int , int );
int RenderText(int, int, char *, TTF_Font *, SDL_Color *, SDL_Renderer* );
int RenderLogo(int, int, SDL_Surface *, SDL_Renderer *);

void CoordToPixels(float, char, float, char, int *, int *, int, int);
void ReadFromCityList(SDL_Renderer *, TTF_Font *,  int *, node_t_city **, node_t_city **, int[3][3], int, int, int, int);
void HoverInfo(char *, TTF_Font *, SDL_Renderer *, int, int );

#endif