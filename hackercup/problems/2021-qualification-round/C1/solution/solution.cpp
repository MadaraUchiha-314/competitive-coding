/*
 * Problem Name/URL: https://www.facebook.com/codingcompetitions/hacker-cup/2021/qualification-round/problems/C1
 */
#include <bits/stdc++.h>
using namespace std;

#define NEW_LINE "\n"
#define SPACE " "
#define COMMA ","
#define COLON ":"
#define SQB_O "["
#define SQB_C "]"
#define CYB_O "{"
#define CYB_C "}"
#define ROB_O "("
#define ROB_C ")"

/**
 * Overloading ostream for Pairs, Vectors, Maps
 */
template <typename T, typename U>
ostream& operator<< (ostream& os, pair<T, U> x) { os << ROB_O << x.first << COMMA << SPACE << x.second << ROB_C; return os; }

template <typename T>
ostream& operator<< (ostream& os, vector<T> x) { os << SQB_O; for (auto e: x) os << e << COMMA << SPACE; os << SQB_C << NEW_LINE; return os; }

template <typename T, typename U>
ostream& operator<< (ostream& os, map<T, U> x) { os << CYB_O << NEW_LINE; for (auto e: x) os << e << COLON << SPACE << x[e] << NEW_LINE; os << CYB_C << NEW_LINE; return os; }

#define DEBUG true
#if DEBUG
  #define trace(x, y) cout << x << COLON << SPACE << y << NEW_LINE;
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

/**
 * Problem Specific Stuff
 */
int N;
vector<int> coins;
vector<vector<int>> tree;
int child_to_ignore = -1;

const int ROOT = 0;

int dfs(int root, int parent, int ignore_child) {
  int max_coins_child = -1, max_coins = 0;
  for (auto child: tree[root]) {
    if (child != parent && child != ignore_child) {
      int coins_collected = dfs(child, root, ignore_child);
      if (coins_collected > max_coins) {
        max_coins = coins_collected;
        max_coins_child = child;
      }
    }  
  }
  if (root == ROOT) {
    child_to_ignore = max_coins_child;
  }
  return max_coins + coins[root];
}

void solve() {
  cout << dfs(ROOT, -1, -1) + dfs(ROOT, -1, child_to_ignore)  - coins[ROOT] << "\n";
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
    pcodejam(t + 1);
    solve();
  }
  return 0;
}

void input() {
  cin >> N;

  int src, dest;
  tree.clear();
  coins.clear();
  tree.resize(N);
  coins.resize(N);

  for (int i = 0; i < N; i++) {
    cin >> coins[i];
  }
  for (int i = 0; i < N - 1; i++) {
    cin >> src >> dest;
    src--; dest--;
    tree[src].push_back(dest);
    tree[dest].push_back(src);
  }
}
