/**
 * Author: ShahjalalShohag
 * Date: 2023-11-30
 * Description:
 */

#include "Polynomial.h"
#include "Polynomial_log.h"

poly exp(int n) const { //e ^ p(x) mod x^n
  if(is_zero()) return {1};
  assert(a[0] == 0);
  poly ans({1});
  int i = 1;
  while(i < n) {
    poly C = ans.log(2 * i).div_xk(i) - substr(i, 2 * i);
    ans -= (ans * C).mod_xk(i).mul_xk(i);
    i *= 2;
  }
  return ans.mod_xk(n);
}
