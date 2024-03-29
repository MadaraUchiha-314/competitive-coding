/*
 * Problem Name/URL: 
 */
#include <bits/stdc++.h>
using namespace std;

/**
 * Overloading ostream for Pairs, Vectors, Maps
 */
template <typename T, typename U>
ostream& operator<< (ostream& os, pair<T, U> x) { os << "(" << x.first << "," << " " << x.second << ")"; return os; }

template <typename T>
ostream& operator<< (ostream& os, vector<T> x) { os << "["; for (auto e: x) os << e << "," << " "; os << "]" << "\n"; return os; }

template <typename T, typename U>
ostream& operator<< (ostream& os, map<T, U> x) { os << "{" << "\n"; for (auto [k, v]: x) os << k << ":" << " " << v << "\n"; os << "}" << "\n"; return os; }

#define DEBUG true
#if DEBUG
  #define trace(x, y) cout << x << ":" << " " << y << "\n";
#else
  #define trace(x, y) 1
#endif

/**
 * Defining min and max for multiple arguments.
 */
template <typename T>
T mins(T a, T b) { return min(a, b); }

template <typename T, typename... Args>
T mins(T a, Args... args) { return min(a, mins(args...)); }

template <typename T>
T maxs(T a, T b) { return max(a, b); }

template <typename T, typename... Args>
T maxs(T a, Args... args) { return max(a, maxs(args...)); }

/**
 * Modular arithmetic.
 */
inline int add(int a, int b, int mod) { a += b; if (a >= mod) a -= mod; return a; }
inline int sub(int a, int b, int mod) { a -= b; if (a < 0) a += mod; return a; }
inline int mul(int a, int b, int mod) { return (a * 1ll * b) % mod; }
inline int power(int a, int b, int mod) { int ans = 1; while (b > 0) { if (b & 1) ans = mul(ans, a, mod); a = mul(a, a, mod); b >>= 1; } return ans; }
inline int inv(int a, int mod) { return power(a, mod - 2, mod); }

/**
 * Misc
 */
#define pcodejam(t) cout << "Case #" << t << ": "

void input();
void solve();

/**
 * Problem Specific Stuff
 */

void solve() {
}

int main () {
  /**
   * Fast IO.
   */
  ios::sync_with_stdio(false);
  cin.tie(0);

  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    input();
    solve();
  }
  return 0;
}

void input() {
}
