/**
 * Author: adamant
 * Date: 2023-11-30
 * Description: Modulo template.
 */

template<typename T>
T bpow(T const& x, int64_t n) {
    if(n == 0) {
        return T(1);
    } else {
        auto t = bpow(x, n / 2);
        t = t * t;
        return n % 2 ? x * t : t;
    }
}

template<int m>
struct modular {
    // https://en.wikipedia.org/wiki/Berlekamp-Rabin_algorithm
    // solves x^2 = y (mod m) assuming m is prime in O(log m).
    // returns nullopt if no sol.
    optional<modular> sqrt() const {
        static modular y;
        y = *this;
        if(r == 0) {
            return 0;
        } else if(bpow(y, (m - 1) / 2) != modular(1)) {
            return nullopt;
        } else {
            while(true) {
                modular z = rng();
                if(z * z == *this) {
                    return z;
                }
                struct lin {
                    modular a, b;
                    lin(modular a, modular b): a(a), b(b) {}
                    lin(modular a): a(a), b(0) {}
                    lin operator * (const lin& t) const {
                        return {
                            a * t.a + b * t.b * y,
                            a * t.b + b * t.a
                        };
                    }
                } x(z, 1); // z + x
                x = bpow(x, (m - 1) / 2);
                if(x.b != modular(0)) {
                    return x.b.inv();
                }
            }
        }
    }
    
    int r;
    constexpr modular(): r(0) {}
    constexpr modular(int64_t rr): r(rr % m) {if(r < 0) r += m;}
    modular inv() const {return bpow(*this, m - 2);}
    modular operator - () const {return r ? m - r : 0;}
    modular operator * (const modular &t) const {return (int64_t)r * t.r % m;}
    modular operator / (const modular &t) const {return *this * t.inv();}
    modular operator += (const modular &t) {r += t.r; r = min<unsigned>(r, r - m); return *this;}
    modular operator -= (const modular &t) {r -= t.r; r = min<unsigned>(r, r + m); return *this;}
    modular operator + (const modular &t) const {return modular(*this) += t;}
    modular operator - (const modular &t) const {return modular(*this) -= t;}
    modular operator *= (const modular &t) {return *this = *this * t;}
    modular operator /= (const modular &t) {return *this = *this / t;}
    
    bool operator == (const modular &t) const {return r == t.r;}
    bool operator != (const modular &t) const {return r != t.r;}
    
    explicit operator int() const {return r;}
    int64_t rem() const {return 2 * r > m ? r - m : r;}
};

template<int T>
istream& operator >> (istream &in, modular<T> &x) {
    return in >> x.r;
}

template<int T>
ostream& operator << (ostream &out, modular<T> const& x) {
    return out << x.r;
}
