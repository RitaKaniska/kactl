/**
 * Author: Robert1003
 * Source: https://robert1003.github.io/2020/02/29/dp-opt-knuth.html
 * Description: Solves DP on intervals: $dp[i] = \min_{j < i}(dp[j] + cost(i+1, j))$, where $cost(i, j)$ satisfies quarangle equality. (or $H_i < H_{i + 1} \forall i$, $H_i$ is optimal transition point of $i$) 
 * Status: Tested on https://codeforces.com/gym/101981 problem B
 * Time: O(NlogN)
 */

struct Node { 
  ll p, l, r; // p is the best transition point for dp[l], dp[l+1], ..., dp[r]
}; 

deque<Node> dq;
dp[0] = 0;
dq.push_back({0, 1, n});
for(int i = 1 ; i <= n ; ++i) {
  dp[i] = f(dq.front().p, i)
  // r == i implies that this Node is useless later, so pop it
  if(dq.front().r == i) dq.pop_front(); 
  // else update l
  else dq.front().l++;

  // find l, r for i
  // f(i, dq.back().l) < f(dq.back().p, dq.back().l) implies the last Node in deque is useless
  while(!dq.empty() && f(i, dq.back().l) < f(dq.back().p, dq.back().l)) dq.pop_back();
  // we know that r=n, now we need to find l
  // l=i+1 as deque is empty
  if(dq.empty()) dq.push_back({i, i + 1, n});
  // find l by binary search
  else {
    int l = dq.back().l, r = dq.back().r;
    while(l < r) {
      int mid = r - (r - l) / 2;
      if(f(i, mid) < f(dq.back().p, mid)) r = mid - 1;
      else l = mid;
    }
    dq.back().r = l;
    // l == n means that i is useless
    if(l != n) dq.push_back({i, l + 1, n});
  }
}
