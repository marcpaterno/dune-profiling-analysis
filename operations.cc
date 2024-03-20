#include "operations.hh"
#include "sp2.hh"
#include "sp_pairs.hh"

////////////////////////////////////////////
// Part 1: Functions that look only at values, not keys.
//
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

// Iterate through all the structs, looking only at the nphot values.
int
sum(sp_pairs const& s)
{
  int sum = 0;
  for (auto const& p : s)
    sum += p.nphots;
  return sum;
}

////////////////////////////////////////////
// Part 2: Functions that look at both values and keys.
//

// Iterate through all keys and values in map.
result_t
find_largest(std::map<int, int> const& m)
{
  result_t result;
  for (auto [k, v] : m) {
    if (result.value < v) {
      result.key = k;
      result.value = v;
    }
  }
  return result;
}

// Iterate through all keys and values in struct.
result_t
find_largest(sp2 const& s)
{
  result_t result;
  for (std::size_t i = 0; i != s.nphots.size(); ++i) {
    if (result.value < s.nphots[i]) {
      result.key = s.ticks[i];
      result.value = s.nphots[i];
    }
  }
  return result;
}

// Iterate through all keys and values in the hashmap.
result_t
find_largest(std::unordered_map<int, int> const& m)
{
  result_t result;
  for (auto [k, v] : m) {
    if (result.value < v) {
      result.key = k;
      result.value = v;
    }
  }
  return result;
}

// Iterate through all the structs, looking at both keys and values.
result_t
find_largest(sp_pairs const& s)
{
  result_t result;
  for (auto const& p : s) {
    if (result.value < p.nphots) {
      result.key = p.ticks;
      result.value = p.nphots;
    }
  }
  return result;
}