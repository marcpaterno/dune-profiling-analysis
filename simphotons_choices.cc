// Test program to benchmark different choices for SimPhotons implementation.
//
#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

#include "fmt/core.h"
#include "nanobench.h"

#include "fill_functions.hh"
#include "sp2.hh"
#include "operations.hh"

template <typename S>
void
run_sum(ankerl::nanobench::Bench* bench,
        S const& m,
        std::size_t n,
        std::string const& name)
{
  int s = 0;
  bench->run(name, [&]() { s = sum(m); });
  ankerl::nanobench::doNotOptimizeAway(s);
}

template <typename S>
void
run_scan(ankerl::nanobench::Bench* bench,
         S const& m,
         std::size_t n,
         std::string const& name)
{
  int s = 0;
  bench->run(name, [&]() { auto [idx, val] = find_largest(m); });
  ankerl::nanobench::doNotOptimizeAway(s);
}

int
main()
{
  ankerl::nanobench::Bench b;
  b.title("simphotons choices")
    .performanceCounters(true)
    .minEpochIterations(150 * 1000);

  std::array<std::size_t, 7> NM = {
    10ULL, 30ULL, 100ULL, 300ULL, 1000ULL, 3000ULL, 10000ULL};
  std::ranges::reverse(NM);

  std::map<int, int> sp_orig;
  sp2 sp_new;
  std::unordered_map<int, int> hashmap;
  sp_pairs pairs;

  for (auto n : NM) {
    std::string suffix = std::to_string(n);
    sp_orig = std::map<int, int>();
    sp_new = sp2();
    hashmap = std::unordered_map<int, int>();
    fill(sp_orig, n);
    fill(sp_new, n);
    fill(hashmap, n);
    fill(pairs, n);

    run_sum(&b, sp_orig, n, fmt::format("sum_map_{}", suffix));
    run_sum(&b, sp_new, n, fmt::format("sum_sp2_{}", suffix));
    run_sum(&b, hashmap, n, fmt::format("sum_hashmap_{}", suffix));
    run_sum(&b, pairs, n, fmt::format("sum_pairs_{}", suffix));
  }

  for (auto n : NM) {
    std::string suffix = std::to_string(n);
    sp_orig = std::map<int, int>();
    sp_new = sp2();
    hashmap = std::unordered_map<int, int>();
    fill(sp_orig, n);
    fill(sp_new, n);
    fill(hashmap, n);
    fill(pairs, n);

    run_scan(&b, sp_orig, n, fmt::format("scan_map_{}", suffix));
    run_scan(&b, sp_new, n, fmt::format("scan_sp2_{}", suffix));
    run_scan(&b, hashmap, n, fmt::format("scan_hashmap_{}", suffix));
    run_scan(&b, pairs, n, fmt::format("scan_pairs_{}", suffix));
  }
}
