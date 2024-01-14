/**
 * Author: Anonymous
 * Date: Unknown
 * License: None
 * Description: Returns true if segment (a,b) lies within the polygon. If strict is true,
 * it returns false for on the boundary case. 
 * Time: O(n^2)
 * Usage:
 * vector<P> v = {P{4,4}, P{1,2}, P{2,1}};
 * bool in = inPolygon(v, P{3, 3}, P{4,4}, false);
 * Status: stress-tested and tested on https://codeforces.com/gym/104849/problem/J
 */

template<class P>
bool SegmentinPolygon(vector <P> &p, P a, P b, bool strict = false) {
    if (a==b) return inPolygon(p, a, strict);
    if (!inPolygon(p,a,strict)||!inPolygon(p,b,strict)) return false;
    int n = p.size();
    vector <P> tmp;
    for (int i = 0; i < n; i++)
    {
        P cur = p[i], next = p[(i + 1) % n];
        auto v0 = cur.cross(next,a), v1 = cur.cross(next,b), v2 = a.cross(b,cur), v3 = a.cross(b,next);
        if (sgn(v0)*sgn(v1)>0 && sgn(v2)*sgn(v3)>0) continue;
        if (sgn(v0)*sgn(v1)<0 && sgn(v2)*sgn(v3)<0) return false;
        if (onSegment(a, b, cur)) tmp.push_back(cur);
        if (onSegment(a, b, next)) tmp.push_back(next);
        if (onSegment(cur, next, a)) tmp.push_back(a);
        if (onSegment(cur, next, b)) tmp.push_back(b);
    }
    if (strict) return tmp.empty();
    sort(tmp.begin(), tmp.end());
    tmp.resize(unique(tmp.begin(), tmp.end()) - tmp.begin());
 
    for (int i = 1; i < tmp.size(); i++)
    {
        P x = (tmp[i] + tmp[i - 1]) / 2.0;
        if (!inPolygon(p, x, false)) return false;
    }
    return true;
}
