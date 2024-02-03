/**
 * Author: ShahjalalShohag
 * Date: 2023-11-30
 * Description: In-struct. Given $p(x)$ and $g(x)$, calculate $p(g(x))$.
 */

#include "Polynomial.h"

// p(g(x))
// O(n^2 logn)
poly composition_brute(poly g, int deg){
  int n = size();
  poly c(deg, 0), pw({1});
  for (int i = 0; i < min(deg, n); i++){
    int d = min(deg, (int)pw.size());
    for (int j = 0; j < d; j++){
      c.a[j] += coef(i) * pw[j];
    }
    pw *= g;
    if (pw.size() > deg) pw.a.resize(deg);
  }
  return c;
}
// p(g(x))
// O(nlogn * sqrt(nlogn))
poly composition(poly g, int deg) {
  int n = size();
  int k = 1;
  while (k * k <= n) k++;
  k--;
  int d = n / k;
  if (k * d < n) d++;
  vector<poly> pw(k + 3, poly({1}));
  for(int i = 1; i <= k + 2; i++) {
    pw[i] = pw[i - 1] * g;
    if (pw[i].size() > deg) pw[i].a.resize(deg);
  }
  vector<poly> fi(k, poly(deg, 0));
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < d; j++) {
      int idx = i * d + j;
      if (idx >= n) break;
      int sz = min(fi[i].size(), pw[j].size());
      for (int t = 0; t < sz; t++) {
        fi[i].a[t] += pw[j][t] * coef(idx);
      }
    }
  }
  poly ret(deg, 0), gd({1});
  for (int i = 0; i < k; i++){
    fi[i] = fi[i] * gd;
    int sz = min((int)ret.size(), (int)fi[i].size());
    for (int j = 0; j < sz; j++) ret.a[j] += fi[i][j];
    gd = gd * pw[d];
    if (gd.size() > deg) gd.a.resize(deg);
  }
  return ret;
}
