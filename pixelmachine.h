
#ifndef __PIXELMACHINE_H__
#define __PIXELMACHINE_H__


#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <memory.h>
#include <time.h>

#ifndef unix
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

#include <SDL/SDL.h>

#include "font.h"
#include "collision.h"

#include "dSFMT.h"


//#define PHOTONMODE


#ifndef PHOTONMODE
#define TERDIV  8   // terrain divisions (powers of 2 ONLY!)
#define TERSECS 16    // sections per division
                     // this will work out to (TERDIV*TERSECS+1)^3 cubes!!
#define FALLOFF 600000.0
#else
#define TERDIV  1   // terrain divisions (powers of 2 ONLY!)
#define TERSECS 3    // sections per division
#define FALLOFF 30000.0
#endif


#define BSIZE (TERDIV*TERSECS+1)
#define SQSIZE (1000.0/(double)BSIZE)

#define PREVIEWW 80
#define PREVIEWH 60

#define MAXBOUNCE 20

#define XY 0
#define XZ 1
#define YZ 2

#define SCATTER 0.000003

#define SUNS 1

#ifndef PHOTONMODE
#define SPHERES 80
#else
#define SPHERES 6
#endif


#define PATCHDIM 250
#define PHOTONRADIUS 1.0

#define PX0 499.0
#define PX1 751.0
#define PY0 499.0
#define PY1 751.0
#define PZ0 499.0
#define PZ1 751.0

#define NO_PIXEL -1

#define MODE_CAMRAY 0
#define MODE_LIGHTTEST 1
#define MODE_PHOTON 2

#define PHOTONS 20000000

#define INVRAND ((double)2.0/(double)RAND_MAX)


struct PIXELMACHINE
{
    struct RENDER_ARGS
    {
        V cam;
        V tar;
        int w,h;
        int l,r,t,b;
        bool quiet;
        SDL_mutex *lock;
        int threadid;
        PIXELMACHINE *pm;
    };
    struct PHOTON_ARGS
    {
        COLOR c;
        int ration;
        unsigned seed;
        SDL_mutex *lock;
        int threadid;
        PIXELMACHINE *pm;
    };
    struct P
    {
        V v;
        int i;
        P *n;
    };
    struct REG
    {
        int l,r,t,b;
    };
    P *patch[PATCHDIM][PATCHDIM][PATCHDIM];
    P **patchterm[PATCHDIM][PATCHDIM][PATCHDIM];
    int tempx,tempy,tempz;
    double terrain[BSIZE][BSIZE];
    unsigned char *img;
    COLOR *dimg;
    int w;
    int h;
    int multis;
    int threads;
    int frames;
    unsigned seed;
    COLOR blocks[BSIZE][BSIZE][BSIZE];
    double blocksize;
    double tarw;
    double pixpitch;
    double subpitch;
    V sun[SUNS];
    SPHERE sphere[SPHERES+1];
    bool *busy;
    bool running;
    V cam;
    V tar;
    REG *regions;
    int reg_count;
    int reg_alloc;
    SDL_mutex *lock;
    bool cancel;
    char statustext[80];

    PIXELMACHINE();
    ~PIXELMACHINE();

    void init(unsigned seed,int w,int h,int multis,int threads);
    void build_terrain();
    void generate_objects();
    void run();
    void savebmp( const char *filename, int w, int h );
    void render( int w, int h, bool quiet );
    void push_region( RENDER_ARGS *ra );
    bool pop_region( SDL_Rect *rect );
    int render_thread( void *data );
    int photon_thread( void *data );
    void render_photons( V cam, V tar, int w, int h, bool quiet );
    COLOR &raytrace( COLOR &color, const V &cam, const V &ray, int mode, int bounce, int pixelindex=NO_PIXEL );
    void attach( int pixelindex, const V &hit );
    void feed( const COLOR &c, const V &hit );
};




int ext_render_thread( void *data );
int ext_photon_thread( void *data );


#endif //__PIXELMACHINE_H__
