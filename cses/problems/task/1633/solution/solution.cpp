/*
 * Problem Name/URL: 
 */
#include <bits/stdc++.h>
using namespace std;

void input();

/**
 * Problem Specific Stuff
 */
int N;
const int mod = (int) 1e9 + 7;
int dp[1000010];

void solve() {
  for (int i = 1; i < 7; i++) dp[i] = 1;
  for (int i = 0; i < N; i++) {
    for (int j = 1; j < 7; j++) {
      dp[i + j] += dp[i];
      dp[i + j] %= mod;
    }
  }
  cout << dp[N] << "\n";
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
  cin >> N;
}
