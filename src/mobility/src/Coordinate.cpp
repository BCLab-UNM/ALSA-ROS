#include "Coordinate.h"
#include <math.h>

Coordinate::Coordinate()
{
    x = 0;
    y = 0;
    z = 0;
    t = 0;
}

Coordinate::Coordinate(float x_pos, float y_pos, float z_pos, time_t time)
{
    x = x_pos;
    y = y_pos;
    z = z_pos;
    t = time;
}

float Coordinate::getX()
{
    return x;
}

float Coordinate::getY()
{
    return y;
}

float Coordinate::getZ()
{
    return z;
}

time_t Coordinate::getTime()
{
    return t;
}

void Coordinate::setX(float x_c)
{
    x = x_c;
}

void Coordinate::setY( float y_c )
{
    y = y_c;
}

void Coordinate::setZ( float z_c )
{
    z = z_c;
}

void Coordinate::setTime(time_t t_c)
{
    t = t_c;
}

float Coordinate::getDistance( Coordinate* end )
{
    float v_x = (this->getX() - end->getX());
    float v_y = (this->getY() - end->getY());
    float v_z = (this->getZ() - end->getZ());
    return sqrt( v_x*v_x + v_y*v_y + v_z*v_z );
}

// Used the standard vector calulus formula (cosine version) for angles in 3D.
float Coordinate::getAngle( Coordinate* mid, Coordinate* end )
{
    Coordinate A = *this;
    Coordinate B = *mid;
    Coordinate C = *end;

    float AB[] = {A.getX()-B.getX(), A.getY()-B.getY(), A.getZ()-B.getZ()};
    float BC[] = {C.getX()-B.getX(), C.getY()-B.getX(), C.getZ()-B.getX()};

    // Make unit vectors
    float ABmag = sqrt(AB[0]*AB[0]+AB[1]*AB[1]+AB[2]*AB[2]);
    float BCmag = sqrt(BC[0]*BC[0]+BC[1]*BC[1]+BC[2]*BC[2]);

    float ABunit[] = {AB[0]/ABmag, AB[1]/ABmag, AB[2]/ABmag};
    float BCunit[] = {BC[0]/BCmag, BC[1]/ABmag, BC[2]/BCmag};

    float dotprod = ABunit[0]*BCunit[0] + ABunit[1]*BCunit[1] + ABunit[2]*BCunit[2];

    float angle = acos(dotprod);

    return angle;

}

