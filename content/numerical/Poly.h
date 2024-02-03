/**
 * Author: ShahjalalShohag
 * Date: 2023-11-30
 * Description:
 */

#include "NumberTheoreticTransform.h"

struct poly {
  vector<mint> a;
  inline void normalize() {
    while((int)a.size() && a.back() == 0) a.pop_back();
  }
  template<class...Args> poly(Args...args): a(args...) { }
  poly(const initializer_list<mint> &x): a(x.begin(), x.end()) { }
  int size() const { return (int)a.size(); }
  inline mint coef(const int i) const { return (i < a.size() && i >= 0) ? a[i]: mint(0); }
  mint operator[](const int i) const { return (i < a.size() && i >= 0) ? a[i]: mint(0); } //Beware!! p[i] = k won't change the value of p.a[i]
  bool is_zero() const {
    for (int i = 0; i < size(); i++) if (a[i] != 0) return 0;
    return 1;
  }   
  poly operator + (const poly &x) const {
    int n = max(size(), x.size());
    vector<mint> ans(n);
    for(int i = 0; i < n; i++) ans[i] = coef(i) + x.coef(i);
    while ((int)ans.size() && ans.back() == 0) ans.pop_back();
    return ans;
  }
  poly operator - (const poly &x) const {
    int n = max(size(), x.size());
    vector<mint> ans(n);
    for(int i = 0; i < n; i++) ans[i] = coef(i) - x.coef(i);
    while ((int)ans.size() && ans.back() == 0) ans.pop_back();
    return ans;
  }
  poly operator * (const poly& b) const {
    if(is_zero() || b.is_zero()) return {};
    vl A, B;
    for(auto x: a) A.push_back(x.value);
    for(auto x: b.a) B.push_back(x.value);
    auto res = multiply(A, B);
    vector<mint> ans;
    for(auto x: res) ans.push_back(mint(x));
    while ((int)ans.size() && ans.back() == 0) ans.pop_back();
    return ans;
  }
  poly operator * (const mint& x) const {
    int n = size();
    vector<mint> ans(n);
    for(int i = 0; i < n; i++) ans[i] = a[i] * x;
    return ans;
  }
  poly operator / (const mint &x) const{ return (*this) * x.inv(); }
  poly& operator += (const poly &x) { return *this = (*this) + x; }
  poly& operator -= (const poly &x) { return *this = (*this) - x; }
  poly& operator *= (const poly &x) { return *this = (*this) * x; }
  poly& operator *= (const mint &x) { return *this = (*this) * x; }
  poly& operator /= (const mint &x) { return *this = (*this) / x; }
  poly mod_xk(int k) const { return {a.begin(), a.begin() + min(k, size())}; } //modulo by x^k
  poly mul_xk(int k) const { // multiply by x^k
    poly ans(*this);
    ans.a.insert(ans.a.begin(), k, 0);
    return ans;
  }
  poly div_xk(int k) const { // divide by x^k
    return vector<mint>(a.begin() + min(k, (int)a.size()), a.end());
  }
  poly substr(int l, int r) const { // return mod_xk(r).div_xk(l)
    l = min(l, size());
    r = min(r, size());
    return vector<mint>(a.begin() + l, a.begin() + r);
  }
  poly reverse_it(int n, bool rev = 0) const { // reverses and leaves only n terms
    poly ans(*this);
    if(rev) { // if rev = 1 then tail goes to head
      ans.a.resize(max(n, (int)ans.a.size()));
    }
    reverse(ans.a.begin(), ans.a.end());
    return ans.mod_xk(n);
  }
  poly differentiate() const {
    int n = size(); vector<mint> ans(n);
    for(int i = 1; i < size(); i++) ans[i - 1] = coef(i) * i;
    return ans;
  }
  poly integrate() const {
    int n = size(); vector<mint> ans(n + 1);
    for(int i = 0; i < size(); i++) ans[i + 1] = coef(i) / (i + 1);
    return ans;
  }
  poly inverse(int n) const {  // 1 / p(x) % x^n, O(nlogn)
    assert(!is_zero()); assert(a[0] != 0);
    poly ans{mint(1) / a[0]};
    for(int i = 1; i < n; i *= 2) {
      ans = (ans * mint(2) - ans * ans * mod_xk(2 * i)).mod_xk(2 * i);
    }
    return ans.mod_xk(n);
  }
  pair<poly, poly> divmod_slow(const poly &b) const { // when divisor or quotient is small
    vector<mint> A(a);
    vector<mint> ans;
    while(A.size() >= b.a.size()) {
      ans.push_back(A.back() / b.a.back());
      if(ans.back() != mint(0)) {
        for(size_t i = 0; i < b.a.size(); i++) {
          A[A.size() - i - 1] -= ans.back() * b.a[b.a.size() - i - 1];
        }
      }
      A.pop_back();
    }
    reverse(ans.begin(), ans.end());
    return {ans, A};
  }
  pair<poly, poly> divmod(const poly &b) const { // returns quotient and remainder of a mod b
    if(size() < b.size()) return {poly{0}, *this};
    int d = size() - b.size();
    if(min(d, b.size()) < 250) return divmod_slow(b);
    poly D = (reverse_it(d + 1) * b.reverse_it(d + 1).inverse(d + 1)).mod_xk(d + 1).reverse_it(d + 1, 1);
    return {D, *this - (D * b)};
  }
  poly operator / (const poly &t) const {return divmod(t).first;}
  poly operator % (const poly &t) const {return divmod(t).second;}
  poly& operator /= (const poly &t) {return *this = divmod(t).first;}
  poly& operator %= (const poly &t) {return *this = divmod(t).second;}
};
