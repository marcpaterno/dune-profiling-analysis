#include "fill_functions.hh"
#include <algorithm>
#include <random>
#include <utility>
#include <vector>

// Make the vectors of random numbers used to fill the various data structures.
std::pair<std::vector<int>, std::vector<int>>
make_random_vectors(std::size_t n_measurements, unsigned long long seed)
{
  std::minstd_rand0 engine(seed);
  int MAXPHOTS = 1000;
  std::uniform_int_distribution<int> dist{0, MAXPHOTS};
  auto gen = [&dist, &engine]() { return dist(engine); };

  std::vector<int> ticks(n_measurements);
  std::vector<int> nphots(n_measurements);

  std::generate(begin(ticks), end(ticks), gen);
  std::generate(begin(nphots), end(nphots), gen);
  return {ticks, nphots};
}

// Node-based versions.
template <typename RECORDBASED>
void
fill_nodebased(RECORDBASED& m, std::size_t n_measurements)
{
  auto [ticks, nphots] = make_random_vectors(n_measurements, 123);
  for (std::size_t i = 0; i != n_measurements; ++i) {
    m.insert({ticks[i], nphots[i]});
  }
}

void
fill(std::map<int, int>& m, std::size_t n_measurements)
{
  fill_nodebased(m, n_measurements);
}

void
fill(std::unordered_map<int, int>& m, std::size_t n_measurements)
{
  fill_nodebased(m, n_measurements);
}

// AOS-based versions.

template <typename AOS>
void
fill_aos(AOS& m, std::size_t n_measurements)
{
  std::minstd_rand0 engine(123);
  int MAXPHOTS = 1000;
  std::uniform_int_distribution<int> dist{0, MAXPHOTS};
  auto gen = [&dist, &engine]() { return dist(engine); };
  m.resize(n_measurements);
  for (auto& record : m) {
    record.first = gen();
    record.second = gen();
  }
}

void
fill(aos_vector& m, std::size_t n_measurements)
{
  fill_aos(m, n_measurements);
}

void
fill(aos_deq& m, std::size_t n_measurements)
{
  fill_aos(m, n_measurements);
}

void
fill(aos_slist& m, std::size_t n_measurements)
{
  fill_aos(m, n_measurements);
}

// SOA-based versions.

template <typename SOA>
void
fill_soa(SOA& m, std::size_t n_measurements)
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

void
fill(soa_vector& m, std::size_t n_measurements)
{
  fill_soa(m, n_measurements);
}

void
fill(soa_deq& m, std::size_t n_measurements)
{
  fill_soa(m, n_measurements);
}
void
fill(soa_slist& m, std::size_t n_measurements)
{
  fill_soa(m, n_measurements);
}
