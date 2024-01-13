#include "driving_command.h"

#include <iostream>
#include <string>
#include <vector>

namespace DrivingCommand {
std::string ChangeDirectionLeft(const std::string& d) {
  std::string result;
  if (d == "↑") {
    result = "←";
  } else if (d == "←") {
    result = "↓";
  } else if (d == "↓") {
    result = "→";
  } else {
    result = "↑";
  }

  return result;
}

std::string ChangeDirectionRight(const std::string& d) {
  std::string result;

  if (d == "↑") {
    result = "→";
  } else if (d == "→") {
    result = "↓";
  } else if (d == "↓") {
    result = "←";
  } else {
    result = "↑";
  }
  return result;
}

void UpdatePosition(const std::vector<std::vector<char>>& map, VehicleState& vs) {
  Position result_tmp = vs.player_position;
  int distance_current_step = 0;
  for (auto i = 0; i < vs.speed; i++) {
    if (vs.direction == "↑") {
      result_tmp.y -= 1;
    } else if (vs.direction == "→") {
      result_tmp.x += 1;
    } else if (vs.direction == "↓") {
      result_tmp.y += 1;
    } else if (vs.direction == "←") {
      result_tmp.x -= 1;
    }
    std::cout << "Y:" << result_tmp.y << ", X:" << result_tmp.x << std::endl;
    if (result_tmp.y >= map.size() - 1 || result_tmp.x >= map[0].size() - 1) {
      std::cout << "!!! 領域外なので進めません。" << std::endl;
    } else if (map[result_tmp.y][result_tmp.x] == '+') {
      std::cout << "!!! 壁なので進めません。" << std::endl;
    } else {
      // 領域外 or 壁でない とき自車位置を更新できる。
      vs.player_position = result_tmp;
      distance_current_step += 1;
    }
  }

  // ガソリン更新
  vs.fuel -= distance_current_step;
  if (vs.fuel < 0) {
    vs.fuel = 0;
  }

  return;
}

void VdUpdateDrivingState(const char& command, VehicleState& vs, const std::vector<std::vector<char>>& map) {
  switch (command) {
    case 'a':
      vs.speed = std::min(vs.speed + 1, vs.speed_limit);
      UpdatePosition(map, vs);
      break;

    case 'b':
      if (vs.speed > 0) {
        vs.speed--;
        UpdatePosition(map, vs);
      }
      break;

    case 'g':
      UpdatePosition(map, vs);
      break;

    case 's':
      vs.speed = 0;
      break;

    case 'l':
      vs.direction = ChangeDirectionLeft(vs.direction);
      break;

    case 'r':
      vs.direction = ChangeDirectionRight(vs.direction);
      break;
  }

  return;
}

}  // namespace DrivingCommand
namespace Display {
void VdShowMap(const std::vector<std::vector<char>>& map, const VehicleState& vehicle_state) {
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (vehicle_state.player_position.x == j && vehicle_state.player_position.y == i) {
        std::cout << vehicle_state.direction << " ";
      } else {
        std::cout << map[i][j] << " ";
      }
    }
    std::cout << std::endl;
  }
}
}  // namespace Display
