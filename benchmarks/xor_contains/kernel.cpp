#include <algorithm>
#include <vector>

bool xor_contains_native(const std::vector<int> &x, const std::vector<int> &y,
                         int val) {
  bool found_in_x = false;
  bool found_in_y = false;

  for (const auto &num : x) {
    if (num == val) {
      found_in_x = true;
      break;
    }
  }

  for (const auto &num : y) {
    if (num == val) {
      found_in_y = true;
      break;
    }
  }

  return found_in_x != found_in_y;
}

bool xor_contains_stl(const std::vector<int> &x, const std::vector<int> &y,
                      int val) {
  bool found_in_x = std::ranges::find(x, val) != x.end();
  bool found_in_y = std::ranges::find(y, val) != y.end();

  return found_in_x != found_in_y;
}
