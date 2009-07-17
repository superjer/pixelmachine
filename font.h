
#ifndef __FONT_H__
#define __FONT_H__

#include <SDL/SDL.h>

/*
extern SDL_Surface *gpofont;

extern int gnfontw;
extern int gnfonth;
extern int gnfontpitch;
extern int gnfontspace[];
extern char gsfontraw[];
*/


void SJF_Init(const SDL_VideoInfo *pinfo);
void SJF_DrawChar(SDL_Surface *surf, int x, int y, char c);
void SJF_DrawText(SDL_Surface *surf, int x, int y, const char *s);
void SDL_SetPixel(SDL_Surface *surf, int x, int y, Uint8 R, Uint8 G, Uint8 B);



void DrawSquare( SDL_Surface *surf, SDL_Rect *rect, Uint32 color );


#endif //__FONT_H__

