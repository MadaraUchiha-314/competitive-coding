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

const int MOD = (int) 1e9 + 7;

/**
 * Problem Specific Stuff
 */
const int MAX_LEN = (int) 8e5;
int N;
string s;
vector<int> flips;

void solve() {
  string last_char_before(N, 'F');
  vector<int> pos_last_non_f(N, 0);
  char current_last_char = s[0];
  for (int i = 1; i < N; i++) {
    last_char_before[i] = current_last_char;
    if (s[i - 1] != 'F') {
      pos_last_non_f[i] = i - 1;
    } else {
      pos_last_non_f[i] = pos_last_non_f[i - 1];
    }
    if (s[i] != 'F') {
      current_last_char = s[i];
    }
  }
  vector<int> answer(N, 0);
  int total = 0;
  for (int i = 1; i < N; i++) {
    if (s[i] != 'F' && last_char_before[i] != 'F' && last_char_before[i] != s[i]) {
      answer[i] = (answer[i - 1] + pos_last_non_f[i] + 1) % MOD;
    } else {
      answer[i] = answer[i - 1];
    }
    total += answer[i];
    total %= MOD;
  }
  cout << total << "\n";
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
  flips.clear();
  flips.resize(N, 0);
}
