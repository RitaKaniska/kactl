/**
 * Author: ShahjalalShohag
 * Date: 2023-11-30
 * Description:
 */

#include "Polynomial.h"
#include "Polynomial_evaluate.h"

//In-struct
poly interpolate(vector<poly> &tree, int v, int l, int r, int ly, int ry, vector<mint> &y) { //auxiliary interpolation function
  if(l == r) return {y[ly] / a[0]};
  int mid = l + r >> 1;
  int midy = ly + ry >> 1;
  auto A = (*this % tree[2 * v]).interpolate(tree, 2 * v, l, mid, ly, midy, y);
  auto B = (*this % tree[2 * v + 1]).interpolate(tree, 2 * v + 1, mid + 1, r, midy + 1, ry, y);
  return A * tree[2 * v + 1] + B * tree[2 * v];
}

//Not in-struct
//O(nlog^2n)
poly interpolate(vector<mint> x, vector<mint> y) { //interpolates minimum polynomial from (xi, yi) pairs
  int n = x.size(); assert(n == (int)y.size());//assert(all x are distinct)
  vector<poly> tree(4 * n);
  poly tmp({1});
  return tmp.build(tree, 1, 0, n - 1, x).differentiate().interpolate(tree, 1, 0, n - 1, 0, n - 1, y);
}
