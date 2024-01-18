#include <string>
#include <vector>

#ifndef DEF_H
#define DEF_H

typedef struct {
  int x;
  int y;
} Position;

typedef struct {
  Position player_position;
  Position player_position_pre;
  std::string direction;
  int speed;  // [m/s]
  int fuel;   // [%]
  int time;
  int money;
  int speed_limit;
  int fuel_count;
  int one_step_dist;
  bool is_goal;
  bool is_snow;
  bool is_rain;
} VehicleState;

#endif
