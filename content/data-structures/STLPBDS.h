/**
 * Author: DeMen100ns
 * Date: 2024-01-01
 * Description: - order_of_key(k) : Number of items strictly smaller than k.
 * - find_by_order(k) : K-th element in a set (counting from zero).
 */

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>

using namespace __gnu_pbds;
using namespace __gnu_cxx;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

struct chash { // large odd number for C
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	ll operator()(ll x) const { return __builtin_bswap64(x*C); }
};

__gnu_pbds::gp_hash_table<ll,int,chash> h({},{},{},{},{1<<16}); //hash map
ordered_set s; //ordered_set
rope <int> v; //rope (almost like string...)
