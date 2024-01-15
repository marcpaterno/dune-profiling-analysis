#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

#include "nanobench.h"

double atan2d(double y, double x)
{
  return std::atan2(y, x);
}

inline double atan_aux2(double z)
{
  // Note: 0 < z <= 1.
  double const a0 = 0.78539816;
  double const a1 = 0.24434610;
  double const a2 = 0.06684611;
  return z * (a0 - (z - 1)*(a1 + a2*z));
}

inline double atan2_aux(double y, double x)
{
  // Note: x > 0 and y > 0.
  double const z = y/x;
  if ( z <= 1.) return atan_aux2(z);
  return M_PI_2 - atan_aux2(1/z);
}

double atan2_1(double y, double x)
{
  if (x > 0) return atan2_aux(y, x);
  if (x < 0)
  {
    if (y >= 0) return atan2_aux(y, x) + M_PI;
    return atan2_aux(y, x) - M_PI;
  }
  // We now know x == 0.0
  if (y > 0) return M_PI_2;
  if (y < 0) return -M_PI_2;
  // We now know y == 0
  return std::numeric_limits<double>::quiet_NaN();
}

template <typename F>
void
run_bench(F func, ankerl::nanobench::Bench* bench, char const* name)
{
  volatile double x = 0.457;
  volatile double y = -0.57;
  bench->run(name, [&]() {
      double z = func(y, x);
      ankerl::nanobench::doNotOptimizeAway(z);
      });
}

void bmark() {
  ankerl::nanobench::Bench b;
  b.title("atan tests")
    .performanceCounters(true)
    .minEpochIterations(1 * 1000 * 1000);
  run_bench(&atan2d, &b, "atan2d");
  run_bench(&atan2_1, &b, "atan2_1");
}

int main() {
  int const npoints = 10 * 1000;
  double const ymin = 0.0;
  double const ymax = 1.0;
  double dy = (ymax - ymin) / npoints;
  std::cerr << "x\tatan2d\n" << std::setprecision(17);

  for (int i = 0; i != npoints+1; ++i) {
    // double const y = ymin + i * dy;
    double const frac = static_cast<double>(i)/npoints;
    double const y = ymax * frac; // we know that ymin is zero
    std::cerr << y 
      << '\t' << atan2d(y, 1.0)
      << '\t' << atan2_1(y, 1.0)
      << '\n';
  }

  bmark();
}
