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

#include "data_structures.hh"
#include "fill_functions.hh"
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
  std::unordered_map<int, int> hashmap;

  aos_vector aos_v;
  aos_deq aos_d;
  aos_slist aos_l;

  soa_vector soa_v;
  soa_deq soa_d;
  soa_slist soa_l;

  for (auto n : NM) {
    std::string suffix = std::to_string(n);

    // Node-based types
    sp_orig = std::map<int, int>();
    hashmap = std::unordered_map<int, int>();

    // Record-oriented types
    aos_v = aos_vector();
    aos_d = aos_deq();
    aos_l = aos_slist();

    // Array-oriented types
    soa_v = soa_vector();
    soa_d = soa_deq();
    soa_l = soa_slist();

    fill(sp_orig, n);
    fill(hashmap, n);

    fill(aos_v, n);
    fill(aos_d, n);
    fill(aos_l, n);

    fill(soa_v, n);
    fill(soa_d, n);
    fill(soa_l, n);

    run_sum(&b, sp_orig, n, fmt::format("sum_map_{}", suffix));
    run_sum(&b, hashmap, n, fmt::format("sum_hashmap_{}", suffix));

    run_sum(&b, aos_v, n, fmt::format("sum_aosv_{}", suffix));
    run_sum(&b, aos_d, n, fmt::format("sum_aosd_{}", suffix));
    run_sum(&b, aos_l, n, fmt::format("sum_aosl_{}", suffix));

    run_sum(&b, soa_v, n, fmt::format("sum_soav_{}", suffix));
    run_sum(&b, soa_v, n, fmt::format("sum_soad_{}", suffix));
    run_sum(&b, soa_v, n, fmt::format("sum_soal_{}", suffix));
  }

  for (auto n : NM) {
    std::string suffix = std::to_string(n);

    // Node-based types
    sp_orig = std::map<int, int>();
    hashmap = std::unordered_map<int, int>();

    // Record-oriented types
    aos_v = aos_vector();
    aos_d = aos_deq();
    aos_l = aos_slist();

    // Array-oriented types
    soa_v = soa_vector();
    soa_d = soa_deq();
    soa_l = soa_slist();

    fill(sp_orig, n);
    fill(hashmap, n);

    fill(aos_v, n);
    fill(aos_d, n);
    fill(aos_l, n);

    fill(soa_v, n);
    fill(soa_d, n);
    fill(soa_l, n);

    run_scan(&b, sp_orig, n, fmt::format("scan_map_{}", suffix));
    run_scan(&b, hashmap, n, fmt::format("scan_hashmap_{}", suffix));

    run_scan(&b, aos_v, n, fmt::format("scan_aosv_{}", suffix));
    run_scan(&b, aos_d, n, fmt::format("scan_aosd_{}", suffix));
    // run_scan(&b, aos_l, n, fmt::format("scan_aosl_{}", suffix));

    // run_scan(&b, soa_v, n, fmt::format("scan_soav_{}", suffix));
    // run_scan(&b, soa_v, n, fmt::format("scan_soad_{}", suffix));
    // run_scan(&b, soa_v, n, fmt::format("scan_soal_{}", suffix
  }
}
