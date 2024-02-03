/**
 * Author: ShahjalalShohag
 * Date: 2023-11-30
 * Description:
 */

#include "Polynomial.h"

poly shift_it(int m, vector<poly> &pw) {
  if (size() <= 1) return *this;
  while (m >= size()) m /= 2;
  poly q(a.begin() + m, a.end());
  return q.shift_it(m, pw) * pw[m] + mod_xk(m).shift_it(m, pw);
};
//n log(n)
poly shift(mint a) { //p(x + a)
  int n = size();
  if (n == 1) return *this;
  vector<poly> pw(n);
  pw[0] = poly({1});
  pw[1] = poly({a, 1});
  int i = 2;
  for (; i < n; i *= 2) pw[i] = pw[i / 2] * pw[i / 2];
  return shift_it(i, pw);
}
