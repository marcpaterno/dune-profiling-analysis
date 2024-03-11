#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include "sp_pairs.hh"

struct sp2;

void fill(std::map<int, int>& m, std::size_t n_measurements);
void fill(std::unordered_map<int, int>& m, std::size_t n_measurements);
void fill(sp2& m, std::size_t n_measurements);
void fill(sp_pairs& m, std::size_t n_measurements);

