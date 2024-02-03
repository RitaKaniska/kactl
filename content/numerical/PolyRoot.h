/**
 * Author: ShahjalalShohag
 * Date: 2023-11-30
 * Description: Given $p(x)$ and an integer $k$. Calculate $k-th$ root of $p(x)$.
 */

#include "Polynomial.h"

poly root(int n, int k = 2) const { //kth root of p(x) mod x^n
  if(is_zero()) return *this;
  if (k == 1) return mod_xk(n);
  assert(a[0] == 1);
  poly q({1});
  for(int i = 1; i < n; i <<= 1){
    if(k == 2) q += mod_xk(2 * i) * q.inverse(2 * i);
    else q = q * mint(k - 1) + mod_xk(2 * i) * q.inverse(2 * i).pow(k - 1, 2 * i);
    q = q.mod_xk(2 * i) / mint(k);
  }
  return q.mod_xk(n);
}
