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

namespace StringHashing {
  class StringHash {
    public:
      static const int mod = (int) 1e9 + 7;
      static const int p = 9973;

      static vector<int> pows;
      static const int max_len = 1e6;

      static void init() {
        pows.resize(max_len);
        pows[0] = 1;
        for (int i = 1; i < max_len; i++) {
          pows[i] = mul(pows[i - 1], p, mod);
        }
      }

      vector<int> prefix_hash;

      StringHash(string s) {
        prefix_hash.resize(s.length() + 1);
        prefix_hash[0] = 0;
        for (int i = 0; i < s.length(); i++) {
          prefix_hash[i + 1] = add(prefix_hash[i], mul((int) (s[i]), pows[i], mod), mod);
        }
      }

      int get_hash(int l, int r) {
        l++; r++;
        return mul(inv(power(p, l, mod), mod), sub(prefix_hash[r], prefix_hash[l - 1], mod), mod);
      }
  };
}

using namespace StringHashing;

vector<int> StringHash::pows;

void input();

string s, p;

void solve() {
  StringHash::init();
  StringHash sh(s);
  StringHash ph(p);
  int answer = 0;
  for (int i = 0 ; i + p.length() <= s.length(); i++) {
    if (ph.get_hash(0, p.length() - 1) == sh.get_hash(i, i + p.length() - 1)) {
      answer += 1;
    }
  }
  cout << answer << "\n";
}



int main () {
  /**
   * Fast IO.
   */
  ios::sync_with_stdio(false);
  cin.tie(0);

  int T = 1;
  for (int t = 0; t < T; t++) {
    input();
    solve();
  }
  return 0;
}

void input() {
  cin >> s >> p;
}
