#pragma once

#include <map>
#include <unordered_map>
#include <vector>

#include "data_structures.hh"

// Iterate through all values in map; we don't look at the keys.
int sum(std::map<int, int> const& m);
int sum(soa_vector const& s);
int sum(std::unordered_map<int, int> const& m);
int sum(aos_vector const& s);
int sum(soa_deq const& s);
int sum(soa_slist const& s);
int sum(aos_deq const& s);
int sum(aos_slist const& s);

// This is the type of the result returned by all the find_largest functions.
struct result_t {
  int key = -1;
  int value = -1;
};

result_t find_largest(std::map<int, int> const& m);
result_t find_largest(std::unordered_map<int, int> const& m);

result_t find_largest(aos_vector const& m);
result_t find_largest(aos_deq const& s);
result_t find_largest(aos_slist const& s);

result_t find_largest(soa_vector const& m);
result_t find_largest(soa_deq const& s);
result_t find_largest(soa_slist const& s);