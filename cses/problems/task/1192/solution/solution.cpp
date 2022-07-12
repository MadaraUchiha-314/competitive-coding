/*
 * Problem Name/URL: 
 */
#include <bits/stdc++.h>
using namespace std;

void input();

/**
 * Problem Specific Stuff
 */
int N, M;
char g[1000][1000];
bool visited[1000][1000];

bool isValid(int x, int y) {
  return x >= 0 && x < N && y >= 0 && y < M && g[x][y] == '.';
}

void dfs(int x, int y) {
  visited[x][y] = true;
  if (isValid(x + 1, y) && !visited[x + 1][y])
    dfs(x + 1, y);
  if (isValid(x - 1, y) && !visited[x - 1][y])
    dfs(x - 1, y);
  if (isValid(x, y + 1) && !visited[x][y + 1])
    dfs(x, y + 1);
  if (isValid(x, y - 1) && !visited[x][y - 1])
    dfs(x, y - 1);
}

void solve() {
  int count = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (g[i][j] == '.' && !visited[i][j]) {
        count += 1;
        dfs(i, j);
      }
    }
  }
  cout << count << "\n";
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
  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++)
      cin >> g[i][j];
}
