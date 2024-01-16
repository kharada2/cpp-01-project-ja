#include "driving_command.h"

#include <iostream>
#include <string>
#include <vector>

namespace DrivingCommand {
std::string ChangeDirectionLeft(const std::string& d) {
  std::string result;
  if (d == "NOTRH") {
    result = "WEST";
  } else if (d == "WEST") {
    result = "SOUTH";
  } else if (d == "SOUTH") {
    result = "EAST";
  } else {
    result = "NOTRH";
  }

  return result;
}

std::string ChangeDirectionRight(const std::string& d) {
  std::string result;

  if (d == "NOTRH") {
    result = "EAST";
  } else if (d == "EAST") {
    result = "SOUTH";
  } else if (d == "SOUTH") {
    result = "WEST";
  } else {
    result = "NOTRH";
  }
  return result;
}

std::string ChangeDirectionUturn(const std::string& d) {
  std::string result;

  if (d == "NOTRH") {
    result = "SOUTH";
  } else if (d == "EAST") {
    result = "WEST";
  } else if (d == "NOTRH") {
    result = "WEST";
  } else {
    result = "EAST";
  }
  return result;
}

void UpdatePosition(const std::vector<std::vector<char>>& map, VehicleState& vs) {
  Position result_tmp = vs.player_position;
  int distance_current_step = 0;
  for (auto i = 0; i < vs.speed; i++) {
    if (vs.direction == "NOTRH") {
      result_tmp.y -= 1;
    } else if (vs.direction == "EAST") {
      result_tmp.x += 1;
    } else if (vs.direction == "SOUTH") {
      result_tmp.y += 1;
    } else if (vs.direction == "WEST") {
      result_tmp.x -= 1;
    }
    std::cout << "Y:" << result_tmp.y << ", X:" << result_tmp.x << std::endl;
    if (result_tmp.y >= map.size() - 1 || result_tmp.x >= map[0].size() - 1) {
      std::cout << "!!! 領域外なので進めません。" << std::endl;
    } else if (map[result_tmp.y][result_tmp.x] == '*') {
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
  Position result_tmp = vs.player_position;
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

      if (vs.direction == "NOTRH") {
        result_tmp.x -= 1;
      } else if (vs.direction == "EAST") {
        result_tmp.y -= 1;
      } else if (vs.direction == "SOUTH") {
        result_tmp.x += 1;
      } else if (vs.direction == "WEST") {
        result_tmp.y += 1;
      }
      if (map[result_tmp.y][result_tmp.x] == '*') {
        std::cout << "壁なので左折できません" << std::endl;
      } else {
        vs.direction = ChangeDirectionLeft(vs.direction);
      }

      break;

    case 'r':

      if (vs.direction == "NOTRH") {
        result_tmp.x += 1;
      } else if (vs.direction == "EAST") {
        result_tmp.y += 1;
      } else if (vs.direction == "SOUTH") {
        result_tmp.x -= 1;
      } else if (vs.direction == "WEST") {
        result_tmp.y -= 1;
      }
      if (map[result_tmp.y][result_tmp.x] == '*') {
        std::cout << "壁なので右折できません" << std::endl;
      } else {
        vs.direction = ChangeDirectionRight(vs.direction);
      }
      break;

    case 'u':
      if (vs.direction == "NOTRH") {
        result_tmp.y += 1;
      } else if (vs.direction == "EAST") {
        result_tmp.x -= 1;
      } else if (vs.direction == "SOUTH") {
        result_tmp.y -= 1;
      } else if (vs.direction == "WEST") {
        result_tmp.x += 1;
      }
      if (map[result_tmp.y][result_tmp.x] == '*') {
        std::cout << "壁なのでUターンできません" << std::endl;
      } else {
        vs.direction = ChangeDirectionUturn(vs.direction);
      }
      break;
  }

  return;
}
}  // namespace DrivingCommand
