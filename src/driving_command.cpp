#include "driving_command.h"

#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>

#include "define_const.h"
#include "struct_def.h"

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
      // std::cout << "!!! CANNOT PROCEED. OUT OF ROAD." << std::endl;
      vs.is_accident = true;
    } else if (map[result_tmp.y][result_tmp.x] == '#') {
      // std::cout << "!!! CANNOT PROCEED." << std::endl;
      vs.is_accident = true;
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

void UpdateDrivingState(const char& command, VehicleState& vs, const std::vector<std::vector<char>>& map) {
  Position result_tmp = vs.player_position;
  switch (command) {
    case 'a':  // 加速
      vs.speed = std::min(vs.speed + 1, SPEED_MAX);
      UpdatePosition(map, vs);
      break;
    case 'b':  // 減速
      if (vs.speed > SPEED_MIN) {
        vs.speed--;
        UpdatePosition(map, vs);
      }
      break;

    case 'g':  // 直進
      UpdatePosition(map, vs);
      break;

    case 's':  // 停止
      vs.speed = SPEED_MIN;
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
        // std::cout << "CANNOT TURN LEFT" << std::endl;
        vs.is_accident = true;
      } else {
        vs.direction = ChangeDirectionLeft(vs.direction);
        vs.player_position = {result_tmp.x, result_tmp.y};
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
        // std::cout << "CANNOT TURN RIGHT" << std::endl;
        vs.is_accident = true;
      } else {
        vs.direction = ChangeDirectionRight(vs.direction);
        vs.player_position = {result_tmp.x, result_tmp.y};
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
        // std::cout << "CANNOT DO A U-TURN" << std::endl;
        vs.is_accident = true;
      } else {
        vs.direction = ChangeDirectionUturn(vs.direction);
        vs.player_position = {result_tmp.x, result_tmp.y};
      }
      break;

    default:
      // std::cout << "無効なコマンドです。" << std::endl;
      std::cout << "INVALID COMMAND" << std::endl;
      break;
  }

  return;
}

bool GameEndJdg(const char& command, VehicleState& vehicle_state) {
  bool result = false;
  if (vehicle_state.is_goal) {
    std::cout << "####### GAME CLEAR!! ####" << std::endl;
    std::cout << "YOUR SCORE IS: " << vehicle_state.time + vehicle_state.fuel_count * 10 << std::endl;
    result = true;
  } else if (vehicle_state.is_accident) {
    std::cout << "GAME OVER!! CAR CRASHED BY ACCIDENT." << std::endl;
    result = true;
  } else if (vehicle_state.fuel == 0) {
    std::cout << "GAME OVER!! OUT OF GASOLINE." << std::endl;
    result = true;
  } else if (vehicle_state.time == 0) {
    std::cout << "GAME OVER!! TIMEOVER." << std::endl;
    result = true;
  } else if (command == 'q') {
    std::cout << "####### GAME ABORT #########" << std::endl;
    result = true;
  }

  return result;
}
}  // namespace DrivingCommand

namespace Score {
void CheckRule(VehicleState& vs) {
  if (vs.speed > vs.speed_limit) {
    std::cout << "##############################################" << std::endl;
    std::cout << "!!! SPEED OVER. PLEASE SPEED DOWN. !!!" << std::endl;
    std::cout << "!!! PENALTY:  TIME-5 !!!" << std::endl;
    vs.time -= PENALTY_SPEED_OVER;
    std::cout << "REMAIN TIME:" << vs.time << std::endl;
    std::cout << "##############################################" << std::endl;
  }
}
}  // namespace Score

namespace Weather {
void UpdateWeather(VehicleState& vs) {
  int max_value = std::numeric_limits<int>::max();
  float f_rand = std::rand() / static_cast<double>(max_value);

  if (vs.weather == SNOW) {
    // 雪が降っている
    if (f_rand < SHOW_STOP) {
      // 雪がやむ
      vs.weather = SUNNY;
    }
  } else {
    // 雪が降っていない
    if (f_rand < SHOW_POSSIBILITY) {
      // 雪が降り始める
      vs.weather = SNOW;
    }
  }
}
}  // namespace Weather