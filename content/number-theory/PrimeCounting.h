/**
 * Author: Unknown
 * Date: 2023-10-26
 * Source:
 *  - https://codeforces.com/blog/entry/91632
 *  - https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/number-theory%20(11.1)/Primality/PrimeCnt.h
 * Description: Returns sum of $f(p)$ for primes $p$ from $1$ to $n$. Change $f$ and $pref$ to count other things.
 * Time: $O(N^{3/4}/\log N)$, ~60ms for $N=10^{11}$, ~2.5s for $N=10^{13}$
 * Status:
 *  - stress-tested (count primes, sum primes, sum prime squares)
 *  - tested on yosupo:counting_primes
 */

#ifndef CUSTOM_F /// exclude-line
ll f(ll n) { return 1; }    // multiplicative: f(ab) = f(a)f(b)
ll pref(ll n) { return n; } // f(1) + f(2) + ... + f(n)
#endif /// exclude-line
ll count_primes(ll N) { // count_primes(1e13) == 346065536839
	if (N <= 1) return 0;
	auto calc=[&](ll n){return pref(n) - pref(n/2)*f(2) - f(1);};
	int sq = (int)sqrt(N); vl big((sq + 1) / 2), small(sq + 1);
	rep(i,0,sz(small)) small[i] = calc(i);
	rep(i,0,sz(big)) big[i] = calc(N / (2 * i + 1));
	vector<bool> skip(sq + 1); ll sum = 0;
	for (int p = 3; p <= sq; p += 2) if (!skip[p]) {
		for (int j = p; j <= sq; j += 2 * p) skip[j] = 1;
		rep(j,0,min((ll)sz(big), (N / p / p + 1) / 2)) {
			ll k = 1LL * (2 * j + 1) * p;
			big[j] -= ((k>sq ? small[1.*N/k] : big[k/2])-sum) * f(p);
		}
		for (int j = sq, q = sq/p; q >= p; --q) for(;j >= q*p; --j)
			small[j] -= (small[q] - sum) * f(p);
		sum += f(p);
	}
	return big[0] + f(2);
}
