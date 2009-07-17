/*
** collision.cpp
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

#include "collision.h"


V &add( V &out, const V &a, const V &b )
{
    out.x = a.x + b.x;
    out.y = a.y + b.y;
    out.z = a.z + b.z;
    return out;
}


V &subtract( V &out, const V &a, const V &b )
{
    out.x = a.x - b.x;
    out.y = a.y - b.y;
    out.z = a.z - b.z;
    return out;
}



V &cross( V &out, const V &a, const V &b )
{
    out.x = a.y*b.z - a.z*b.y;
    out.y = a.z*b.x - a.x*b.z;
    out.z = a.x*b.y - a.y*b.x;
    return out;
}


V &scale( V &out, double n )
{
    out.x *= n;
    out.y *= n;
    out.z *= n;
    return out;
}


V &normalize( V &out, double n )
{
    double l = sqrt(out.x*out.x + out.y*out.y + out.z*out.z);
    out.x *= n/l;
    out.y *= n/l;
    out.z *= n/l;
    return out;
}


V &mirror( V &out, const V &in, const V &mirror )
{
    V perp1, perp2;
    cross( perp1, in, mirror );
    cross( perp2, perp1, mirror );
    
    const double &a = mirror.x;
    const double &b = perp2.x;
    const double &c = in.x;

    const double &x = mirror.y;
    const double &y = perp2.y;
    const double &z = in.y;

    const double &i = mirror.z;
    const double &j = perp2.z;
    const double &k = in.z;
    
    double n, m;
    if( a > -0.0001 && a < 0.0001 )
    {
        if( i > -0.0001 && i < 0.0001 )
        {
            out.x = -in.x;
            out.y =  in.y;
            out.z = -in.z;
            return out;
        }
        else
        {
            n = (z - (x*k)/i)/(y - (x*j)/i);
            m = (k - (j*n))/i;
        }
    }
    else
    {
        n = (z - (x*c)/a)/(y - (x*b)/a);
        m = (c - (b*n))/a;
    }

    V v1, v2;
    v1 = mirror;
    v2 = perp2;

    scale( v1, m );
    scale( v2, n );

    subtract( out, v1, v2 );
    return out;
}



// This function is part of the SPARToR game engine by SuperJer.com
void CollideRaySphere( double &t, const V &o, const V &v, const V &p, const double &r )
{
    double a, b, c, d, ox, oy, oz;

    // check that v is even headed toward the sphere first
    {
        if( (v.x>0.0 && o.x>p.x+r) || (v.x<0.0 && o.x<p.x-r) ||
            (v.y>0.0 && o.y>p.y+r) || (v.y<0.0 && o.y<p.y-r) || 
            (v.z>0.0 && o.z>p.z+r) || (v.z<0.0 && o.z<p.z-r) )
        {
            t = NO_COLLISION;
            return;
        }
    }

    // quadratic formula
    ox = o.x - p.x;
    oy = o.y - p.y;
    oz = o.z - p.z;
    a = 2.0*(v.x*v.x + v.y*v.y + v.z*v.z);
    b = 2.0*(v.x*ox + v.y*oy + v.z*oz);
    c = ox*ox + oy*oy + oz*oz - r*r;

    d = b*b - 2.0*a*c; // determinant
    if( d < 0.0 ) // no intersection at all
    {
        t = NO_COLLISION;
        return;
    }
    a = 1.0 / a;
    d = sqrt( d );
    t = (-d - b) * a;
    if( t >= 0.0 ) return; // smaller root wins
    t = ( d - b) * a;
    if( t >= 0.0 ) return; // bigger root wins
    t = NO_COLLISION;
    return; // no root in range
}
