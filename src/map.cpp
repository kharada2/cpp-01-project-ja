#include "map.h"

namespace RoadMap {
std::vector<std::vector<char>> GenerateMap() {
  std::vector<std::vector<char>> map = {
      // #: 壁
      // F: ガソリンスタンド
      // C: コンビニ
      // G: ゴール
      // H: 高速道路
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
      {'#', '#', 'F', '#', '#', 'F', ' ', ' ', '#', '#', 'C', '#', '#', '#', ' ', '#', '#', '#', '#', 'G', '#', '#'},
      {'#', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#', ' ', '#', '#'},
      {'#', '#', ' ', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#'},
      {'#', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#', '#'},
      {'#', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#', '#'},
      {'#', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#', '#'},
      {'#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'H', 'H', 'H', 'H', '#', '#', '#'},
      {'#', '#', ' ', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#', ' ', 'F', '#', '#', '#', '#', 'H', '#', '#', '#'},
      {'#', '#', ' ', '#', ' ', '#', '#', ' ', '#', 'F', '#', '#', ' ', '#', '#', '#', '#', '#', 'H', '#', '#', '#'},
      {'#', '#', ' ', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#', ' ', '#', '#', '#', '#', '#', 'H', '#', '#', '#'},
      {'#', '#', ' ', ' ', 'F', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', 'H', '#', '#', '#'},
      {'#', '#', ' ', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'H', 'H', '#', '#', '#'},
      {'#', '#', ' ', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'F', 'H', '#', '#', '#'},
      {'#', '#', 'F', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', '#', 'H', 'H', '#', ' ', ' '},
      {'#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', '#', '#', 'H', '#', ' ', '#'},
      {'#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', 'C', '#', 'H', '#', ' ', '#'},
      {'#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', 'H', '#', ' ', '#'},
      {'#', '#', '#', '#', 'C', '#', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', 'H', '#', '#', '#'},
      {'#', '#', '#', '#', ' ', '#', '#', ' ', '#', '#', '#', ' ', ' ', 'F', ' ', '#', '#', '#', 'H', '#', 'F', '#'},
      {'#', '#', 'F', ' ', ' ', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', ' ', '#', '#', '#', 'H', '#', ' ', '#'},
      {'#', '#', ' ', '#', ' ', '#', 'F', ' ', '#', 'F', ' ', ' ', '#', '#', ' ', '#', '#', '#', 'H', '#', ' ', '#'},
      {'#', '#', ' ', '#', ' ', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#', '#', '#', 'H', '#', ' ', '#'},
      {'#', '#', ' ', '#', ' ', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', ' ', 'F', '#', 'H', '#', ' ', '#'},
      {'#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}};

  return map;
}
}  // namespace RoadMap