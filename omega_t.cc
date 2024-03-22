#include "nanobench.h"
#include <cmath>

#include "fast_atan.hh"

inline double
fast_acos(double xin)
{
  double const a3 = -2.08730442907856008e-02;
  double const a2 = 7.68769404161671888e-02;
  double const a1 = -2.12871094165645952e-01;
  double const a0 = 1.57075835365209659e+00;
  double const x = std::abs(xin);
  double ret = a3;
  ret *= x;
  ret += a2;
  ret *= x;
  ret += a1;
  ret *= x;
  ret += a0;
  ret *= std::sqrt(1.0 - x);
  if (xin >= 0)
    return ret;
  return M_PI - ret;
}

__attribute__((noinline)) __attribute__((optimize("-ffast-math"))) double
omega_1(double a, double b, double d)
{
  double const alpha = a / (2 * d);
  double const beta = b / (2 * d);
  double const numerator = 1 + alpha * alpha + beta * beta;
  double const denominator = (1 + alpha * alpha) * (1 + beta * beta);
  double const x = std::sqrt(numerator / denominator);
  return 4 * fast_acos(x);
}

__attribute__((noinline)) __attribute__((optimize("-ffast-math"))) double
omega_2(double a, double b, double d)
{
  double const alpha = a / (2 * d);
  double const beta = b / (2 * d);
  double const numerator = alpha * beta;
  double const denominator = std::sqrt(1 + alpha * alpha + beta * beta);
  return 4 * atan2_4(denominator, numerator);
}

template <typename F>
void
run_bench(F func, ankerl::nanobench::Bench* bench, char const* name)
{
  volatile double a = 0.457;
  volatile double b = -0.57;
  volatile double d = 0.9;

  bench->run(name, [&]() {
    double z = func(a, b, d);
    ankerl::nanobench::doNotOptimizeAway(z);
  });
}

int
main()
{
  ankerl::nanobench::Bench b;
  b.title("solid angle tests")
    .performanceCounters(true)
    .minEpochIterations(100 * 1000 * 1000);
  run_bench(&omega_1, &b, "omega_1");
  run_bench(&omega_2, &b, "omega_3");
}
