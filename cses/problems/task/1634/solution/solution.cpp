/*
 * Problem Name/URL: 
 */
#include <bits/stdc++.h>
using namespace std;

void input();

/**
 * Problem Specific Stuff
 */
int N, X;
int C[100];
int memo[1000001];
const int INF = numeric_limits<int>::max();;

int ways(int x) {
  if (x < 1) return INF;
  if (memo[x]  != 0) return memo[x];
  int answer = INF;
  for (int i = 0; i < N; i++) {
    int next_answer = ways(x - C[i]);
    if (next_answer != INF) {
      answer = min(answer, 1 + ways(x - C[i]));
    }
  }
  memo[x] = answer;
  return answer;
}

void solve() {
  for (int i = 0; i < N; i++) memo[C[i]] = 1;
  int answer = ways(X);
  if (answer == INF) cout << "-1" << "\n";
  else cout << answer << "\n";
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
  cin >> N >> X;
  for (int i = 0; i < N; i++) cin >> C[i];
}
