#pragma once

#include <vector>

struct sp2 {
  std::vector<int> ticks;
  std::vector<int> nphots;

  void clear() noexcept;
};

inline
void
sp2::clear() noexcept
{
  ticks.clear();
  nphots.clear();
}

