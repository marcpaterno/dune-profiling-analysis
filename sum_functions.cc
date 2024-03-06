#include "sum_functions.hh"
#include "sp2.hh"

// Iterate through all values in map; we don't look at the keys.
int
sum(std::map<int, int> const& m)
{
  int sum = 0;
  for (auto const& p : m)
    sum += p.second;
  return sum;
}

// Iterate through all values in struct; we don't look at the keys.
int
sum(sp2 const& s)
{
  int sum = 0;
  for (auto const& p : s.nphots)
    sum += p;
  return sum;
}

// Iterate through all values in the hashmap; we don't look at the keys.
int
sum(std::unordered_map<int, int> const& m)
{
  int sum = 0;
  for (auto const& p : m)
    sum += p.second;
  return sum;
}
