#include "way_point.h"

#include <iostream>

namespace WayPoint {
bool WayPointCheck(const std::vector<std::vector<char>>& map, VehicleState& vehicle_state) {
  const char way_point = map[vehicle_state.player_position.y][vehicle_state.player_position.x];

  switch (way_point) {
    case 'G':
      return true;

    case 'F':
      std::cout << "給油完了" << std::endl;
      vehicle_state.fuel += 10;
      vehicle_state.money -= 5;

    case 'H':
      // 料金所
      vehicle_state.money -= 5;
      vehicle_state.speed_limit = 3;

    case 'E':
      // 高速出口
      vehicle_state.speed_limit = 2;
  }

  return false;
}

}  // namespace WayPoint
