#include <iostream>
#include <string>
#include <vector>

#include "define_const.h"
#include "driving_command.h"
#include "way_point.h"

namespace Display {
std::string WeatherJudge(const VehicleState& vehicle_state) {
  std::string result = "SUNNY";
  if (vehicle_state.is_snow) {
    std::cout << "SHOW " << std::endl;
    std::string result = "SNOW";
  }

  return result;
}

std::string ReplaceCharToStringForViewer(char in, const VehicleState& vehicle_state) {
  std::string out = "   ";

  if (in == '#') {
    out = DIAPLAY_EMPTY;
  } else if (in == 'H') {
    out = DIAPLAY_HIGHWAY;
  } else if (in == 'F') {
    out = DIAPLAY_GAS_STATION;
  } else if (in == 'G') {
    out = DIAPLAY_GOAL;
  } else if (in == 'C') {
    out = DIAPLAY_CONVINI;
  } else if (in == ' ') {
    out = DIAPLAY_ROAD;
  }

  if (vehicle_state.is_snow) {
    out = DIAPLAY_ROAD;
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
          std::cout << ReplaceCharToStringForViewer(map[y][x], vehicle_state);
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
          std::cout << ReplaceCharToStringForViewer(map[y][x], vehicle_state);
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
          std::cout << ReplaceCharToStringForViewer(map[y][x], vehicle_state);
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
          std::cout << ReplaceCharToStringForViewer(map[y][x], vehicle_state);
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
  std::cout << "WEATHER     :  " << WeatherJudge(vehicle_state) << std::endl;
}

void DisplayStatus(const std::vector<std::vector<char>>& map, const VehicleState& vehicle_state) {
  std::cout << "-------------------------" << std::endl;
  std::cout << "| TIME         | " << vehicle_state.time << std::endl;
  std::cout << "| SPEED        | " << vehicle_state.speed << std::endl;
  std::cout << "| FUEL         | " << vehicle_state.fuel << std::endl;
  // std::cout << "| DIRECTION    | " << vehicle_state.direction << std::endl;
  std::cout << "| DIST TO GOAL | "
            << std::abs(WayPoint::DistanceToLandMark(map, 'G', vehicle_state).y) +
                   std::abs(WayPoint::DistanceToLandMark(map, 'G', vehicle_state).x)
            << std::endl;
  std::cout << "-------------------------" << std::endl;
  std::cout << std::endl;
}

}  // namespace Display
