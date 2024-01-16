#include <iostream>
#include <string>
#include <vector>

#include "display.h"
#include "driving_command.h"
#include "way_point.h"

void VdInitvehicleState(int map_size, VehicleState& vehicle_state) {
  vehicle_state.fuel = 40;
  vehicle_state.speed = 0;
  vehicle_state.player_position = {1, map_size - 1};  // x, y
  vehicle_state.direction = "NOTRH";
  vehicle_state.time = 100;
  vehicle_state.fuel_count = 2;
  vehicle_state.speed_limit = 1;
}

bool isOutOfFual(const int fuel) { return fuel == 0; }

int main() {
  // ゴールがどこかわからない。
  VehicleState vehicle_state;
  char command;

  std::vector<std::vector<char>> map = RoadMap::GenerateMap();
  VdInitvehicleState(map.size(), vehicle_state);

  std::cout << "####### GAME START #######" << std::endl;
  std::cout << "'a'を押して走行を開始してください。（ コマンド　a:加速 b:減速 g:直進 s:停止 r:右折 l:左折）"
            << std::endl;

  while (true) {
    // コマンド入力
    std::cin >> command;

    // 車両状態更新
    DrivingCommand::VdUpdateDrivingState(command, vehicle_state, map);

    // 現在の状態を表示
    std::cout << "残時間:" << vehicle_state.time << ", "
              << "速度:" << vehicle_state.speed << ",  "
              << "進行方向:" << vehicle_state.direction
              << ", "
              // << "ゴールまでの距離:" << vehicle_state.direction << ", "
              << "上限速度:" << vehicle_state.speed_limit << ",  "
              << "燃料:" << vehicle_state.fuel << "  ";
    std::cout << std::endl;

    // WayPoint check
    bool fg_is_goal = WayPoint::WayPointCheck(map, vehicle_state);

    // ガス欠判定
    bool fg_out_of_fual = isOutOfFual(vehicle_state.fuel);
    // 時間更新
    vehicle_state.time--;

    if (fg_is_goal) {
      std::cout << "####### GAME CLEAR!! ####" << std::endl;
      break;
    } else if (fg_out_of_fual) {
      std::cout << "GAME OVER!! ガソリンが無くなりました。" << std::endl;
      break;
    } else if (vehicle_state.time <= 0) {
      std::cout << "TIMEOVER!!" << std::endl;
      break;
    } else if (command == 'q') {
      std::cout << "####### GAME ABORT #########" << std::endl;
      break;
    }

    // map表示
    // Display::VdShowMap(map, vehicle_state);
    Display::ShowDriverView(map, vehicle_state);
  }

  return 0;
}