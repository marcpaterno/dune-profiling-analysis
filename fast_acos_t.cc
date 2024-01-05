#include <cmath>
#include <iomanip>
#include <iostream>

#include "nanobench.h"

// This is from LArSim.

 __attribute__((noinline))
 double fast_acos(double x) {
  double negate = double(x < 0.);
  x = std::abs(x);
  x -= double(x > 1.) * (x - 1.); // <- equivalent to min(1.,x), but faster
  double ret = -0.0187293;
  ret = ret * x;
  ret = ret + 0.0742610;
  ret = ret * x;
  ret = ret - 0.2121144;
  ret = ret * x;
  ret = ret + 1.5707288;
  ret = ret * std::sqrt(1. - x);
  ret = ret - 2. * negate * ret;
  return negate * 3.14159265358979 + ret;
}

__attribute__((noinline))
double hastings_acos_obfuscated(double xin) {
  double x = xin;
  double term = 0.0;
  double factor = 1.0;

  if (xin < 0) {
    x *= -1.0;
    factor = -1.0;
    term = M_PI;
  }

  double const a0 =  1.5707288;
  double const a1 = -0.2121144;
  double const a2 =  0.0742610;
  double const a3 = -0.0187293;
  double ret = a3;
  ret *= x;
  ret += a2;
  ret *= x;
  ret += a1;
  ret *= x;
  ret += a0;
  ret *= std::sqrt(1.0-x);
  return factor * ret + term;
}


__attribute__((noinline))
double hastings_acos(double xin) {
  double const x = std::abs(xin);
  double const a0 =  1.5707288;
  double const a1 = -0.2121144;
  double const a2 =  0.0742610;
  double const a3 = -0.0187293;
  double ret = a3;
  ret *= x;
  ret += a2;
  ret *= x;
  ret += a1;
  ret *= x;
  ret += a0;
  ret *= std::sqrt(1.0-x);
  if (xin >= 0) return ret;
  return M_PI - ret;
}


__attribute__((noinline))
double hastings_acos_4(double xin)
{
  double const a3 = -2.08730442907856008e-02;
  double const a2 =  7.68769404161671888e-02;
  double const a1 = -2.12871094165645952e-01;
  double const a0 =  1.57075835365209659e+00;
  double const x = std::abs(xin);
  double ret = a3;
  ret *= x;
  ret += a2;
  ret *= x;
  ret += a1;
  ret *= x;
  ret += a0;
  ret *= std::sqrt(1.0-x);
  if (xin >= 0) return ret;
  return M_PI - ret;
}


// agm_acos is disabled because it is terribly slow, even when
// used with poor accuracy.
#if 0
inline double agm_acos_aux(double x) {
  double const L = std::sqrt(1-x*x);
  double a = x;
  double b = 1.0;
  while(std::abs(a-b) > 1.e-3)
  {
    a = 0.5 * (a+b);
    b = std::sqrt(a*b);
  }
  return L/a;
}

__attribute__((noinline))
double agm_acos(double xin) {
  double x = std::abs(xin);
  double res = agm_acos_aux(x);
  if (xin >= 0.) return res;
  return M_PI - res;
}
#endif

__attribute__((noinline))
double std_acos(double x)
{
  return std::acos(x);
}


__attribute__((noinline))
float std_acosf(float x)
{
  return std::acos(x);
}

template <typename F>
void
run_bench(F func, ankerl::nanobench::Bench* bench, char const* name)
{
  volatile double x = 0.457;
  volatile double y = -0.57;
  bench->run(name, [&]() {
      double z1 = func(x);
      double z2 = func(y);
      ankerl::nanobench::doNotOptimizeAway(z1);
      ankerl::nanobench::doNotOptimizeAway(z2);
      });
}

void bmark() {
  ankerl::nanobench::Bench b;
  b.title("acos tests")
    .performanceCounters(true)
    .minEpochIterations(1000 * 1000);
  run_bench(&fast_acos, &b, "fast_acos");
  run_bench(&hastings_acos, &b, "hastings_acos");
  run_bench(&hastings_acos_obfuscated, &b, "hastings_acos_obfuscated");
  run_bench(&std_acos, &b, "acosd");
  run_bench(&std_acosf, &b, "acosf");
  run_bench(&hastings_acos_4, &b, "hastings_acos_4");
}

int main() {
  int const npoints = 100 * 1000;
  double const xmin = -1.0;
  double const xmax = 1.0;
  double dx = (xmax - xmin) / npoints;
  std::cerr << "x\tfast\tstd\tstdf\thastings\thastings_4\n" << std::setprecision(17);

  for (int i = 0; i != npoints; ++i) {
    double const x = xmin + i * dx;
    float const xf = x;
    std::cerr << x << '\t'
              << fast_acos(x) << '\t'
              << std::acos(x) << '\t'
              << std::acos(xf) << '\t'
              << hastings_acos(x) << '\t'
              << hastings_acos_4(x) << '\n';
  }

  bmark();
}
