// Test program to benchmark different choices for SimPhotons implementation.
//
#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <random>
#include <unordered_map>
#include <vector>

#include "nanobench.h"
#include "fmt/core.h"

struct sp2 {
  std::vector<int> ticks;
  std::vector<int> nphots;
};

// Iterate through all values in map; we don't look at the keys.
__attribute__((noinline))
std::size_t
sum(std::map<int, int> const& m)
{
  std::size_t sum = 0;
  for (auto const& p : m)
    sum += p.second;
  return sum;
}

// Iterate through all values in struct; we don't look at the keys.
__attribute__((noinline))
std::size_t
sum(sp2 const& s)
{
  std::size_t sum = 0;
  for (auto const& p : s.nphots)
    sum += p;
  return sum;
}

// Iterate through all values in the hashmap; we don't look at the keys.
__attribute__((noinline))
std::size_t
sum(std::unordered_map<int, int> const& m)
{
  std::size_t sum = 0;
  for (auto const& p : m)
    sum += p.second;
  return sum;
}


// Fill the container m with n key/value pairs.
void fill(std::map<int, int>& m, std::size_t n_measurements)
{
  std::minstd_rand0 engine(123);
  int MAXPHOTS = 1000;
  std::uniform_int_distribution<int> dist{0, MAXPHOTS};
  auto gen = [&dist, &engine]() { return dist(engine); };

  std::vector<int> ticks(n_measurements);
  std::vector<int> nphots(n_measurements);

  std::generate(begin(ticks), end(ticks), gen);
  std::generate(begin(nphots), end(nphots), gen);

  for (std::size_t i = 0; i != n_measurements; ++i) {
    m.insert({ticks[i], nphots[i]});
  }
}

// Fill the container m with n key/value pairs.
void fill(sp2& m, std::size_t n_measurements)
{
  std::minstd_rand0 engine(123);
  int MAXPHOTS = 1000;
  std::uniform_int_distribution<int> dist{0, MAXPHOTS};
  auto gen = [&dist, &engine]() { return dist(engine); };
  m.ticks.resize(n_measurements);
  m.nphots.resize(n_measurements);
  std::generate(begin(m.ticks), end(m.ticks), gen);
  std::generate(begin(m.nphots), end(m.nphots), gen);

}

// Fill the container m with n key/value pairs.
void fill(std::unordered_map<int, int>& m, std::size_t n_measurements)
{
  std::minstd_rand0 engine(123);
  int MAXPHOTS = 1000;
  std::uniform_int_distribution<int> dist{0, MAXPHOTS};
  auto gen = [&dist, &engine]() { return dist(engine); };

  std::vector<int> ticks(n_measurements);
  std::vector<int> nphots(n_measurements);

  std::generate(begin(ticks), end(ticks), gen);
  std::generate(begin(nphots), end(nphots), gen);

  for (std::size_t i = 0; i != n_measurements; ++i) {
    m.insert({ticks[i], nphots[i]});
  }
}

template <typename S>
void
run_sum(ankerl::nanobench::Bench* bench, S& m, std::size_t n, std::string const& name)
{
  std::size_t sz = 0;
  fill(m, n);
  bench->run(name, [&]() {
    sz = sum(m);
  });
  ankerl::nanobench::doNotOptimizeAway(sz);
}

int
main()
{
  ankerl::nanobench::Bench b;
  b.title("simphotons choices")
    .performanceCounters(true)
    .minEpochIterations(200 * 1000);

  std::array<std::size_t, 7> NM = { 10ULL, 30ULL, 100ULL, 300ULL, 1000ULL, 3000ULL, 10000ULL };

  std::map<int, int> sp_orig;
  sp2 sp_new;
  std::unordered_map<int, int> hashmap;

  for (auto n : NM) {
    std::string suffix = std::to_string(n);
    run_sum(&b, sp_orig, n, fmt::format("sum_map_{}", suffix));
    run_sum(&b, sp_new, n, fmt::format("sum_sp2_{}", suffix));
    run_sum(&b, hashmap, n, fmt::format("sum_hashmap_{}", suffix));
  }
}
