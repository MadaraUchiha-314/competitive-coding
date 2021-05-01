/*
 * Problem Name/URL: https://codingcompetitions.withgoogle.com/codejam/round/0000000000007765/000000000003e068
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <utility>
#include <functional>
#include <limits>
#include <map>
#include <set>
#include <iterator>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

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
ostream& operator<< (ostream& os, pair<T, U> x) { os << ROB_O << x.first << SPACE << x.second << ROB_C; return os; }

template <typename T>
ostream& operator<< (ostream& os, vector<T> x) { os << SQB_O; for (auto e: x) os << e << COMMA << SPACE; os << SQB_C << NEW_LINE; return os; }

template <typename T, typename U>
ostream& operator<< (ostream& os, map<T, U> x) { os << CYB_O << NEW_LINE; for (auto e: x) os << e << COLON << SPACE << x[e] << NEW_LINE; os << CYB_C << NEW_LINE; return os; }

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
int N, D;
int flavor;
vector<int> preferences;
vector<int> frequencies(200);
vector<bool> availability(200);

void solve() {
  for (int i = 0; i < N; i++) {
    cin >> D;
    assert(D != -1);
    for (int j = 0; j < D; j++) {
      cin >> flavor;
      preferences.push_back(flavor);
      frequencies[flavor] += 1;
    }
    int most_preferred_count = (int) 1e9, most_preferred_candy = -1;
    for (int j = 0; j < D; j++) {
      int preference = preferences[j];
      if (availability[preference]) {
        if (frequencies[preference] < most_preferred_count) {
          most_preferred_count = frequencies[preference];
          most_preferred_candy = preference;
        }
      }
    }
    if (most_preferred_candy != -1) {
      frequencies[most_preferred_candy] -= 1;
      availability[most_preferred_candy] = false;
      cout << most_preferred_candy << "\n";
      cout.flush();
    } else {
      cout << "-1" << "\n";
      cout.flush();
    }
    preferences.clear();
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
  cin >> N;
  for (int i = 0; i < N; i++) {
    availability[i] = true;
    frequencies[i] = 0;
  }
}
