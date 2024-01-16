#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>

#include "display.h"
#include "driving_command.h"
#include "way_point.h"
void VdInitvehicleState(int map_size, VehicleState& vehicle_state) {
  vehicle_state.fuel = 20;
  vehicle_state.speed = 0;
  vehicle_state.player_position = {2, map_size - 3};      // x, y
  vehicle_state.player_position_pre = {1, map_size - 3};  // x, y
  vehicle_state.direction = "NOTRH";
  vehicle_state.time = 100;
  vehicle_state.fuel_count = 2;
  vehicle_state.speed_limit = 1;
}

bool isOutOfFual(const int fuel) { return fuel == 0; }

int main() {
  // 変数宣言
  VehicleState vehicle_state;
  std::vector<std::vector<char>> map = RoadMap::GenerateMap();

  // 自車状態初期化
  VdInitvehicleState(map.size(), vehicle_state);

  std::cout << "####### GAME START #######" << std::endl;
  std::cout << "'a(加速)'を押して走行を開始してください。" << std::endl;
  while (true) {
    // コマンド入力
    char command;
    std::cin >> command;

    // 車両状態更新
    DrivingCommand::VdUpdateDrivingState(command, vehicle_state, map);

    // ルール違反チェック
    Score::CheckRule(vehicle_state);

    // 現在の状態を表示
    Display::DisplayStatus(map, vehicle_state);

    // ランドマークチェック
    bool fg_is_goal = WayPoint::WayPointCheck(map, vehicle_state, command);

    // map表示
    Display::ShowDriverView(map, vehicle_state);

    // ゲーム終了判定
    if (fg_is_goal) {
      std::cout << "####### GAME CLEAR!! ####" << std::endl;
      std::cout << "YOUR SCORE IS: " << vehicle_state.time + vehicle_state.fuel_count * 10 << std::endl;
      break;
    } else if (vehicle_state.fuel == 0) {
      std::cout << "GAME OVER!! ガソリンが無くなりました。" << std::endl;
      break;
    } else if (vehicle_state.time <= 0) {
      std::cout << "TIMEOVER!!" << std::endl;
      break;
    } else if (command == 'q') {
      std::cout << "####### GAME ABORT #########" << std::endl;
      break;
    }

    // 時間更新
    vehicle_state.time--;

    // 現在位置情報保存
    vehicle_state.player_position_pre = vehicle_state.player_position;
    std::cout << std::endl;
  }

  return 0;
}