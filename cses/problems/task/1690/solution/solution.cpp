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
int N, M;
int src, dest;
int MOD = (int) 1e9 + 7;
vector<vector<int>> graph;
 
int dp[20][1 << 20];

int dfs(int current, int bitmask) {
	if (dp[current][bitmask] != -1) {
		return dp[current][bitmask];
	}
	if (current == N - 1) {
		if (bitmask == ((1 << N) - 1)) {
			return 1;
		}
		return 0;
	}
	int answer = 0;
	for (auto child: graph[current]) {
		if (((1 << child) & bitmask) == 0) {
			answer += dfs(child, bitmask | (1 << child));
			answer %= MOD;
		}
	}
	dp[current][bitmask] = answer;
	return answer;
}
 
void solve() {
	cout << dfs(0, 1) << NEW_LINE;
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
	graph.resize(N);
	for (int i = 0; i < 20; i++) {
		fill(dp[i], dp[i + 1], -1);
	}
	for (int i = 0 ; i < M; i++) {
		cin >> src >> dest;
		graph[src - 1].push_back(dest - 1);
	}
}
