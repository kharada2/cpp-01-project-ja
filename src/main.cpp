#include <iostream>
#include <string>
#include <vector>

#include "driving_command.h"

void VdInitvehicleState(VehicleState& vehicle_state) {
  vehicle_state.s1_gasoline = 30;
  vehicle_state.s1_speed = 0;
  vehicle_state.player_position = {1, 1};
  vehicle_state.direction = "↑";
}

bool isGoalReached(const std::vector<std::vector<char>>& map, const int size_h, const Position& position) {
  // プレイヤーの位置がゴールであるかをチェックする
  if (map[position.y - 1][position.x] == 'G') {
    return true;
  }

  std::cout << map[position.y][position.x] << std::endl;

  return false;
}

bool isOutOfFual(const int s1_gasoline) { return s1_gasoline == 0; }

int main() {
  // ゴールがどこかわからない。
  VehicleState vehicle_state;
  char command;
  VdInitvehicleState(vehicle_state);
  std::vector<std::vector<char>> map = RoadMap::VdGenerateMap();

  std::cout << "GAME START" << std::endl;
  std::cout << "コマンドを入力してください（ a:加速 b:減速 g:直進 s:停止 r:右折 l:左折）" << std::endl;

  while (true) {
    // コマンド入力
    std::cin >> command;

    // 車両状態更新
    DrivingCommand::VdUpdateDrivingState(command, vehicle_state, map);

    // 現在の状態を表示
    std::cout << "自車情報【速度:" << vehicle_state.s1_speed << ",  "
              << "方向:" << vehicle_state.direction << ", "
              << "燃料:" << vehicle_state.s1_gasoline << "】 ";
    std::cout << std::endl;

    // map表示
    Display::VdShowMap(map, vehicle_state.player_position);

    // ゴール判定
    bool fg_is_goal = isGoalReached(map, map[0].size(), vehicle_state.player_position);
    // ガス欠判定
    bool fg_out_of_fual = isOutOfFual(vehicle_state.s1_gasoline);

    if (fg_is_goal) {
      std::cout << "GAME CLEAR!!" << std::endl;
      break;
    } else if (fg_out_of_fual) {
      std::cout << "GAME OVER!! ガソリンが無くなりました。" << std::endl;
      break;
    } else if (command == 'q') {
      std::cout << "GAME中止" << std::endl;
      break;
    }
  }

  return 0;
}