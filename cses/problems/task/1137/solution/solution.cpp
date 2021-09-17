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


namespace SegmentTree {
  
  #define middle(l, r) (l + r) / 2
  #define left_child(current) 1 + (current << 1)
  #define right_child(current) 2 + (current << 1)

  template <
    typename Item,
    typename Node,
    typename QueryTerm,
    typename QueryResult,
    Node create_node(Item&),
    Node combine_nodes(Node&, Node&),
    void update_node(Node&, Item&),
    QueryResult query_node(Node& node, QueryTerm& query_term),
    QueryResult combine_queries(QueryResult& q1, QueryResult& q2),
    Node& Identity
  >
  class SegTree {
    public:
      int N;
      vector<Node> tree;
      
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

      void update(int index, Node& value, int current, int left, int right) {
        int mid = middle(left, right);
        if (left == right) {
          update_node(tree[current], value);
        } else {
          if (index <= mid) {
            update(index, value, left_child(current),left, mid);
          } else {
            update(index, value, right_child(current), mid + 1, right);
          }
          tree[current] = combine_nodes(tree[left_child(current)], tree[right_child(current)]);
        }
      }

     public:
      SegTree(vector<Item>& nodes) {
        N = nodes.size();
        tree.resize(4 * N);
        create(nodes, 0, N - 1, 0);
      }
      
      QueryResult query(int left, int right, QueryTerm query_term) {
        return query(left, right, 0, 0, N - 1, query_term);
      }

      void update(int index, Item& value) {
        update(index, value, 0, 0, N - 1);
      }
  };
}

using namespace SegmentTree;

void input();
void solve();

/**
 * Problem Specific Stuff
 */
int N, Q;
vector<vector<int>> tree;
vector<long long> values;
vector<pair<int, int>> indices_for_node;

struct Query {
  int type, s;
  long long  x;
};

vector<Query> queries;

int euler_tour(int current, int parent, int index) {
  int total = index;
  for (auto child: tree[current]) {
    if (child != parent) {
      total = euler_tour(child, current, total + 1);
    }
  }
  indices_for_node[current] = { index, total };
  return total;
}

long long create_node(long long& a) { return a;}
long long combine_nodes(long long& a, long long& b) { return a + b; }
void update_node(long long& a, long long& val) { a = val; }
long long query_node(long long& a, long long& b) { return a; }
long long combine_queries(long long& a, long long& b) { return a + b; }
long long identity = 0;

void solve() {
  euler_tour(0, -1, 0);
  vector<long long> new_values(N, 0);
  for (int i = 0; i < N; i++) {
    new_values[indices_for_node[i].first] = values[i];
  }
  SegTree<long long, long long, long long, long long, create_node, combine_nodes, update_node, query_node, combine_queries, identity> st(new_values);
  for (auto query: queries) {
    if (query.type == 1) {
      st.update(indices_for_node[query.s - 1].first, query.x);
    } else {
      auto [left, right] = indices_for_node[query.s - 1];
      cout << st.query(left, right, 0) << "\n";
    }
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
  tree.resize(N);
  values.resize(N);
  indices_for_node.resize(N);
  queries.resize(Q);
  for (int i = 0; i < N; i++) {
    cin >> values[i];
  }
  int from, to;
  for (int i = 0; i < N - 1; i++) {
    cin >> from >> to;
    from--; to--;
    tree[from].push_back(to);
    tree[to].push_back(from);
  }
  for (int i = 0; i < Q; i++) {
    cin >> queries[i].type;
    if (queries[i].type == 1) {
      cin >> queries[i].s >> queries[i].x;
    } else {
      cin >> queries[i].s;
    }
  }
}
