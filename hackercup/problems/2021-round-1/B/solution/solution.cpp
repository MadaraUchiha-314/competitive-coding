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
ostream& operator<< (ostream& os, map<T, U> x) { os << "{" << "\n"; for (auto e: x) os << e << ":" << " " << x[e] << "\n"; os << "}" << "\n"; return os; }

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

/**
 * Problem Specific Stuff
 */
int N, M, A, B;
vector<vector<int>> mat(50, vector<int>(50, 1000));

void solve() {
  int sum = (A - M) / (N - 1);
  int total = M;
  for (int i = 0; i < N - 1; i++) {
    mat[i][0] = sum;
    total += sum;
  }
  if (total < A) {
    mat[0][0] += A - total;
  }

  sum = (B - M) / (N - 1);
  total = M;
 for (int i = 0; i < N - 1; i++) {
    mat[i][M - 1] = sum;
    total += sum;
  }
  if (total < B) {
    mat[0][M - 1] += B - total;
  }
  for (int i = 0; i < M; i ++) {
    mat[N - 1][i] = 1;
  }
  bool possible = true;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (mat[i][j] <= 0) possible = false;
    }
  }
  if (!possible) cout << "Impossible" << "\n";
  else {
    cout << "Possible" << "\n";
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        cout << mat[i][j] << " ";
      }
      cout << "\n";
    }
    // Asserting Everything is ok.
    int sum_a = 0, sum_b = 0;
    for (int i = 0; i < N; i++) {
      sum_a += mat[i][0];
      sum_b += mat[i][M -1];
    }
    for (int i = 1; i < M; i++) {
      sum_a += mat[N - 1][i];
      sum_b += mat[N - 1][M - i - 1];
    }
    if (sum_a != A || sum_b != B) {
      cout << A << " " << B << " " << sum_a << " " << sum_b << "\n";
      assert(false);
    }
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
    pcodejam(t + 1);
    solve();
  }
  return 0;
}

void input() {
  cin >> N >> M >> A >> B;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      mat[i][j] = 1000;
    }
  }
}
