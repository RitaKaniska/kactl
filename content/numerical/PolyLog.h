/**
 * Author: ShahjalalShohag
 * Date: 2023-11-30
 * Description: In-struct. Given $p(x)$, calculate $q(x)$ such that $q(x) = \ln(p(x)) (p(x) = e^{q(x)})$ 
 */

#include "Polynomial.h"

poly log(int n) const { //ln p(x) mod x^n
  assert(a[0] == 1);
  return (differentiate().mod_xk(n) * inverse(n)).integrate().mod_xk(n);
}
