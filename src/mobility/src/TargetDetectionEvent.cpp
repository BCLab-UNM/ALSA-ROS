#include "TargetDetectionEvent.h"
#include <iostream>

using namespace std;

TargetDetectionEvent::TargetDetectionEvent( time_t t, float x, float y, int id)
{
  position = Coordinate(x, y, 0.0f, t);
}

time_t TargetDetectionEvent::getTime()
{
  return position.getTime();
}

float TargetDetectionEvent::getX()
{
  return position.getX();
}

float TargetDetectionEvent::getY()
{
  return position.getY();
}

int TargetDetectionEvent::getID()
{
  return id;
}

Coordinate* TargetDetectionEvent::getPositionPtr()
{
  return &position;
}

Coordinate TargetDetectionEvent::getPosition()
{
  return position;
}
