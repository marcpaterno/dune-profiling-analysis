#pragma once

#include <deque>
#include <forward_list>
#include <vector>

struct soa_vector {
  std::vector<int> ticks;
  std::vector<int> nphots;

  void clear() noexcept;
};

inline void
soa_vector::clear() noexcept
{
  ticks.clear();
  nphots.clear();
}

struct soa_deq {
  std::deque<int> ticks;
  std::deque<int> nphots;

  void clear() noexcept;
};

inline void
soa_deq::clear() noexcept
{
  ticks.clear();
  nphots.clear();
}

struct soa_slist {
  std::forward_list<int> ticks;
  std::forward_list<int> nphots;

  void clear() noexcept;
};

inline void
soa_slist::clear() noexcept
{
  ticks.clear();
  nphots.clear();
}

// using record = std::pair<int, int>;

struct record {
  int first;
  int second;
};

using aos_vector = std::vector<record>;
using aos_deq = std::deque<record>;
using aos_list = std::forward_list<record>;
