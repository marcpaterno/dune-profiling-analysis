#include "fill_functions.hh"
#include <algorithm>
#include <random>
#include <utility>
#include <vector>

// Make the vectors of numbers used to fill the various data structures.
// We use random numbers for the number of photons, and consecutive integers
// for the ticks values. This is to avoid map and hashmap key collisions.
std::pair<std::vector<int>, std::vector<int>>
make_random_vectors(std::size_t n_measurements, unsigned long long seed)
{
  std::minstd_rand0 engine(seed);
  int MAXPHOT = 10000;
  std::uniform_int_distribution<int> dist{0, MAXPHOT};
  auto gen = [&dist, &engine]() { return dist(engine); };

  std::vector<int> ticks(n_measurements);
  std::vector<int> nphots(n_measurements);

  for (std::size_t i = 0; i != n_measurements; ++i) {
    ticks[i] = i;
  }
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
  auto [ticks, nphots] = make_random_vectors(n_measurements, 123);
  m.resize(n_measurements);
  std::size_t i = 0;
  for (auto& record : m) {
    record.first = ticks[i];
    record.second = nphots[i];
    ++i;
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
  auto [ticks, nphots] = make_random_vectors(n_measurements, 123);
  m.ticks.assign(begin(ticks), end(ticks));
  m.nphots.assign(begin(nphots), end(nphots));
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
