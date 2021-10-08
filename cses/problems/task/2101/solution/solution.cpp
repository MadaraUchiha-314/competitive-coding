/*
 * Problem Name/URL: https://cses.fi/problemset/task/2101/
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

template <typename T>
class PersistentArray {
  public:
    vector<vector<pair<int, T>>> arr;
    
    PersistentArray() {}

    PersistentArray(int n) { arr.resize(n); }

    PersistentArray(vector<T>& initial_array) {
      arr.resize(initial_array.size());
      for (int i = 0; i < initial_array.size(); i++) {
        arr[i].push_back({ 0, initial_array[i] });
      }
    }

    void resize(int n) { arr.resize(n); }

    void resize(int n, T a) {
      arr.resize(n);
      for (int i = 0; i < n; i++) {
        arr[i].push_back({ 0, a });
      }
    }

    void clear() { arr.clear(); }

    void push_back(T item, int index, int time) { arr[index].push_back({ time, item }); }

    T at(int index, int time) {
      return prev(
        upper_bound(arr[index].begin(), arr[index].end(), make_pair(time, numeric_limits<T>::max()))
      )->second;
    }
};


class PersistentDisjointSet {
  public:
    PersistentArray<int> parent;
    PersistentArray<int> size;

    PersistentDisjointSet(int n) {
      parent.resize(n);
      size.resize(n, 1);
      for (int i = 0; i < n; i++) parent.push_back(i, i, 0);
    }

    int root(int a, int t) {
      int temp = a;
      while (parent.at(a, t) != a) {
        a = parent.at(a, t);
      }
      return a;
    }

    int find(int a, int b, int t) {
      return root(a, t) == root(b, t);
    }

    void merge(int a, int b, int t) {
      int root_a = root(a, t); int root_b = root(b, t);
      if (root_a != root_b) {
         if (size.at(root_a, t) < size.at(root_b, t)) {
          parent.push_back(parent.at(root_b, t), root_a, t);
          size.push_back(size.at(root_b, t) + size.at(root_a, t), root_b, t);
        } else {
          parent.push_back(parent.at(root_a, t), root_b, t);
          size.push_back(size.at(root_a, t) + size.at(root_b, t), root_a, t);
        }
      }
    }
};

/**
 * Problem Specific Stuff
 */
int N, M, Q;
vector<pair<int, int>> edges;
vector<pair<int, int>> queries;

int infinity = numeric_limits<int>::max();
int null_val = -1;

void solve() {
  PersistentDisjointSet pds(N);
  for (int i = 0; i < edges.size(); i++) {
    pds.merge(edges[i].first - 1, edges[i].second - 1, i + 1);
  }

  for (auto [from, to]: queries) {
    int low = 0, high = M + 1;
    int answer = -1;
    int mid = (high + low) / 2;

    while (low <= high) {
      mid = (high + low) / 2;
      if (pds.find(from - 1, to - 1, mid)) {
        high = mid - 1;
        answer = mid;
      } else {
        low = mid + 1;
      }
    }
    cout << answer << "\n";
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
  cin >> N >> M >> Q;
  edges.resize(M);
  queries.resize(Q);
  for (int i = 0; i < M; i++) {
    cin >> edges[i].first >> edges[i].second;
  }
  for (int i = 0; i < Q; i++) {
    cin >> queries[i].first >> queries[i].second;
  }
}
