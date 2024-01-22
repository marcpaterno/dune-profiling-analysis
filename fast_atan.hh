#pragma once


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

inline double atan2_1(double y, double x) {
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


inline double atan2_4(double y, double x) {
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

