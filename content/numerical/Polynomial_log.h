

#include "Polynomial.h"

poly log(int n) const { //ln p(x) mod x^n
  assert(a[0] == 1);
  return (differentiate().mod_xk(n) * inverse(n)).integrate().mod_xk(n);
}
