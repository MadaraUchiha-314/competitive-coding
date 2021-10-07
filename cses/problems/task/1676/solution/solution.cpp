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

class DisjointSet {
  public:
    vector<int> parent;
    vector<int> size;
    int total_components;
    int max_size_component;

    DisjointSet(int n) {
      parent.resize(n);
      size.resize(n, 1);
      max_size_component = 1;
      total_components = n;
      for (int i = 0; i < n; i++) parent[i] = i;
    }

    int root(int a) {
      while (parent[a] != a) {
        parent[a] = parent[parent[a]];
        a = parent[a];
      }
      return a;
    }

    int find(int a, int b) {
      return root(a) == root(b);
    }

    void merge(int a, int b) {
      int root_a = root(a); int root_b = root(b);
      if (root_a != root_b) {
         if (size[root_a] < size[root_b]) {
          parent[root_a] = parent[root_b];
          size[root_b] += size[root_a];
        } else {
          parent[root_b] = parent[root_a];
          size[root_a] += size[root_b];
        }
        max_size_component = max(max_size_component, size[root(a)]);
        total_components = total_components - 1;
      }    
    }
};

/**
 * Problem Specific Stuff
 */
int N, M;
vector<pair<int, int>> edges;

void solve() {
  DisjointSet ds(N);
  for (auto [from, to]: edges) {
    ds.merge(from - 1, to - 1);
    cout << ds.total_components << " " << ds.max_size_component << "\n";
  }
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
  cin >> N >> M;
  edges.resize(M);
  for (int i = 0; i < M; i++) {
    cin >> edges[i].first >> edges[i].second;
  }
}
