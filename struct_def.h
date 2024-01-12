#include <string>
#include <vector>

typedef struct {
  int x;
  int y;
} Position;

typedef struct {
  Position player_position;
  std::string direction;
  int u1_speed;     // [m/s]
  int u1_gasoline;  // [%]
} VehicleState;
