#include <iostream>
#include <string>
#include <vector>

#include "define_const.h"
#include "driving_command.h"
#include "way_point.h"

namespace Display {
std::string ReplaceCharToStringForViewer(char in) {
  std::string out = "   ";
  if (in == '#') {
    out = DIAPLAY_EMPTY;
  } else if (in == 'H') {
    out = " ◇ ";
  } else if (in == 'F') {
    out = " F ";
  }

  return out;
}

void VdShowMap(const std::vector<std::vector<char>>& map, const VehicleState& vehicle_state) {
  std::cout << "====== MAP ======" << std::endl;
  for (int y = 0; y < map.size(); y++) {
    std::cout << "  ";
    for (int x = 0; x < map[y].size(); x++) {
      if (vehicle_state.player_position.x == x && vehicle_state.player_position.y == y) {
        std::cout << vehicle_state.direction << " ";
      } else {
        std::cout << map[y][x] << " ";
      }
    }
    std::cout << std::endl;
  }
}
void ShowDriverView(const std::vector<std::vector<char>>& map, const VehicleState& vehicle_state) {
  if (vehicle_state.direction == "NOTRH") {
    for (int y = 0; y < map.size(); y++) {
      bool align = false;
      for (int x = 0; x < map[0].size(); x++) {
        if (vehicle_state.player_position.x == x && vehicle_state.player_position.y == y) {
          std::cout << DIAPLAY_EGO_CAR;
        } else if (std::abs(vehicle_state.player_position.x - x) <= DISPLAY_RANGE &&
                   std::abs(vehicle_state.player_position.y - y) <= DISPLAY_RANGE) {
          std::cout << ReplaceCharToStringForViewer(map[y][x]);
          align = true;
        } else {
          // nothing
        }
      }
      if (align) {
        std::cout << std::endl;
      }
    }
  } else if (vehicle_state.direction == "SOUTH") {
    for (int y = map.size() - 1; y > 0; y--) {
      bool align = false;
      for (int x = map[0].size() - 1; x > 0; x--) {
        if (vehicle_state.player_position.x == x && vehicle_state.player_position.y == y) {
          std::cout << DIAPLAY_EGO_CAR;
        } else if (std::abs(vehicle_state.player_position.x - x) <= DISPLAY_RANGE &&
                   std::abs(vehicle_state.player_position.y - y) <= DISPLAY_RANGE) {
          std::cout << ReplaceCharToStringForViewer(map[y][x]);
          align = true;
        } else {
          // nothing
        }
      }
      if (align) {
        std::cout << std::endl;
      }
    }
  } else if (vehicle_state.direction == "EAST") {
    for (int x = map[0].size() - 1; x > 0; x--) {
      bool align = false;
      for (int y = 0; y < map.size(); y++) {
        if (vehicle_state.player_position.x == x && vehicle_state.player_position.y == y) {
          std::cout << DIAPLAY_EGO_CAR;
        } else if (std::abs(vehicle_state.player_position.x - x) <= DISPLAY_RANGE &&
                   std::abs(vehicle_state.player_position.y - y) <= DISPLAY_RANGE) {
          std::cout << ReplaceCharToStringForViewer(map[y][x]);
          align = true;
        } else {
          // nothing
        }
      }
      if (align) {
        std::cout << std::endl;
      }
    }
  } else if (vehicle_state.direction == "WEST") {
    for (int x = 0; x < map[0].size(); x++) {
      bool align = false;
      for (int y = map.size() - 1; y > 0; y--) {
        if (vehicle_state.player_position.x == x && vehicle_state.player_position.y == y) {
          std::cout << DIAPLAY_EGO_CAR;
        } else if (std::abs(vehicle_state.player_position.x - x) <= DISPLAY_RANGE &&
                   std::abs(vehicle_state.player_position.y - y) <= DISPLAY_RANGE) {
          std::cout << ReplaceCharToStringForViewer(map[y][x]);
          align = true;
        } else {
          // nothing
        }
      }
      if (align) {
        std::cout << std::endl;
      }
    }
  }
  std::cout << "SPEED LIMIT :  " << vehicle_state.speed_limit << std::endl;
}

void DisplayStatus(const std::vector<std::vector<char>>& map, const VehicleState& vehicle_state) {
  std::cout << "-------------------------" << std::endl;
  std::cout << "| TIME         | " << vehicle_state.time << std::endl;
  std::cout << "| SPEED        | " << vehicle_state.speed << std::endl;
  std::cout << "| FUEL         | " << vehicle_state.fuel << std::endl;
  std::cout << "| REFUEL COUNT | " << vehicle_state.fuel_count << std::endl;
  std::cout << "| DIRECTION    | " << vehicle_state.direction << std::endl;
  std::cout << "| DIST TO GOAL | "
            << std::abs(WayPoint::DistanceToLandMark(map, 'G', vehicle_state).y) +
                   std::abs(WayPoint::DistanceToLandMark(map, 'G', vehicle_state).x)
            << std::endl;
  std::cout << "-------------------------" << std::endl;
  std::cout << std::endl;

  // std::cout << "【自車状態】 TIME:" << vehicle_state.time << ", "
  //           << "速度:" << vehicle_state.speed << "("
  //           << "制限速度:" << vehicle_state.speed_limit << ")  "
  //           << "燃料:" << vehicle_state.fuel << "("
  //           << "給油残り回数 :" << vehicle_state.fuel_count << ")  " << std::endl;
  // std::cout << "【参考情報】前方方角:" << vehicle_state.direction << ", "
  //           << "目的地までの距離:"
  //           << std::abs(WayPoint::DistanceToLandMark(map, 'G', vehicle_state).y) +
  //                  std::abs(WayPoint::DistanceToLandMark(map, 'G', vehicle_state).x)
  //           << std::endl;
}

}  // namespace Display
