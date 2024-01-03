#include <cmath>
#include <iomanip>
#include <iostream>

#include "nanobench.h"

// This is from LArSim.

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


double hastings_asin(double x) {
  double const a0 =  1.5707963050;
  double const a1 = -0.2145988016;
  double const a2 =  0.0889789874;
  double const a3 = -0.0501743046;
  double const a4 =  0.0308918810;
  double const a5 = -0.0170881256;
  double const a6 =  0.0066700901;
  double const a7 = -0.0012624911;
  //double const m_pi_2 = static_cast<double>(M_PI_2);
  //double const m_pi = static_cast<double>(M_PI);
  double const res = M_PI_2 - std::sqrt(1.0-x) * (a0 + a1*x + a2*x*x + a3*x*x*x + a4*x*x*x*x + a5*x*x*x*x*x + a6*x*x*x*x*x*x + a7*x*x*x*x*x*x*x);
  if (x>=0) return res;
  return -1.0 * res;
}

template <typename F>
void
run_bench(F func, ankerl::nanobench::Bench* bench, char const* name)
{
  double x = 0.57;
  bench->run(name, [&]() {
      double z = func(x);
      ankerl::nanobench::doNotOptimizeAway(z);
      });
}

#if 0
int main() {
  int const npoints = 100 * 1000;
  double const xmin = -1.0;
  double const xmax = 1.0;
  double dx = (xmax - xmin) / npoints;
  std::cout << "x\tfast\tstd\tstdf\thastings\n" << std::setprecision(17);

  for (int i = 0; i != npoints; ++i) {
    double const x = xmin + i * dx;
    float const xf = x;
    std::cout << x << '\t' << fast_acos(x) << '\t' << std::acos(x) << '\t'
              << std::acos(xf) << '\t' << hastings_acos(x) << '\n';
  }
}
#endif

int main() {
  ankerl::nanobench::Bench b;
  b.title("acos tests")
    .performanceCounters(true)
    .minEpochIterations(50 * 1000 * 1000);
  run_bench(&fast_acos, &b, "fast_acos");
  run_bench(&hastings_acos, &b, "hastings_acos");
  run_bench(&hastings_acos_obfuscated, &b, "hastings_acos_obfuscated");
}
