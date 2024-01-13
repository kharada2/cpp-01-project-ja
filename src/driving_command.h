#include <string>
#include <vector>

#include "map.h"
#include "struct_def.h"

namespace DrivingCommand {
void VdUpdateDrivingState(const char& command, VehicleState& vs, const std::vector<std::vector<char>>& map);
}

namespace Display {
void VdShowMap(const std::vector<std::vector<char>>& map, const VehicleState& vehicle_state);
}
