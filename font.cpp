
#include "font.h"

SDL_Surface *gpofont;

int gnfontw = 8;
int gnfonth = 12;
int gnfontpitch = 128;
int gnfontspace[256] = { 6,3,5,7,7,6,7,3,5,5,6,7,3,6,3,6,
                         6,6,6,6,6,6,6,6,6,6,3,3,5,6,5,7,
                         7,6,6,6,6,6,6,6,6,5,6,6,6,7,7,6,
                         6,6,6,6,7,6,7,7,7,7,6,5,6,5,7,7,
                         4,6,6,6,6,6,5,6,6,4,5,6,4,7,6,6,
                         6,6,5,6,5,6,7,7,7,6,6,5,3,5,6,6,
                         6,7,9,0,0,0,0,0,0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
char gsfontraw[] =
"                                                                                                                                "
"                                                                                                                                "
"         O       O O               O                     O         O     O                                                  O   "
"         O       O O      O O     OOO             OO     O        O       O      O  O      O                                O   "
"         O               OOOOO   O O             O  O            O         O      OO       O                               O    "
"         O                O O     OOO    O  O     OO             O         O      OO     OOOOO           OOOO              O    "
"         O                O O      O O     O     O  OO           O         O     O  O      O                              O     "
"                         OOOOO    OOO     O      O  O             O       O                O                              O     "
"         O                O O      O     O  O     OO O             O     O                       O               O       O      "
"                                                                                                 O                       O      "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                          OOO   "
"  OO       O      OO      OO       OO    OOOO     OO     OOOO     OO      OO                       O             O       O   O  "
" O  O     OO     O  O    O  O     O O    O       O          O    O  O    O  O                     O      OOOO     O          O  "
" O OO      O        O      O     O  O    OOO     OOO       O      OO     O  O    O       O       O                 O        O   "
" OO O      O      OO        O    OOOO       O    O  O      O     O  O     OOO                     O      OOOO     O        O    "
" O  O      O     O       O  O       O    O  O    O  O     O      O  O       O                      O             O              "
"  OO      OOO    OOOO     OO        O     OO      OO      O       OO      OO     O       O                                 O    "
"                                                                                         O                                      "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"  OOO     OO     OOO      OO     OOO     OOOO    OOOO     OO     O  O    OOO       OO    O  O    O       O   O   O   O    OO    "
" O   O   O  O    O  O    O  O    O  O    O       O       O  O    O  O     O         O    O  O    O       OO OO   OO  O   O  O   "
" O OOO   O  O    O  O    O       O  O    O       O       O       O  O     O         O    O O     O       O O O   O O O   O  O   "
" O O O   OOOO    OOO     O       O  O    OOO     OOO     O OO    OOOO     O         O    OO      O       O O O   O  OO   O  O   "
" O OOO   O  O    O  O    O       O  O    O       O       O  O    O  O     O         O    O O     O       O   O   O   O   O  O   "
" O       O  O    O  O    O  O    O  O    O       O       O  O    O  O     O      O  O    O  O    O       O   O   O   O   O  O   "
"  OOO    O  O    OOO      OO     OOO     OOOO    O        OOO    O  O    OOO      OO     O  O    OOOO    O   O   O   O    OO    "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
" OOO      OO     OOO      OOO    OOOOO   O  O    O   O   O   O   O   O   O   O   OOOO    OOO     O       OOO       O            "
" O  O    O  O    O  O    O         O     O  O    O   O   O   O   O   O   O   O      O    O       O         O      O O           "
" O  O    O  O    O  O    O         O     O  O    O   O   O   O    O O    O   O     O     O        O        O     O   O          "
" OOO     O  O    OOO      OO       O     O  O    O   O   O O O     O      OOO     O      O        O        O                    "
" O       O  O    O O        O      O     O  O     O O    O O O    O O      O     O       O         O       O                    "
" O       O  O    O  O       O      O     O  O     O O    O O O   O   O     O     O       O         O       O                    "
" O        OO     O  O    OOO       O      OO       O      O O    O   O     O     OOOO    OOO        O    OOO                    "
"            O                                                                                       O                    OOOOO  "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
" O               O                  O              O             O        O        O     O       OO                             "
"  O              O                  O             O              O                       O        O                             "
"          OO     OOO      OOO     OOO     OO     OOO      OOO    OOO     OO       OO     O  O     O      OOOO    OOO      OO    "
"         O  O    O  O    O       O  O    O  O     O      O  O    O  O     O        O     O O      O      O O O   O  O    O  O   "
"          OOO    O  O    O       O  O    OOOO     O      O  O    O  O     O        O     OO       O      O O O   O  O    O  O   "
"         O  O    O  O    O       O  O    O        O      O  O    O  O     O        O     O O      O      O O O   O  O    O  O   "
"          OOO    OOO      OOO     OOO     OOO     O       OOO    O  O     O        O     O  O     O      O O O   O  O     OO    "
"                                                            O                      O                                            "
"                                                          OO                     OO                                             "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                           O     O       O        O O           "
"                                  O                                                       O      O        O      O O            "
" OOO      OOO    O O      OOO    OOO     O  O    O   O   O O O   O   O   O  O    OOOO     O      O        O                     "
" O  O    O  O    OO      O        O      O  O    O   O   O O O    O O    O  O       O    O       O         O                    "
" O  O    O  O    O        OO      O      O  O     O O    O O O     O     O  O     OO      O               O                     "
" O  O    O  O    O          O     O      O  O     O O    O O O    O O    O  O    O        O      O        O                     "
" OOO      OOO    O       OOO      OO      OOO      O      OOOO   O   O    OOO    OOOO      O     O       O                      "
" O          O                                                               O                    O                              "
" O          O                                                             OO                     O                              "
"                                                                                                                                "
"                                                                                                                                "
"           O        OOO                                                                                                         "
"           OO       OOOO         OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO   "
"         O  O        OOO         O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
" OOOO    OO      OOO             O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
" OOOO     O O    OOOO OOO        O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
" OOOO       OO    OOO OOOO       O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
" OOOO     O  O         OOO       O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
"          OO       OOO           OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO   "
"           O       OOOO                                                                                                         "
"                    OOO                                                                                                         "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
" OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO   "
" O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
" O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
" O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
" O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
" O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
" OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO   "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
" OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO   "
" O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
" O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
" O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
" O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
" O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
" OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO   "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
" OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO   "
" O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
" O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
" O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
" O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
" O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O    O  O   "
" OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO    OOOO   "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                "
"                                                                                                                                ";


void SJF_Init(const SDL_VideoInfo *pinfo)
{
    int u,v;
    gpofont = SDL_CreateRGBSurface(SDL_SRCCOLORKEY,128,128,pinfo->vfmt->BitsPerPixel,pinfo->vfmt->Rmask,pinfo->vfmt->Gmask,pinfo->vfmt->Bmask,pinfo->vfmt->Amask);
    SDL_SetColorKey( gpofont, SDL_SRCCOLORKEY, SDL_MapRGB(gpofont->format,0,0,0) );
    SDL_FillRect( gpofont, NULL, SDL_MapRGB(gpofont->format,0,0,0) );
    SDL_LockSurface( gpofont );
    for(u=0; u<128; u++)
        for(v=0; v<128; v++)
            if( gsfontraw[u+v*128]!=' ' )
                SDL_SetPixel( gpofont, u, v, 255, 255, 255 );
            else if( (u<127 && gsfontraw[(u+1)+(v+0)*128]!=' ')
                  || (u>0   && gsfontraw[(u-1)+(v+0)*128]!=' ')
                  || (v<127 && gsfontraw[(u+0)+(v+1)*128]!=' ')
                  || (v>0   && gsfontraw[(u+0)+(v-1)*128]!=' ') )
                SDL_SetPixel( gpofont, u, v, 0, 0, 1 ); 
    SDL_UnlockSurface( gpofont );
}

void SJF_DrawChar(SDL_Surface *surf, int x, int y, char c)
{
    SDL_Rect src;
    SDL_Rect dst;

    src.x = (c%16)*gnfontw;
    src.y = ((c-32)/16)*gnfonth;
    src.w = 8;
    src.h = 12;

    dst.x = x;
    dst.y = y;
    dst.w = 8;
    dst.h = 12;

    SDL_UpperBlit(gpofont,&src,surf,&dst);
}


void SJF_DrawText(SDL_Surface *surf, int x, int y, const char *s)
{
    SDL_Rect src;
    SDL_Rect dst;

    src.h = 12;
    dst.x = x;
    dst.y = y;
    dst.h = 12;

    while( *s )
    {
        src.x = (*s%16)*gnfontw;
        src.y = ((*s-32)/16)*gnfonth;
        src.w = gnfontspace[(Uint8)*s-32]-1;
        dst.w = src.w;
        SDL_UpperBlit(gpofont,&src,surf,&dst);
        dst.x += src.w;
        s++;
    }
}



void SDL_SetPixel(SDL_Surface *surf, int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
    Uint32 color = SDL_MapRGB(surf->format, R, G, B);
    switch (surf->format->BytesPerPixel)
    {
    case 1: // 8-bpp
        {
            Uint8 *bufp;
            bufp = (Uint8 *)surf->pixels + y*surf->pitch + x;
            *bufp = color;
        }
        break;
    case 2: // 15-bpp or 16-bpp
        {
            Uint16 *bufp;
            bufp = (Uint16 *)surf->pixels + y*surf->pitch/2 + x;
            *bufp = color;
        }
        break;
    case 3: // 24-bpp mode, usually not used
        {
            Uint8 *bufp;
            bufp = (Uint8 *)surf->pixels + y*surf->pitch + x * 3;
            if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
            {
                bufp[0] = color;
                bufp[1] = color >> 8;
                bufp[2] = color >> 16;
            } else {
                bufp[2] = color;
                bufp[1] = color >> 8;
                bufp[0] = color >> 16;
            }
        }
        break;
    case 4: // 32-bpp
        {
            Uint32 *bufp;
            bufp = (Uint32 *)surf->pixels + y*surf->pitch/4 + x;
            *bufp = color;
        }
        break;
    }
} 

