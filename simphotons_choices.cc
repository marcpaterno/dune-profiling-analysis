// Test program to benchmark different choices for SimPhotons implementation.
//
#include <iostream>
#include <map>
#include <random>
#include <vector>

#include "nanobench.h"

struct sp2 {
  std::vector<int> ticks;
  std::vector<int> nphots;
};

// Iterate through all values in map; we don't look at the keys.
std::size_t
sum(std::map<int, int> const& m)
{
  std::size_t sum = 0;
  for (auto const& p : m)
    sum += p.second;
  return sum;
}

// Iterate through all values in struct; we don't look at the keys.
std::size_t
sum(sp2 const& s)
{
  std::size_t sum = 0;
  for (auto const& p : s.nphots)
    sum += p;
  return sum;
}

template <typename S>
void
run_sum(ankerl::nanobench::Bench* bench, S const& m, const char* name)
{
  bench->run(name, [&m]() {
    auto s = sum(m);
    ankerl::nanobench::doNotOptimizeAway(s);
  });
}

int
main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Please specificy a number of measurements to use\n";
    return 1;
  }
  std::size_t const N_MEASUREMENTS = std::atoll(argv[1]);

  ankerl::nanobench::Bench b;
  b.title("simphotons choices")
    .performanceCounters(true)
    .minEpochIterations(10 * 1000);

  std::minstd_rand0 engine(123);
  int MAXPHOTS = 1000;
  std::uniform_int_distribution<int> dist{0, MAXPHOTS};
  auto gen = [&dist, &engine]() { return dist(engine); };

  std::vector<int> ticks(N_MEASUREMENTS);
  std::vector<int> nphots(N_MEASUREMENTS);

  std::generate(begin(ticks), end(ticks), gen);
  std::generate(begin(nphots), end(nphots), gen);

  std::map<int, int> sp_orig;
  for (std::size_t i = 0; i != N_MEASUREMENTS; ++i) {
    sp_orig.insert({ticks[i], nphots[i]});
  }

  sp2 sp_new{ticks, nphots};

  run_sum(&b, sp_orig, "sum_map");
  run_sum(&b, sp_new, "sum_sp2");
}
