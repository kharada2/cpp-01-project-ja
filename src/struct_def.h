#include <string>
#include <vector>

typedef struct {
  int x;
  int y;
} Position;

typedef struct {
  Position player_position;
  std::string direction;
  int s1_speed;     // [m/s]
  int s1_gasoline;  // [%]
} VehicleState;
