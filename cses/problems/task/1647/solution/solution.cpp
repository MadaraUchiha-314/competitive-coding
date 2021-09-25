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
 * Misc
 */
#define pcodejam(t) cout << "Case #" << t << ": "

void input();
void solve();

template <typename Item, typename Node, Node create(Item a), Node combine(Node a, Node b)>
class SparseTable {
  public:
    int N;
    vector<vector<Node>> table;

    SparseTable(vector<Item>& nodes) {
      N = (int) nodes.size();
      table.resize(N);
      for (int i = 0; i < N; i++) {
        table[i].push_back(nodes[i]);
      }
      for (int i = 0; i < 30; i++) {
        for (int j = 0; (j + (1 << i)) < N; j++) {
          table[j].push_back(
            combine(
              table[j].back(), table[j + (1 << i)].back()
            )
          );
        }
      }
    }

    Node query(int left, int right) {
      int offset = 32 - __builtin_clz(right - left) - 1;
      int interval = (1 << offset) - 1;
      return combine(
        table[left][offset], table[right - interval][offset]
      );
    }
};

/**
 * Problem Specific Stuff
 */
int N, Q;
vector<int> arr;
vector<pair<int, int>> queries;

int create(int a) { return a; };

void solve() {
  SparseTable<int, int, create, mins> st(arr);
  for (auto query: queries) {
    cout << st.query(query.first - 1, query.second - 1) << "\n";
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
  cin >> N >> Q;
  arr.resize(N);
  queries.resize(Q);
  for (int i = 0; i < N; i++) {
    cin >> arr[i];
  }
  for (int i = 0; i < Q; i++) {
    cin >> queries[i].first >> queries[i].second;
  }
}
