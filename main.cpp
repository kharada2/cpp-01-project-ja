#include <iostream>
#include <string>
#include <vector>

#include "driving_command.h"

void VdInitvehicleState(VehicleState& vehicle_state) {
  vehicle_state.u1_gasoline = 10;
  vehicle_state.u1_speed = 0;
  vehicle_state.player_position = {0, 0};
  vehicle_state.direction = "North";
}

int main() {
  VehicleState vehicle_state;
  char command;
  VdInitvehicleState(vehicle_state);

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

    if (command == 'q') {
      break;
    }
  }

  // std::cout << "Game over. Final distance: " << GameState.distance << " meters" << std::endl;

  return 0;
}