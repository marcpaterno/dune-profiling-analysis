#include <algorithm> // for std::generate
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>

#include "nanobench.h"

double atan2d(double y, double x) { return std::atan2(y, x); }

inline double atan_aux2(double z) {
  // Note: 0 < z <= 1.
  double const a0 = 7.84086493111993965e-01;
  double const a1 = 2.43049810801771404e-01;
  double const a2 = 7.67849627218896019e-02;
  return z * (a0 - (z - 1) * (a1 + a2 * z));
}

inline double atan_aux2_4(double z) {
  // Note: 0 < z <= 1.
  double const a0 = 7.85534551672149362e-01;
  double const a1 = 2.17350373225576182e-01;
  double const a2 = -1.39301583348149155e-01;
  double const a3 = -1.44923156111041140e+00;
  return z * (a0 - (z - 1) * (a1 + a2 *z*(a3 + z)));
}

inline double atan2_aux_4(double z) {
  bool const negative = (z < 0.);
  double abz = std::fabs(z);
  double tmp = (abz <= 1.) ? atan_aux2_4(abz) : M_PI_2 - atan_aux2_4(1. / abz);
  if (z >= 0.)
    return tmp;
  return -tmp;
}


inline double atan2_aux(double z) {
  bool const negative = (z < 0.);
  double abz = std::fabs(z);
  double tmp = (abz <= 1.) ? atan_aux2(abz) : M_PI_2 - atan_aux2(1. / abz);
  if (z >= 0.)
    return tmp;
  return -tmp;
}

double atan2_1(double y, double x) {
  if (x == 0) {
    if (y > 0)
      return M_PI_2;
    if (y < 0)
      return -M_PI_2;
    // We now know y == 0
    return std::numeric_limits<double>::quiet_NaN();
  }
  // We now know x != 0.0
  double const tmp = atan2_aux(y / x);
  if (x > 0)
    return tmp;
  // Now we know x < 0
  if (y >= 0)
    return M_PI + tmp;
  return -M_PI + tmp;
}


double atan2_4(double y, double x) {
  if (x == 0) {
    if (y > 0)
      return M_PI_2;
    if (y < 0)
      return -M_PI_2;
    // We now know y == 0
    return std::numeric_limits<double>::quiet_NaN();
  }
  // We now know x != 0.0
  double const tmp = atan2_aux_4(y / x);
  if (x > 0)
    return tmp;
  // Now we know x < 0
  if (y >= 0)
    return M_PI + tmp;
  return -M_PI + tmp;
}

std::vector<double> make_randoms(unsigned long n) {
  std::minstd_rand0 engine(123);
  std::uniform_real_distribution<double> dist{-4.0, 4.0};
  auto gen = [&dist, &engine]() { return dist(engine); };

  std::vector<double> values(n);
  std::generate(begin(values), end(values), gen);
  return values;
}

template <typename F>
void run_bench(F func, ankerl::nanobench::Bench *bench, char const *name) {
  // array sizes are set large enough to exhause L2 cache on my laptop.
  unsigned long const n = 1 * 1000 * 1000;
  auto vals = make_randoms(2 * n);
  std::vector<double> zs(n);
  bench->run(name, [&]() {
    for (int i = 0; i != n; ++i) {
      zs[i] = func(vals[i], vals[i + n]);
    }
    ankerl::nanobench::doNotOptimizeAway(zs);
  });
}

void bmark() {
  ankerl::nanobench::Bench b;
  b.title("atan tests");
  b.performanceCounters(true);
  // b.minEpochIterations(1 * 1000);

  run_bench(&atan2d, &b, "atan2d");
  run_bench(&atan2_1, &b, "atan2_1");
  run_bench(&atan2_4, &b, "atan2_4");
}

int main() {
  int const npoints = 40 * 1000;
  double const ymin = -4.0;
  double const ymax = 4.0;
  double dy = (ymax - ymin) / npoints;
  std::cerr << "x\tatan2d\tatan2_1\tatan2_4\n" << std::setprecision(17);

  for (int i = 0; i != npoints + 1; ++i) {
    double const y = ymin + i * dy;
    // double const frac = static_cast<double>(i)/npoints;
    // double const y = ymax * frac; // we know that ymin is zero
    std::cerr << y <<
      '\t' << atan2d(y, 1.0)
      << '\t' << atan2_1(y, 1.0)
      << '\t' << atan2_4(y, 1.0)
      << '\n';
  }

  bmark();
}
