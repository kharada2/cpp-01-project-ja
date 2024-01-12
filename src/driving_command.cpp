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

int UpdateGasoline(const int s1_speed, const int s1_gasoline, const Position& position,
                   const std::vector<std::vector<char>>& map) {
  int result = std::max(s1_gasoline - s1_speed, 0);
  // ガソリン補充
  if (map[map.size() - 1 - position.y][position.x] == 'F') {
    std::cout << "給油完了" << std::endl;
    result = 100;
  }

  return result;
}
Position UpdatePosition(const Position& position, std::string direction, const int s1_speed,
                        const std::vector<std::vector<char>>& map) {
  Position result = {position.x, position.y};

  if (direction == "↑") {
    result.y = position.y + s1_speed;
  } else if (direction == "→") {
    result.x = position.x + s1_speed;
  } else if (direction == "↓") {
    result.y = position.y - s1_speed;
  } else if (direction == "←") {
    result.x = position.x - s1_speed;
  }

  if (result.x >= map[0].size() - 1 || result.y >= map.size() - 1) {
    std::cout << "!!! 領域外なので進めません。" << std::endl;
    result = {position.x, position.y};
  } else if (map[map.size() - 1 - result.y][result.x] == '#') {
    //  途中に壁があっても進めないようにする。
    std::cout << "!!! 壁なので進めません。" << std::endl;
    result = {position.x, position.y};
  }

  return result;
}

void VdUpdateDrivingState(const char& command, VehicleState& vs, const std::vector<std::vector<char>>& map) {
  switch (command) {
    case 'a':
      vs.s1_speed++;
      vs.player_position = UpdatePosition(vs.player_position, vs.direction, vs.s1_speed, map);
      vs.s1_gasoline = UpdateGasoline(vs.s1_speed, vs.s1_gasoline, vs.player_position, map);
      break;

    case 'b':
      if (vs.s1_speed > 0) {
        vs.s1_speed--;
        vs.player_position = UpdatePosition(vs.player_position, vs.direction, vs.s1_speed, map);
        vs.s1_gasoline = UpdateGasoline(vs.s1_speed, vs.s1_gasoline, vs.player_position, map);
      }
      break;

    case 'g':
      vs.player_position = UpdatePosition(vs.player_position, vs.direction, vs.s1_speed, map);
      vs.s1_gasoline = UpdateGasoline(vs.s1_speed, vs.s1_gasoline, vs.player_position, map);
      break;

    case 's':
      vs.s1_speed = 0;
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
void VdShowMap(const std::vector<std::vector<char>>& map, const Position& player_position) {
  std::cout << "▼▼▼ MAP (E: 自車位置, G: ゴール) ▼▼▼" << std::endl;
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (player_position.x == j && player_position.y == (map.size() - 1 - i)) {
        std::cout << "E ";
      } else {
        std::cout << map[i][j] << " ";
      }
    }
    std::cout << std::endl;
  }
}
}  // namespace Display
