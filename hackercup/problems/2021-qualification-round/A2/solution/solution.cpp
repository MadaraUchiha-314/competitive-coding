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
string S;
int K;
string r;
vector<vector<int>> dist(26, vector<int>(26));

const int INF = 1e5;

void solve() {
    for (int k = 0; k < 26; k++) {
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    int min_cost = 1e9;
    bool possible = false;
    for (int i = 0; i < 26; i++) {
        int cost = 0;
        bool convert_to_ith = true;
        for (char c: S) {
            if (c - 'A' == i) continue;
            if (dist[c - 'A'][i] != INF) {
                cost += dist[c - 'A'][i];
            } else {
                convert_to_ith = false;
                break;
            } 
        }
        if (convert_to_ith ){
            min_cost = min(min_cost, cost);
            possible = true;
        }
    }
    cout << (possible ? min_cost : -1) << "\n";
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
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            if (i == j) {
                dist[i][j] = 0;
            }  
            else {
                dist[i][j] = INF;
            }
        }
    }
    cin >> S;
    cin >> K;
    for (int i = 0; i < K; i++) {
        cin >> r;
        dist[r[0] - 'A'][r[1] - 'A'] = 1;
    }
}
