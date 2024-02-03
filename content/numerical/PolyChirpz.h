/**
 * Author: ShahjalalShohag
 * Date: 2023-11-30
 * Description: In struct. Given $z, n$, calculate $P(1), P(z), P(z^2), ..., P(z^(n-1))$ in $O(n \log n)$.
 */

#include "Polynomial.h"

poly mulx(mint x) { //component-wise multiplication with x^k
  mint cur = 1; poly ans(*this);
  for(int i = 0; i < size(); i++) ans.a[i] *= cur, cur *= x;
  return ans;
}
poly mulx_sq(mint x) { //component-wise multiplication with x^{k^2}
  mint cur = x, total = 1, xx = x * x; poly ans(*this);
  for(int i = 0; i < size(); i++) ans.a[i] *= total, total *= cur, cur *= xx;
  return ans;
}
vector<mint> chirpz_even(mint z, int n) { //P(1), P(z^2), P(z^4), ..., P(z^2(n-1))
  int m = size() - 1;
  if(is_zero()) return vector<mint>(n, 0);
  vector<mint> vv(m + n);
  mint iz = z.inv(), zz = iz * iz, cur = iz, total = 1;
  for(int i = 0; i <= max(n - 1, m); i++) {
    if(i <= m) vv[m - i] = total;
    if(i < n) vv[m + i] = total;
    total *= cur; cur *= zz;
  }
  poly w = (mulx_sq(z) * vv).substr(m, m + n).mulx_sq(z);
  vector<mint> ans(n);
  for(int i = 0; i < n; i++) ans[i] = w[i];
  return ans;
}
//O(nlogn)
vector<mint> chirpz(mint z, int n) { //P(1), P(z), P(z^2), ..., P(z^(n-1))
  auto even = chirpz_even(z, (n + 1) / 2);
  auto odd = mulx(z).chirpz_even(z, n / 2);
  vector<mint> ans(n);
  for(int i = 0; i < n / 2; i++) {
    ans[2 * i] = even[i];
    ans[2 * i + 1] = odd[i];
  }
  if(n % 2 == 1) ans[n - 1] = even.back();
  return ans;
}
