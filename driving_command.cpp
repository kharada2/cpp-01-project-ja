#include "driving_command.h"

#include <iostream>
#include <string>
#include <vector>

namespace DrivingCommand {

std::string ChangeDirectionLeft(const std::string& d) {
  std::string result;
  if (d == "North") {
    result = "West";
  } else if (d == "West") {
    result = "South";
  } else if (d == "South") {
    result = "East";
  } else {
    result = "North";
  }

  return result;
}

std::string ChangeDirectionRight(const std::string& d) {
  std::string result;

  if (d == "North") {
    result = "East";
  } else if (d == "East") {
    result = "South";
  } else if (d == "South") {
    result = "West";
  } else {
    result = "North";
  }
  return result;
}

void VdUpdatePosition(const char& command, VehicleState& vs) {
  if ((command != 'l' && command != 'r') && vs.u1_gasoline > 0.0f) {
    if (vs.direction == "North") {
      vs.player_position.y += vs.u1_speed;
    } else if (vs.direction == "East") {
      vs.player_position.x += vs.u1_speed;
    } else if (vs.direction == "South") {
      vs.player_position.y -= vs.u1_speed;
    } else if (vs.direction == "West") {
      vs.player_position.x -= vs.u1_speed;
    }
  }
}

int U1UpdateGasoline(const int u1_speed, const int u1_gasoline) { return std::max(u1_gasoline - u1_speed, 0); }

Position UpdatePosition(const Position& position, std::string direction, const int u1_speed) {
  Position result = {position.x, position.y};

  if (direction == "North") {
    result.y = position.y + u1_speed;
  } else if (direction == "East") {
    result.x = position.x + u1_speed;
  } else if (direction == "South") {
    result.y = position.y - u1_speed;
  } else if (direction == "West") {
    result.x = position.x - u1_speed;
  }

  return result;
}

void VdUpdateDrivingState(const char& command, VehicleState& vs) {
  switch (command) {
    case 'a':
      vs.u1_speed++;
      vs.player_position = UpdatePosition(vs.player_position, vs.direction, vs.u1_speed);
      vs.u1_gasoline = U1UpdateGasoline(vs.u1_speed, vs.u1_gasoline);
      break;

    case 'b':
      if (vs.u1_speed > 0) {
        vs.u1_speed--;
        vs.player_position = UpdatePosition(vs.player_position, vs.direction, vs.u1_speed);
        vs.u1_gasoline = U1UpdateGasoline(vs.u1_speed, vs.u1_gasoline);
      }
      break;

    case 'g':
      vs.player_position = UpdatePosition(vs.player_position, vs.direction, vs.u1_speed);
      vs.u1_gasoline = U1UpdateGasoline(vs.u1_speed, vs.u1_gasoline);
      break;

    case 's':
      vs.u1_speed = 0;
      break;

    case 'l':
      vs.direction = ChangeDirectionLeft(vs.direction);
      break;

    case 'r':
      vs.direction = ChangeDirectionRight(vs.direction);
      break;

    case 'm':
      // 地図の表示
      std::vector<std::vector<char>> map = RoadMap::VdGenerateMap();
      for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
          if (vs.player_position.x == j && vs.player_position.y == (map.size() - 1 - i)) {
            std::cout << "E ";
          } else {
            std::cout << map[i][j] << " ";
          }
        }
        std::cout << std::endl;
      }
      break;
  }

  return;
}

}  // namespace DrivingCommand