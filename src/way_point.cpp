#include "way_point.h"

#include <iostream>

namespace WayPoint {
bool WayPointCheck(const std::vector<std::vector<char>>& map, VehicleState& vehicle_state) {
  const char way_point = map[vehicle_state.player_position.y][vehicle_state.player_position.x];

  switch (way_point) {
    case 'G':
      return true;

    case 'F':
      if (vehicle_state.fuel_count > 1) {
        std::cout << "ガソリンスタンドです。10リットル給油できます。給油しますか？ YES:y, NO:n" << std::endl;
        char command;
        std::cin >> command;
        if (command = 'y') {
          vehicle_state.fuel += 20;
          vehicle_state.fuel_count -= 1;
        }
      } else {
        std::cout << "給油回数が上限に達しているので、給油できません。" << std::endl;
      }
      break;
    case 'H':
      // 料金所
      if (vehicle_state.speed_limit == 1) {
        std::cout << "高速道路入口です。速度上限は２です。" << std::endl;
        vehicle_state.money -= 5;
        vehicle_state.speed_limit = 2;
      } else {
        std::cout << "高速道路を降りました。速度上限は１です。" << std::endl;
        vehicle_state.money -= 5;
        vehicle_state.speed_limit = 1;
        vehicle_state.speed = 1;
      }
      break;
  }

  return false;
}

}  // namespace WayPoint
