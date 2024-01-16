#include "way_point.h"

#include <iostream>

namespace WayPoint {
bool WayPointCheck(const std::vector<std::vector<char>>& map, VehicleState& vehicle_state, const char& command) {
  const char way_point = map[vehicle_state.player_position.y][vehicle_state.player_position.x];

  switch (way_point) {
    case 'G':  // 目的地
      return true;

    case 'F':  // ガソリンスタンド
      std::cout << command << std::endl;
      if (vehicle_state.fuel_count > 0 && (vehicle_state.player_position.x != vehicle_state.player_position_pre.x ||
                                           vehicle_state.player_position.y != vehicle_state.player_position_pre.y)) {
        std::cout << "ガソリンスタンドです。10リットル給油できます。給油しますか？ YES:y, NO:n" << std::endl;
        char c;
        std::cin >> c;
        if (c = 'y') {
          vehicle_state.fuel += 20;
          vehicle_state.fuel_count -= 1;
          std::cout << "給油後の燃料は" << vehicle_state.fuel << "です。" << std::endl;
        } else {
          std::cout << "給油回数が上限に達しているので、給油できません。" << std::endl;
        }
      }
      break;

    case 'H':  // 高速道路
      if (vehicle_state.speed_limit == 1) {
        std::cout << "高速道路です。【速度制限２】" << std::endl;
        vehicle_state.speed_limit = 2;
      }
      break;

    default:
      if (vehicle_state.speed_limit == 2) {
        std::cout << "高速道路を降りました。【速度制限１】" << std::endl;
        vehicle_state.speed_limit = 1;
        vehicle_state.speed = 1;
      }
      break;
  }

  return false;
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
