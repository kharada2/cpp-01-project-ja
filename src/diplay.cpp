#include <iostream>
#include <string>
#include <vector>

#include "driving_command.h"

namespace Display {
void VdShowMap(const std::vector<std::vector<char>>& map, const VehicleState& vehicle_state) {
  for (int y = 0; y < map.size(); y++) {
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
          std::cout << "↑ ";
        } else if (std::abs(vehicle_state.player_position.x - x) <= 3 &&
                   std::abs(vehicle_state.player_position.y - y) <= 3) {
          std::cout << map[y][x] << " ";
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
          std::cout << "↑ ";
        } else if (std::abs(vehicle_state.player_position.x - x) <= 3 &&
                   std::abs(vehicle_state.player_position.y - y) <= 3) {
          std::cout << map[y][x] << " ";
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
          std::cout << "↑ ";
        } else if (std::abs(vehicle_state.player_position.x - x) <= 3 &&
                   std::abs(vehicle_state.player_position.y - y) <= 3) {
          std::cout << map[y][x] << " ";
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
          std::cout << "↑ ";
        } else if (std::abs(vehicle_state.player_position.x - x) <= 3 &&
                   std::abs(vehicle_state.player_position.y - y) <= 3) {
          std::cout << map[y][x] << " ";
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
}

}  // namespace Display
