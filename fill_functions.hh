#pragma once

#include <vector>
#include <map>
#include <unordered_map>

struct sp2;

void fill(std::map<int, int>& m, std::size_t n_measurements);
void fill(std::unordered_map<int, int>& m, std::size_t n_measurements);
void fill(sp2& m, std::size_t n_measurements);

