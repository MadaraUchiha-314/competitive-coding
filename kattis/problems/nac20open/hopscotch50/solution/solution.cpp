/*
 * Problem Name/URL: 
 */
#include <bits/stdc++.h>
using namespace std;

void input();

/**
 * Problem Specific Stuff
 */
const int INF = numeric_limits<int>::max();
const int MAX_N = 51;
int N, K;
int mat[MAX_N][MAX_N];
vector<pair<int, int>> lookup[MAX_N * MAX_N];
int memo[MAX_N][MAX_N];


int cost(int i, int j) {
  int current = mat[i][j];
  if (current == K) {
    return 0;
  }
  if (memo[i][j] != 0) {
    return memo[i][j];
  }
  int next = current + 1;
  if (lookup[next].size() == 0) {
    memo[i][j] = INF;
    return memo[i][j];
  }
  int min_cost = INF;
  for (auto [x, y]: lookup[next]) {
    int cost_to_next = cost(x, y);
    if (cost_to_next == INF) continue;
    min_cost = min(min_cost, abs(i - x) + abs(j - y) + cost_to_next);
  }
  memo[i][j] = min_cost;
  return memo[i][j];
}


void solve() {
  int min_cost = INF;
  for (auto [x, y]: lookup[1]) {
    min_cost = min(min_cost, cost(x, y));
  }
  if (min_cost == INF) {
    cout << -1 << "\n";
  } else {
    cout << min_cost << "\n";
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
  cin >> N >> K;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> mat[i][j];
      lookup[mat[i][j]].push_back({i, j});
    }
  }
}
