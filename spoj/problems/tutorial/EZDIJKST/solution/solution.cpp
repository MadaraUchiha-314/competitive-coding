/*
 * Problem Name/URL: https://www.spoj.com/problems/EZDIJKST/
 */
#include <bits/stdc++.h>
using namespace std;

void input();

/**
 * Problem Specific Stuff
 */
const int INF = numeric_limits<int>::max();
int N, M;
int A, B;
vector<vector<pair<int, int>>> g;
vector<int> memo;
vector<int> cost_to_reach;

int shortest_path(int src, int dest, int current_cost) {
  cost_to_reach[src] = current_cost;
  if (src == dest) {
    return 0;
  }
  if ((memo[src] != -1) && (memo[src] < current_cost)) {
    return memo[src];
  }
  int min_cost = INF;
  for (auto next: g[src]) {
    int weight = next.first;
    int child = next.second;
    if ((current_cost + weight) < cost_to_reach[child]) {
      int cost_from_child = shortest_path(child, dest, current_cost + weight);
      if (cost_from_child != INF) {
        min_cost = min(min_cost, weight + cost_from_child);
      }
    }
  }
  memo[src] = min_cost;
  return min_cost;
}

void solve() {
  int answer = shortest_path(A - 1, B - 1, 0);
  if (answer != INF) {
    cout << answer << "\n";
  } else {
    cout << "NO" << "\n";
  }
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
  g.clear();
  memo.clear();
  cost_to_reach.clear();
  cin >> N >> M;
  g.resize(N);
  memo.resize(N, -1);
  cost_to_reach.resize(N, INF);
  int src, dest, weight;
  for (int i = 0; i < M; i++) {
    cin >> src >> dest >> weight;
    g[src - 1].push_back({ weight, dest - 1});
  }
  cin >> A >> B;
}
