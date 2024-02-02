/**
 * Author: ShahjalalShohag
 * Date: 2023-11-30
 * Description:
 */

#include "Polynomial.h"

poly build(vector<poly> &ans, int v, int l, int r, vector<mint> &vec) { //builds evaluation tree for (x-a1)(x-a2)...(x-an)
  if(l == r) return ans[v] = poly({-vec[l], 1});
  int mid = l + r >> 1;
  return ans[v] = build(ans, 2 * v, l, mid, vec) * build(ans, 2 * v + 1, mid + 1, r, vec);
}
vector<mint> eval(vector<poly> &tree, int v, int l, int r, vector<mint> &vec) { // auxiliary evaluation function
  if(l == r) return {eval(vec[l])};
  if (size() < 400) {
    vector<mint> ans(r - l + 1, 0);
    for (int i = l; i <= r; i++) ans[i - l] = eval(vec[i]);
    return ans; 
  }
  int mid = l + r >> 1;
  auto A = (*this % tree[2 * v]).eval(tree, 2 * v, l, mid, vec);
  auto B = (*this % tree[2 * v + 1]).eval(tree, 2 * v + 1, mid + 1, r, vec);
  A.insert(A.end(), B.begin(), B.end());
  return A;
}
//O(nlog^2n)
vector<mint> eval(vector<mint> x) {// evaluate polynomial in (x_0, ..., x_n-1)
  int n = x.size();
  if(is_zero()) return vector<mint>(n, mint(0));
  vector<poly> tree(4 * n);
  build(tree, 1, 0, n - 1, x);
  return eval(tree, 1, 0, n - 1, x);
}
