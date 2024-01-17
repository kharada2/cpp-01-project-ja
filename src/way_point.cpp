#include "way_point.h"

#include <iostream>

#include "define_const.h"

namespace WayPoint {
void WayPointCheck(const std::vector<std::vector<char>>& map, VehicleState& vehicle_state, const char& command) {
  const char way_point = map[vehicle_state.player_position.y][vehicle_state.player_position.x];

  switch (way_point) {
    case 'G':  // 目的地
      vehicle_state.is_goal = true;
      break;

    case 'F':  // ガソリンスタンド
      std::cout << command << std::endl;
      if (vehicle_state.fuel_count > 0 && (vehicle_state.player_position.x != vehicle_state.player_position_pre.x ||
                                           vehicle_state.player_position.y != vehicle_state.player_position_pre.y)) {
        std::cout << "GAS STATION. CAN REFUEL 10. DO YOU WANT TO REFUEL?  YES:y, NO:n" << std::endl;
        char c;
        std::cin >> c;
        if (c = 'y') {
          vehicle_state.fuel = std::min(vehicle_state.fuel + FUEL_CHARGE, FUEL_MAX);
          vehicle_state.fuel_count -= 1;
          std::cout << "FUEL BECOMES " << vehicle_state.fuel << std::endl;
        } else {
          std::cout << "THE NUMBER OF REFUELS HAS REACHED THE LIMIT, CANNOT REFUEL." << std::endl;
        }
      }
      break;

    case 'H':  // 高速道路
      if (vehicle_state.speed_limit == 1) {
        std::cout << "HIGHWAY" << std::endl;
        std::cout << "SPEED LIMIT BECOMES " << SPEED_HIGHWAY << "." << std::endl;
        vehicle_state.speed_limit = SPEED_HIGHWAY;
      }
      break;

    default:
      if (vehicle_state.speed_limit == SPEED_MAX) {
        vehicle_state.speed_limit = SPEED_NORMAL;
        vehicle_state.speed = SPEED_NORMAL;
        std::cout << "EXIT HIGHWAY" << std::endl;
        std::cout << "SPEED LIMIT BECOMES " << vehicle_state.speed_limit << "." << std::endl;
      }
      break;
  }

  return;
}

Position DistanceToLandMark(const std::vector<std::vector<char>>& map, const char landmark,
                            const VehicleState& vehicle_state) {
  Position DistanceToLandMark;
  Position Goal;
  // ランドマークの座標
  for (int y = 0; y < map.size(); y++) {
    for (int x = 0; x < map[y].size(); x++) {
      if (map[y][x] == landmark) {
        Goal.x = x;
        Goal.y = y;
      }
    }
  }

  // 距離
  DistanceToLandMark.x = Goal.x - vehicle_state.player_position.x;
  DistanceToLandMark.y = Goal.y - vehicle_state.player_position.y;

  return DistanceToLandMark;
}

}  // namespace WayPoint
