#ifndef Coordinate_h
#define Coordinate_h

#include <ctime>

class Coordinate
{
public:
    Coordinate();
    Coordinate(float x, float y, float z, time_t t);
    float getX();
    float getY();
    float getZ();
    time_t getTime();
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setTime(time_t t);
    float getDistance( Coordinate* end );
    float getAngle(Coordinate *mid, Coordinate* end );
    float getSpeed( Coordinate* end );

private:
    float x;
    float y;
    float z;
    time_t t;
};

#endif // Coordinate_h
