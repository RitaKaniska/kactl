/**
 * Author: ShahjalalShohag
 * Date: 2023-11-30
 * Description: Given $p(x)$, calculate $q(x)$ such that, $q(x)^2 = p(x)$.
 */

#include "Polynomial.h"

// if the poly is not zero but the result is zero, then no solution
poly sqrt(int n) const {
  if ((*this)[0] == mint(0)) {
    for (int i = 1; i < size(); i++) {
      if ((*this)[i] != mint(0)) {
        if (i & 1) return {};
        if (n - i / 2 <= 0) break;
        return div_xk(i).sqrt(n - i / 2).mul_xk(i / 2);
      }
    }
    return {};
  }
  mint s = (*this)[0].sqrt();
  if (s == 0)  return {};
  poly y = *this / (*this)[0];
  poly ret({1});
  mint inv2 = mint(1) / 2;
  for (int i = 1; i < n; i <<= 1) {
    ret = (ret + y.mod_xk(i << 1) * ret.inverse(i << 1)) * inv2;
  }
  return ret.mod_xk(n) * s;
}
