#include "fill_functions.hh"
#include <algorithm>
#include <random>

// Fill the container m with n key/value pairs.
void
fill(std::map<int, int>& m, std::size_t n_measurements)
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
void
fill(soa_vector& m, std::size_t n_measurements)
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
void
fill(std::unordered_map<int, int>& m, std::size_t n_measurements)
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

// Fill the container , with n key/value pairs.
template <typename SOA>
void
fill_soa(SOA& m, std::size_t n_measurements)
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
  fill_soa(m, n_measurements);
}

void
fill(aos_deq& m, std::size_t n_measurements)
{
  fill_soa(m, n_measurements);
}

void
fill(aos_list& m, std::size_t n_measurements)
{
  fill_soa(m, n_measurements);
}
