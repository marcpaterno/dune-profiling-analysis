#pragma once

#include "sp_pairs.hh"
#include <map>
#include <unordered_map>
#include <vector>

struct sp2;

// Iterate through all values in map; we don't look at the keys.
int sum(std::map<int, int> const& m);
int sum(sp2 const& s);
int sum(std::unordered_map<int, int> const& m);
int sum(sp_pairs const& s);

// This is the type of the result returned by all the find_largest functions.
struct result_t {
  int key = -1;
  int value = -1;
};

result_t find_largest(std::map<int, int> const& m);
result_t find_largest(sp2 const& m);
result_t find_largest(std::unordered_map<int, int> const& m);
result_t find_largest(sp_pairs const& m);
