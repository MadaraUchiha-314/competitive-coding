/*
 * Problem Name/URL: 
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

#define DEBUG false
#if DEBUG
  #define trace(x, y) cout << x << COLON << SPACE << y << NEW_LINE; cout.flush();
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
int N, Q;
vector<vector<int>> tree;
vector<vector<int>> ancestors;
vector<pair<int, int>> queries;

void dfs(int current, vector<int> &current_stack) {
  trace("Current", current); trace("Stack", current_stack);
  for (int i = 1; ((int) current_stack.size() - i - 1) >= 0; i = i << 1) {
    trace("index", current_stack.size() - i - 1);
    ancestors[current].push_back(
      current_stack[(int)current_stack.size() - i - 1]
    );
  }
  for (int child: tree[current]) {
    current_stack.push_back(child);
    dfs(child, current_stack);
    current_stack.pop_back();
  }
}

int kth_ancestor(int node, int k, int i = 0) {
  trace("n", node); trace("k", k); trace("i", i);
  if (k == 0) {
    return node;
  } 
  if (k & 1) {
    if (i >= ancestors[node].size()) {
      return -1;
    }
    return kth_ancestor(ancestors[node][i], k >> 1, i + 1);
  } else {
    return kth_ancestor(node, k >> 1, i + 1);
  }
}

void solve() {
  vector<int> current_stack;
  current_stack.push_back(0);
  dfs(0, current_stack);
  trace("Ancestors", ancestors);
  for (auto q: queries) {
    int answer = kth_ancestor(q.first, q.second);
    if (answer == -1) {
      cout << answer << NEW_LINE;
    } else {
      cout <<  answer + 1 << NEW_LINE;
    }
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
  int boss, x, k;
  cin >> N >> Q;
  tree.resize(N);
  ancestors.resize(N);
  for (int i = 0; i < N - 1; i++) {
    cin >> boss;
    tree[boss - 1].push_back(i + 1);
  }
  for (int i = 0; i < Q; i++) {
    cin >> x >> k;
    queries.push_back({x - 1, k});
  }
}
