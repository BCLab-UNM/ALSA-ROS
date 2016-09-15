// This is the Adaptive Levy Walk Controller.
// This class estimates the target distribution and generates a Levy search pattern with the appropriate exponent

#ifndef ALSAController_h
#define ALSAController_h

#include <utility>
#include <tuple>
#include <vector>
#include "TargetDetectionEvent.h"

using namespace std;

struct GoalState
{
  float x;
  float y;
  float yaw;
};

class ALSAController
{
 public:
  ALSAController();
  GoalState getNextGoalPosition(pair<float, float> current_position);
  void addDetectedTarget(time_t t, float x, float y, int id);
  void updateStrategy(); // Update the levy exponent given the state of the target vector
  float getMu();
  float getHopkinsIndex();
  ~ALSAController();

 private:
  float calcHopkinsIndex(vector<Coordinate*> S, float max_x, float min_x, float max_y, float min_y, float max_z, float min_z);
  float mapHopkinsToMu(float hopkins_index);
  float min_step_length = 0.5; // Define the minimum step length to be 5 cm
  float mu = 1.5; // mu is the PDF inverse power law exponent
  float hopkins_index = 1;
  vector<TargetDetectionEvent> targets;
};

#endif // End ALSAController_h
