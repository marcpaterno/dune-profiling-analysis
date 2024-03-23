#include "operations.hh"
#include "data_structures.hh"

////////////////////////////////////////////
// Part 1: Functions that look only at values, not keys.
//
// Iterate through all values in a record-based structure; this includes both
// maps and AOS structures.
template <typename RECORDBASED>
int
sum_recordbased(RECORDBASED const& m)
{
  int sum = 0;
  for (auto const& p : m) {
    sum += p.second;
  }
  return sum;
}

int
sum(std::map<int, int> const& m)
{
  return sum_recordbased(m);
}

int
sum(std::unordered_map<int, int> const& m)
{
  return sum_recordbased(m);
}

int
sum(aos_vector const& s)
{
  return sum_recordbased(s);
}

int
sum(aos_deq const& s)
{
  return sum_recordbased(s);
}

int
sum(aos_slist const& s)
{
  return sum_recordbased(s);
}

// Iterate through all values in a SOA structure.
template <typename SOA>
int
sum_soa(SOA const& s)
{
  int sum = 0;
  for (auto const& p : s.nphots) {
    sum += p;
  }
  return sum;
}

int
sum(soa_vector const& s)
{
  return sum_soa(s);
}

int
sum(soa_deq const& s)
{
  return sum_soa(s);
}

int
sum(soa_slist const& s)
{
  return sum_soa(s);
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
find_largest(soa_vector const& s)
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
find_largest(aos_vector const& s)
{
  result_t result;
  for (auto const& p : s) {
    if (result.value < p.second) {
      result.key = p.first;
      result.value = p.second;
    }
  }
  return result;
}
