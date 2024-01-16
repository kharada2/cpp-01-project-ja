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
    if (result_tmp.y >= map.size() - 1 || result_tmp.x >= map[0].size() - 1) {
      std::cout << "!!! 領域外なので進めません。" << std::endl;
    } else if (map[result_tmp.y][result_tmp.x] == '#') {
      std::cout << "!!! 壁なので進めません。" << std::endl;
    } else {
      // 領域外 or 壁でない とき自車位置を更新できる。
      vs.player_position = result_tmp;
      distance_current_step += 1;
    }
  }

  // 進行分だけ燃料を消費させる
  vs.fuel -= distance_current_step;
  if (vs.fuel < 0) {
    vs.fuel = 0;
  }

  return;
}

void VdUpdateDrivingState(const char& command, VehicleState& vs, const std::vector<std::vector<char>>& map) {
  Position result_tmp = vs.player_position;
  switch (command) {
    case 'a':  // 加速
      vs.speed = std::min(vs.speed + 1, 2);
      UpdatePosition(map, vs);
      break;
    case 'b':  // 減速
      if (vs.speed > 0) {
        vs.speed--;
        UpdatePosition(map, vs);
      }
      break;

    case 'g':  // 直進
      UpdatePosition(map, vs);
      break;

    case 's':  // 停止
      vs.speed = 0;
      break;

    case 'l':  // 左折

      if (vs.direction == "NOTRH") {
        result_tmp.x -= 1;
      } else if (vs.direction == "EAST") {
        result_tmp.y -= 1;
      } else if (vs.direction == "SOUTH") {
        result_tmp.x += 1;
      } else if (vs.direction == "WEST") {
        result_tmp.y += 1;
      }
      if (map[result_tmp.y][result_tmp.x] == '#') {
        std::cout << "壁なので左折できません" << std::endl;
      } else {
        vs.direction = ChangeDirectionLeft(vs.direction);
      }

      break;

    case 'r':  // 右折

      if (vs.direction == "NOTRH") {
        result_tmp.x += 1;
      } else if (vs.direction == "EAST") {
        result_tmp.y += 1;
      } else if (vs.direction == "SOUTH") {
        result_tmp.x -= 1;
      } else if (vs.direction == "WEST") {
        result_tmp.y -= 1;
      }
      if (map[result_tmp.y][result_tmp.x] == '#') {
        std::cout << "壁なので右折できません" << std::endl;
      } else {
        vs.direction = ChangeDirectionRight(vs.direction);
      }
      break;

    case 'u':  // Uターン
      if (vs.direction == "NOTRH") {
        result_tmp.y += 1;
      } else if (vs.direction == "EAST") {
        result_tmp.x -= 1;
      } else if (vs.direction == "SOUTH") {
        result_tmp.y -= 1;
      } else if (vs.direction == "WEST") {
        result_tmp.x += 1;
      }
      if (map[result_tmp.y][result_tmp.x] == '#') {
        std::cout << "壁なのでUターンできません" << std::endl;
      } else {
        vs.direction = ChangeDirectionUturn(vs.direction);
      }
      break;

    default:
      std::cout << "無効なコマンドです。" << std::endl;
      break;
  }

  return;
}

}  // namespace DrivingCommand

namespace Score {
void CheckRule(VehicleState& vs) {
  if (vs.speed > vs.speed_limit) {
    std::cout << "##############################################" << std::endl;
    std::cout << "!!! 制限速度超過。減速してください。!!!" << std::endl;
    std::cout << "!!! ペナルティーとしてTIME -5 !!!" << std::endl;
    vs.time -= 5;
    std::cout << "残り時間：" << vs.time << std::endl;
    std::cout << "##############################################" << std::endl;
  }
}
}  // namespace Score