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

#define W 800
#define H 600
#define MULTIS 2
#define THREADS 8
#define PHOTONS 0


Uint32 gutime = 0;
Uint32 gutimenow = 0;

SDL_Surface *sdlscreen = NULL;
SDL_Surface *sdlrender = NULL;
SDL_Thread *thread;
const SDL_VideoInfo *pinfo;
PIXELMACHINE pixelmachine;
SJUI ui;
SJUI_HANDLE h_menu,h_render;

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
    int i;
    int w = W;
    int h = H;
    int multis = MULTIS;
    int threads = THREADS;
    int photons = PHOTONS;
    unsigned seed = (unsigned)-1;

    // Process cmd line args
    for(i=1; i<argc; i++)
    {
        if( argv[i][0]=='-' ) switch( argv[i][1] )
        {
        case 'w': w = atoi(argv[i]+2); break;
        case 'h': h = atoi(argv[i]+2); break;
        case 'm': multis = atoi(argv[i]+2); break;
        case 't': threads = atoi(argv[i]+2); break;
        case 'p': photons = atoi(argv[i]+2); break;
        case '-': printf( "Usage: [OPTION]... [SEED]\nRender ray-traced 3D images generated randomly with seed number SEED.\n\n  option default description\n  -wNUM  %7d Set image output width to NUM\n  -hNUM  %7d Set image output height to NUM\n  -mNUM  %7d Set multisampling level to NUM (level 2 recommended)\n  -tNUM  %7d Parallelize with NUM threads\n  -pNUM  %7d Simulate lighting with NUM million photons!\n",W,H,MULTIS,THREADS,PHOTONS ), exit(0);
        default: fprintf( stderr, "Halt! -%c isn't one of my options!\nUse --help for help.\n", argv[i][1] ), exit(-1);
        }
        else if( seed==(unsigned)-1 )
        {
            seed = atoi(argv[i]);
            if( !seed )
                fprintf( stderr, "Halt! SEED ought to be a positive number, not %s\n", argv[i] ), exit(-1);
        }
        else
            fprintf( stderr, "Halt! I'm confused by cmd line argument #%d: %s\n", i, argv[i] ), exit(-1);
    }
    if( w<1 ) w=W;
    if( h<1 ) h=H;
    if( multis<1 ) multis=MULTIS;
    if( threads<1 ) threads=THREADS;
    if( photons<1 ) photons=PHOTONS;

    // Use time as seed if not otherwise specified
    if( seed==(unsigned)-1 )
        seed = (unsigned)time(NULL);

    // Init SDL
    if( SDL_Init( SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO ) < 0 || !SDL_GetVideoInfo() )
        return 0;

    // Create Window
    SetVideo( w, h );
    SDL_WM_SetCaption("PixelMachine", NULL);

    pinfo = SDL_GetVideoInfo();

    // font init
    SJF_Init(pinfo);

    //ui setup
    ui.init();
    h_menu = ui.new_control(0,0,0,0);
    h_render = ui.new_control(h_menu,80,15,SJUIF_EXTENDSV);
    ui.set_caption(h_menu,"Click to render...");
    ui.set_caption(h_render,"Loading");

    //pm setup
    pixelmachine.init(seed,w,h,multis,threads,photons);

    // MAIN LOOP
    while( 1 )
    {
        while( SDL_PollEvent(&event) ) switch(event.type)
        {
        case SDL_VIDEOEXPOSE:
            ;
            break;
        case SDL_VIDEORESIZE:
            SetVideo( event.resize.w, event.resize.h );
            break;
        case SDL_MOUSEBUTTONDOWN:
            if( !pixelmachine.running )
                thread = SDL_CreateThread(run_pixel_machine,NULL);
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
            SDL_UnlockSurface(sdlrender);
        }
        SDL_BlitSurface(sdlrender,NULL,sdlscreen,NULL);
    }

    ui.set_caption(h_render,pixelmachine.statustext);
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

