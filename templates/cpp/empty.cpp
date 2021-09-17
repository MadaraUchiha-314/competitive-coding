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
ostream& operator<< (ostream& os, map<T, U> x) { os << "{" << "\n"; for (auto [k, v]: x) os << k << ":" << " " << v << "\n"; os << "}" << "\n"; return os; }

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

namespace SegmentTree {
  
  #define middle(l, r) (l + r) / 2
  #define left_child(current) 1 + (current << 1)
  #define right_child(current) 2 + (current << 1)

  template <
    typename Item,
    typename Node,
    typename QueryTerm,
    typename QueryResult,
    typename UpdateTerm,
    Node create_node(Item&),
    Node combine_nodes(Node&, Node&),
    void update_node(Node&, Item&),
    QueryResult query_node(Node& node, QueryTerm& query_term),
    QueryResult combine_queries(QueryResult& q1, QueryResult& q2),
    UpdateTerm set_lazy(UpdateTerm& current, UpdateTerm& previous),
    void evaluate_lazy(Node& node, UpdateTerm& value),
    Node& Identity
  >
  class SegTree {
    public:
      int N;
      vector<Node> tree;
      vector<bool> is_updated;
      vector<UpdateTerm> lazy;
      
      Node create(vector<Item>& nodes, int left, int right, int current) {
        if (right == left) {
          tree[current] = create_node(nodes[left]);
        } else {
          int mid = middle(left, right);
          auto left_node = create(nodes, left, mid, left_child(current));
          auto right_node = create(nodes, mid + 1, right, right_child(current));
          tree[current] = combine_nodes(left_node, right_node);
        }
        return tree[current];
      }

      QueryResult query(int left, int right, int current, int current_left, int current_right, QueryTerm query_term) {
        if (current_left >= left && current_right <= right) {
          return query_node(tree[current], query_term);
        }
        if (current_left > right || current_right < left) {
          return query_node(Identity, query_term);
        }
        int mid = middle(current_left, current_right);
        auto left_query = query(left, right, left_child(current), current_left, mid, query_term);
        auto right_query = query(left, right, right_child(current), mid + 1, current_right, query_term);
        return combine_queries(left_query, right_query);
      }

      void update(int index, Node& value, int current, int current_left, int current_right) {
        int mid = middle(current_left, current_right);
        if (current_left == current_right) {
          tree[current] = update_node(tree[current], value);
        } else {
          if (index <= mid) {
            update(index, value, left_child(current),current_left, mid);
          } else {
            update(index, value, right_child(current), mid + 1, current_right);
          }
          tree[current] = combine_nodes(tree[left_child(current)], tree[right_child(current)]);
        }
      }

      void update(int left, int right, UpdateTerm value, int current, int current_left, int current_right) {
        if (!is_updated[current]) {
          evaluate_lazy(tree[current], lazy[current]);
          is_updated[current] = true;
          if (current_left != current_right) {
            is_updated[left_child(current)] = false;
            is_updated[right_child(current)] = false;
            lazy[left_child(current)] = set_lazy(lazy[left_child(current)], lazy[current]);
            lazy[right_child(current)] = set_lazy(lazy[right_child(current)], lazy[current]);
          }
        }
        if (current_left >= left && current_right <= right) {
          evaluate_lazy(tree[current], value);
          if (left != right) {
            is_updated[left_child(current)] = false;
            is_updated[right_child(current)] = false;
            lazy[left_child(current)] = set_lazy(lazy[left_child(current)], val);
            lazy[right_child(current)] = set_lazy(lazy[right_child(current)], val);
          }
        } else {
          int mid = middle(current_left, current_right);
          update(left, right, value, left_child(current), current_left, mid);
          update(left, right, value, left_child(current), mid + 1, current_right);
          tree[current] = combine_nodes(tree[left_child(current)], tree[right_child(current)]);
        }
      }

     public:
      SegTree(vector<Item>& nodes) {
        N = nodes.size();
        tree.resize(4 * N);
        is_updated.resize(4 * N);
        lazy.resize(4 * N);
        create(nodes, 0, N - 1, 0);
      }
      
      QueryResult query(int left, int right, QueryTerm query_term) {
        return query(left, right, 0, 0, N - 1, query_term);
      }

      void update(int index, Item& value) {
        update(index, value, 0, 0, N - 1);
      }

      void update(int left, int right, Item& value) {

      }
  };
}

using namespace SegmentTree;

/**
 * Problem Specific Stuff
 */


void solve() {
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
}
