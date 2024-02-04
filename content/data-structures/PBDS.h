/**
 * Author: DeMen100ns
 * Date: 2024-01-01
 * Description: - order_of_key(k) : Number of items strictly smaller than k .
 * - find_by_order(k) : K-th element in a set (counting from zero).
 * Time: O(\log N)
 */

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>

using namespace __gnu_pbds;
using namespace __gnu_cxx;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
struct chash {
    int operator()(int x) const { return hash_f(x); }
};

ordered_set s; //ordered_set
gp_hash_table<int, int, chash> mp; //hash map
rope <int> v; //rope (almost like string...)
