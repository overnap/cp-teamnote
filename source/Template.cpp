// precision
cout.precision(16);
cout << fixed;
// gcc bit operator
__builtin_popcount(bits); // popcountll for ll
__builtin_clz(bits);      // left
__builtin_ctz(bits);      // right
// random number generator
random_device rd;
mt19937 mt(rd()); // or use chrono
uniform_int_distribution<> half(0, 1);
cout << half(mt);
// 128MB = int * 33,554,432
struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
        chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename K, typename V, typename Comp = less<K>>
using ordered_map =
    tree<K, V, Comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename Comp = less<K>> // less_equal (MS)
using ordered_set = ordered_map<K, null_type, Comp>;
gp_hash_table<key, int, custom_hash> table;
regex re("^first.[0-9a-z]?*+{n}{n,m}");
regex_match(s, re)
// debug macros
template <class T>
ostream &operator<<(ostream &out, const vector<T> &v) {
  for (const auto &x : v) cout << x << ' ';
  return out;
}
#ifdef LOCAL
#define debug(x) cout << "[Debug] " << #x << " = " << x << '\n'
#else
#define debug(x) void(0)
#endif
// CLion CMakeLists.txt
cmake_minimum_required(VERSION 3.30)
project(ps)
set(CMAKE_CXX_STANDARD 20)
include_directories(.)
MATH(EXPR stack_size "1024 * 1024 * 1024")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")
add_definitions(-DLOCAL)
add_executable(ps main.cpp)