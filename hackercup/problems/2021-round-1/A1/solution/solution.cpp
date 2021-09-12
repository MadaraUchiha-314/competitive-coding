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
int N;
string s;

void solve() {
  int answer = 0;
  char current = 'O'; // 0 denotes FO and 1 denotes FX
  for (int i = 0; i < N; i++) {
    if (s[i] == 'O') {
      current = 'O';
      break;
    }
    if (s[i] == 'X') {
      current = 'X';
      break;
    }
  }
  for (int i = 0; i < N; i++) {
    if (s[i] != 'F' && s[i] != current) {
      current = s[i];
      answer += 1;
    }
  }
  cout << answer << "\n";
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
  cin >> s;
}
