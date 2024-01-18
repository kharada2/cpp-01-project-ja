#include <string>
#include <vector>

#include "map.h"
#include "struct_def.h"

namespace DrivingCommand {
void UpdateDrivingState(const char& command, VehicleState& vs, const std::vector<std::vector<char>>& map);
bool GameEndJdg(const char& command, VehicleState& vehicle_state);
}  // namespace DrivingCommand

namespace Score {
void CheckRule(VehicleState& vs);
}

namespace Weather {
void UpdateWeather(VehicleState& vs);
}  // namespace Weather