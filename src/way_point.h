#include <string>
#include <vector>

#include "map.h"
#include "struct_def.h"

namespace WayPoint {
void WayPointCheck(const std::vector<std::vector<char>>& map, VehicleState& vehicle_state, const char& command);
Position DistanceToLandMark(const std::vector<std::vector<char>>& map, const char landmark,
                            const VehicleState& vehicle_state);
}  // namespace WayPoint
