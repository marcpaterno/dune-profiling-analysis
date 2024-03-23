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
// Iterate through all keys and values in a record-based structure; this
// includes both maps and AOS structures.
template <typename RECORDBASED>
result_t
find_largest_recordbased(RECORDBASED const& m)
{
  result_t result;
  for (auto const& p : m) {
    if (result.value < p.second) {
      result.key = p.first;
      result.value = p.second;
    }
  }
  return result;
}

result_t
find_largest(std::map<int, int> const& m)
{
  return find_largest_recordbased(m);
}

result_t
find_largest(std::unordered_map<int, int> const& m)
{
  return find_largest_recordbased(m);
}

result_t
find_largest(aos_vector const& s)
{
  return find_largest_recordbased(s);
}

result_t
find_largest(aos_deq const& s)
{
  return find_largest_recordbased(s);
}

result_t
find_largest(aos_slist const& s)
{
  return find_largest_recordbased(s);
}

// Iterate through all keys and values in a SOA structure.
template <typename SOA>
result_t
find_largest_soa(SOA const& s)
{
  result_t result;
  auto i_ticks = s.ticks.cbegin();
  auto i_nphots = s.nphots.cbegin();
  auto nphots_end = s.nphots.cend();
  for (; i_nphots != nphots_end; ++i_ticks, ++i_nphots) {
    if (result.value < *i_nphots) {
      result.key = *i_ticks;
      result.value = *i_nphots;
    }
  }
  return result;
}

result_t
find_largest(soa_vector const& s)
{
  return find_largest_soa(s);
}

result_t
find_largest(soa_deq const& s)
{
  return find_largest_soa(s);
}

result_t
find_largest(soa_slist const& s)
{
  return find_largest_soa(s);
}
