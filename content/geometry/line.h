/**
 * Author: Anonymous
 * Date: Unknown
 * License: None
 * Description: Template for line.
 */

template<class T>
struct Line{
    typedef Point<T> P;
    P v; T c;
    Line (P v, T c) : v(v),c(c) {}
    Line (T a, T b, T c) : v(b,-a), c(c) {}
    Line (P p, P q) : v(q-p), c(v.cross(p)) {}

    T side(P p) { return v.cross(p) - c; } /** sideOf point **/
    double dist(P p) { return abs(side(p)) / v.dist(); } /** dist to line **/
    double sqDist(P p) { return side(p)*side(p) / v.dist2(); } /** dist2 to line **/
    Line perpThrough(P p) { return {p, p+v.perp()}; } /** line perp through given point **/
    bool cmpProj(P p, P q) const { return v.dot(p) < v.dot(q); } /** compare 2 points in line in direction to v **/
    Line translate(P t) { return {v, c + v.cross(t)}; } /** translate line by vector t **/
    Line shiftleft(double dist) { return {v, c + dist*v.dist()}; } /** shift left so that the distance of new line to old line is 'dist' */
    P proj(P p) { return p - v.perp()*side(p)/v.dist2(); }
    P refl(P p) { return p - v.perp()*2*side(p)/v.dist2(); }
};

typedef Line<double> line;
bool inter(line l1, line l2, P &out) {
    auto d = l1.v.cross(l2.v);
    if (d==0) return false;
    out = (l2.v*l1.c - l1.v*l2.c) / d; // requires floating-point coordinates
    return true;
};
