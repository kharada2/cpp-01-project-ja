#include <string>
#include <vector>

#include "map.h"
#include "struct_def.h"

namespace Display {
void VdShowMap(const std::vector<std::vector<char>>& map, const VehicleState& vehicle_state);
void ShowDriverView(const std::vector<std::vector<char>>& map, const VehicleState& vehicle_state);
void DisplayStatus(const std::vector<std::vector<char>>& map, const VehicleState& vehicle_state);
}  // namespace Display
