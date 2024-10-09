#include <benchmark/benchmark.h>

#include <algorithm>
#include <random>
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

static std::tuple<std::vector<int>, std::vector<int>, int> setup(size_t N) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(-N, N);

  std::vector<int> x(N), y(N);
  std::ranges::generate(x, [&]() { return distrib(gen); });
  std::ranges::generate(y, [&]() { return distrib(gen); });

  int val = distrib(gen);

  return {x, y, val};
}

static void BM_native(benchmark::State &state) {
  auto [x, y, val] = setup(state.range(0));

  for (auto _ : state) {
    auto res = xor_contains_native(x, y, val);
    benchmark::DoNotOptimize(res);
  }
}

static void BM_stl(benchmark::State &state) {
  auto [x, y, val] = setup(state.range(0));

  for (auto _ : state) {
    auto res = xor_contains_stl(x, y, val);
    benchmark::DoNotOptimize(res);
  }
}

BENCHMARK(BM_native)->RangeMultiplier(2)->Range(1, 1 << 27);
BENCHMARK(BM_stl)->RangeMultiplier(2)->Range(1, 1 << 27);

BENCHMARK_MAIN();
