/*
** PixelMachine
** v 0.2.20071108
**
** A ray-traced 3D renderer by SuperJer
**
** Email = superjer@superjer.com
** Web   = http://www.superjer.com/
**
**
**
*/

#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>
#include <time.h>

//#ifndef unix
//#include <direct.h>
//#endif

#include <SDL/SDL.h>

#include "pixelmachine.h"
#include "sjui.h"


#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define SWAP(t,a,b) {t SWAP_temp = a;a = b;b = SWAP_temp;}


Uint32 gutime = 0;
Uint32 gutimenow = 0;

SDL_Surface *sdlscreen = NULL;
SDL_Surface *sdlrender = NULL;
SDL_Thread *thread;
const SDL_VideoInfo *pinfo;
PIXELMACHINE pixelmachine;
SJUI ui;

int run_pixel_machine( void *data );
void Render();
void SetVideo( const int nw, const int nh );
bool InRect( const SDL_Rect *porect, const int nx, const int ny );
void Cleanup();


int main( int argc, char* argv[] )
{
    SDL_Event event;
    Uint32 u;
    Uint32 v;

    // Init SDL
    if( SDL_Init( SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO ) < 0 || !SDL_GetVideoInfo() )
        return 0;

    // Create Window
    SetVideo( 400, 300 );
    SDL_WM_SetCaption("PixelMachine", NULL);

    pinfo = SDL_GetVideoInfo();

    // font init
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

    //pm setup
    pixelmachine.w = 400;
    pixelmachine.h = 300;
    pixelmachine.multis = 1;

    //ui setup
    ui.init();
    SJUI_HANDLE h_menu = ui.new_control(0,0,0,0);
    SJUI_HANDLE h_render = ui.new_control(h_menu,150,20,SJUIF_EXTENDSV);
    ui.set_caption(h_render,"Render");

    // MAIN LOOP
    while( 1 )
    {
        while( SDL_PollEvent( &event ) )
            switch( event.type )
            {
            case SDL_VIDEOEXPOSE:
                //Render();
                break;
            case SDL_VIDEORESIZE:
                SetVideo( event.resize.w, event.resize.h );
                //Render();
                break;
            case SDL_MOUSEBUTTONDOWN:
                if( !pixelmachine.running )
                {
                    thread = SDL_CreateThread(run_pixel_machine,NULL);
                }
                break;
            case SDL_KEYDOWN:
                ;
                break;
            case SDL_QUIT:
                pixelmachine.cancel = true;
                SDL_WaitThread(thread,NULL);
                Cleanup();
                break;
            }

        gutimenow = SDL_GetTicks();
        if( (Uint32)(gutimenow-gutime)>50 )
        {
            Render();
            gutime = gutimenow;
        }

        // chill out for a bit
        SDL_Delay(10);
    }

    return 0;
}


int run_pixel_machine( void *data )
{
    pixelmachine.run();
    return 0;
}


void Render()
{
    int i,j,m,n;
    const SDL_VideoInfo *info;
    SDL_Rect rect;
    Uint32 color;
    int winw;
    int winh;
    double ratiox;
    double ratioy;

    info = SDL_GetVideoInfo();
    winw = info->current_w;
    winh = info->current_h;

    if( sdlrender )
    {
        if( !SDL_LockSurface(sdlrender) )
        {
            while( pixelmachine.pop_region(&rect) )
            {
                for(i=rect.x; i<rect.x+rect.w; i++)
                    for(j=rect.y; j<rect.y+rect.h; j++)
                    {
                        Uint8 b = pixelmachine.img[(i+j*pixelmachine.w)*3+0];
                        Uint8 g = pixelmachine.img[(i+j*pixelmachine.w)*3+1];
                        Uint8 r = pixelmachine.img[(i+j*pixelmachine.w)*3+2];
                        ratiox = (double)winw/(double)pixelmachine.w;
                        ratioy = (double)winh/(double)pixelmachine.h;
                        for(m=(int)(i*ratiox);m<(int)((i+1)*ratiox);m++)
                            for(n=(int)(j*ratioy);n<(int)((j+1)*ratioy);n++)
                                SDL_SetPixel(sdlrender,m,n,r,g,b);
                    }
            }
            SDL_UnlockSurface(sdlrender);
        }

        SDL_BlitSurface(sdlrender,NULL,sdlscreen,NULL);
    }
    //orect.x = 0;
    //orect.y = 0;
    //orect.w = nwinw;
    //orect.h = 16;
    //ucolor = 0xCCCCCC;
    //SDL_FillRect(sdlscreen,&orect,ucolor);

    ui.paint(sdlscreen);

    SDL_Flip(sdlscreen);
}



void SetVideo( int nw, int nh )
{
    bool different = (!pinfo || nw!=pinfo->current_w || nh!=pinfo->current_h);

    sdlscreen = SDL_SetVideoMode( nw, nh, SDL_GetVideoInfo()->vfmt->BitsPerPixel, SDL_RESIZABLE|SDL_DOUBLEBUF );
    pinfo = SDL_GetVideoInfo();

    if( different && sdlrender )
        SDL_FreeSurface(sdlrender);
    if( different )
        sdlrender = SDL_CreateRGBSurface(0,nw,nh,pinfo->vfmt->BitsPerPixel,pinfo->vfmt->Rmask,pinfo->vfmt->Gmask,pinfo->vfmt->Bmask,pinfo->vfmt->Amask);
}


bool InRect( const SDL_Rect *porect, const int nx, const int ny )
{
    return ( nx>=porect->x && nx<(porect->x+porect->w) &&
             ny>=porect->y && ny<(porect->y+porect->h) );
}


void Cleanup()
{
    ui.destroy();
    SDL_Quit();
    exit(0);
}

