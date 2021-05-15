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
 * Segment Tree
 */
namespace SegmentTree {
  
  #define middle(l, r) (l + r) / 2
  #define left_child(current) 1 + (current << 1)
  #define right_child(current) 2 + (current << 1)

  template <typename Item, typename Node, Node create_node(Item), Node combine_nodes(Node, Node), Node Identity>
  class SegTree {
    private:
      int N;
      vector<Node> tree;
      
      Node create(vector<Item>& nodes, int left, int right, int current) {
        if (right == left) {
          tree[current] = create_node(nodes[left]);
        } else {
          int mid = middle(left, right);
          tree[current] = combine_nodes(
            create(nodes, left, mid, left_child(current)),
            create(nodes, mid + 1, right, right_child(current))
          );
        }
        return tree[current];
      }

      Node query(int left, int right, int current, int current_left, int current_right) {
        if (current_left >= left && current_right <= right) {
          return tree[current];
        }
        if (current_left > right || current_right < left) {
          return Identity;
        }
        int mid = middle(current_left, current_right);
        return combine_nodes(
          query(left, right, left_child(current), current_left, mid),
          query(left, right, right_child(current), mid + 1, current_right)
        );
      }

     public:
      SegTree(vector<Item>& nodes) {
        N = nodes.size();
        tree.resize(4 * N);
        create(nodes, 0, N - 1, 0);
      }
      
      Node query(int l, int r) {
        return query(l, r, 0, 0, N - 1);
      }
  };
}

using namespace SegmentTree;

/**
 * Problem Specific Stuff
 */
int N, Q;
vector<long long> nodes;
vector<pair<int, int>> queries;
long long create(long long e) { return e; }
long long combine(long long a, long long b) { return a + b; }

void solve() {
  SegTree<long long, long long, create, combine, (long long) 0> s(nodes);
  for (auto q: queries) {
    cout << s.query(q.first - 1, q.second - 1) << NEW_LINE;
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
  cin >> N >> Q;
  nodes.resize(N);
  for (int i = 0; i < N; i++) {
    cin >> nodes[i];
  }
  int l, r;
  for (int i = 0; i < Q; i++) {
    cin >> l >> r;
    queries.push_back({l, r});
  }
}
