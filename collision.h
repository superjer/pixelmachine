/*
** collision.h
**
** Some nice vector functions and stuff... for PixelMachine
** by SuperJer
**
** Email = superjer@superjer.com
** Web   = http://www.superjer.com/
**
** You can do whatever you like with this code, I don't care,
** just please recognize me as the original author. :)
**
*/


#ifndef __COLLISION_H__
#define __COLLISION_H__


#include <math.h>


#define NO_COLLISION -1.0


struct V
{
    double x;
    double y;
    double z;
};

struct COLOR
{
    double r;
    double g;
    double b;
    double a;
};

struct SPHERE
{
    V center;
    double radius;
    COLOR color;
};


V &add( V &out, const V &a, const V &b );
V &subtract( V &out, const V &a, const V &b );
V &cross( V &out, const V &a, const V &b );
V &scale( V &out, double n );
V &normalize( V &out, double n );
V &mirror( V &out, const V &in, const V &mirror );
void CollideRaySphere( double &t, const V &o, const V &v, const V &p, const double &r );



#endif //__COLLISION_H__

