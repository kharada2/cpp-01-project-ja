#include <iostream>
#include <string>
#include <vector>

#include "driving_command.h"

void VdInitvehicleState(VehicleState& vehicle_state) {
  vehicle_state.u1_gasoline = 10;
  vehicle_state.u1_speed = 0;
  vehicle_state.player_position = {1, 1};
  vehicle_state.direction = "North";
}

bool isGoalReached(const std::vector<std::vector<char>>& map, const Position& position) {
  // プレイヤーの位置がゴールであるかをチェックする
  if (map[map.size() - 1 - position.y][position.x] == 'g') {
    return true;
  }

  return false;
}

int main() {
  VehicleState vehicle_state;
  char command;
  VdInitvehicleState(vehicle_state);

  std::vector<std::vector<char>> map = RoadMap::VdGenerateMap();

  while (true) {
    // 現在の状態を表示
    std::cout << "speed:" << vehicle_state.u1_speed
              << ",  "
                 "direction:"
              << vehicle_state.direction << ", "
              << "position:"
              << "(" << vehicle_state.player_position.x << ", " << vehicle_state.player_position.y << "),  "
              << "gasoline:" << vehicle_state.u1_gasoline << ", ";
    std::cout << std::endl;

    // コマンド入力
    std::cin >> command;

    DrivingCommand::VdUpdateDrivingState(command, vehicle_state);

    if (vehicle_state.u1_gasoline == 0) {
      std::cout << "GAME OVER!! ガソリンが無くなりました。" << std::endl;
      break;
    }

    // ゴール判定
    bool fg_is_goal = isGoalReached(RoadMap::VdGenerateMap(), vehicle_state.player_position);
    if (fg_is_goal) {
      std::cout << "GAME CLEAR!!" << std::endl;
      break;
    }

    if (command == 'q') {
      break;
    }
  }

  return 0;
}