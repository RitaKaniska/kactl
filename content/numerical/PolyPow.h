/**
 * Author: ShahjalalShohag
 * Date: 2023-11-30
 * Description: Given $p(x)$ and $k$, calculate $q(x) = p(x)^k$.
 */

#include "Polynomial.h"
#include "Polynomial_exp.h"
#include "Polynomial_log.h"

//better for small k, k < 100000
poly pow(int k, int n) const { // p(x)^k mod x^n
  if(is_zero()) return *this;
  poly ans({1}), b = mod_xk(n);
  while(k) {
    if(k & 1) ans = (ans * b).mod_xk(n);
    b = (b * b).mod_xk(n);
    k >>= 1;
  }
  return ans;
}
int leading_xk() const { //minimum i such that C[i] > 0
  if(is_zero()) return 1000000000;
  int res = 0; while(a[res] == 0) res++;
  return res;
}
//better for k > 100000
poly pow2(int k, int n) const { // p(x)^k mod x^n
  if(is_zero()) return *this;
  int i = leading_xk();
  mint j = a[i];
  poly t = div_xk(i) / j;
  poly ans = (t.log(n) * mint(k)).exp(n);
  if (1LL * i * k > n) ans = {0};
  else ans = ans.mul_xk(i * k).mod_xk(n);
  ans *= (j.pow(k));
  return ans;
}
