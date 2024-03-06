#pragma once

#include <map>
#include <unordered_map>
#include <vector>

struct sp2;

// Iterate through all values in map; we don't look at the keys.
int sum(std::map<int, int> const& m);
int sum(sp2 const& s);
int sum(std::unordered_map<int, int> const& m);
