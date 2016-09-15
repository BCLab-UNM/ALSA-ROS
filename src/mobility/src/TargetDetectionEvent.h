#ifndef TargetDetectionEvent_h
#define TargetDetectionEvent_h

#include <ctime>
#include "Coordinate.h"

class TargetDetectionEvent
{
public:
TargetDetectionEvent(time_t t, float x, float y, int id);

time_t getTime();
float getX();
float getY();
int getID();
Coordinate getPosition();
Coordinate* getPositionPtr();

private:

Coordinate position;
  int id;

};

#endif //TargetDetectionEvent_h
