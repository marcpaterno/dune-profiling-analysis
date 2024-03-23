#pragma once

#include "data_structures.hh"
#include <map>
#include <unordered_map>
#include <vector>

void fill(std::map<int, int>& m, std::size_t n_measurements);
void fill(std::unordered_map<int, int>& m, std::size_t n_measurements);

void fill(aos_vector& m, std::size_t n_measurements);
void fill(aos_deq& m, std::size_t n_measurements);
void fill(aos_slist& m, std::size_t n_measurements);

void fill(soa_vector& m, std::size_t n_measurements);
void fill(soa_deq& m, std::size_t n_measurements);
void fill(soa_slist& m, std::size_t n_measurements);
