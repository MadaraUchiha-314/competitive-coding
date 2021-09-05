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

namespace SegmentTree {
  
  #define middle(l, r) (l + r) / 2
  #define left_child(current) 1 + (current << 1)
  #define right_child(current) 2 + (current << 1)

  template <
    typename Item,
    typename Node,
    typename QueryTerm,
    typename QueryResult,
    Node create_node(Item),
    Node combine_nodes(Node&, Node&),
    void update_node(Node&, Item),
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

      void update(int index, int value, int current, int left, int right) {
        int mid = middle(left, right);
        if (left == right) {
          tree[current] = update_node(tree[current], value);
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

      void update(int index, int value) {
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

vector<long long> create_node(long long value) {
  vector<long long> node(1, value);
  return node;
}

vector<long long> combine_nodes(vector<long long>& left, vector<long long>& right) {
  int i = 0, j = 0;
  vector<long long> combined;
  while(i < left.size() && j < right.size()) {
    if (left[i] < right[j]) {
      combined.push_back(left[i]); i++;
    } else {
      combined.push_back(right[j]); j++;
    }
  }
  while(i < left.size()) {
    combined.push_back(left[i]); i++;
  }
  while(j < right.size()) {
    combined.push_back(right[j]); j++;
  }
  return combined;
}

void update_node(vector<long long>& current, long long value) {
  current[0] = value;
}

long long query_node(vector<long long>& node, long long& query) {
  return (long long) (node.end() - upper_bound(node.begin(), node.end(), query));
}

long long combine_queries(long long& q1, long long& q2) {
  return q1 + q2;
}

vector<long long> identity;

int N, Q;
vector<long long> arr;
vector<pair<pair<int, int>, int>> queries;


void solve() {
  SegTree<long long, vector<long long>, long long, long long, create_node, combine_nodes, update_node, query_node, combine_queries, identity> s(arr);
  for (auto query: queries) {
    auto range = query.first;
    auto value = query.second;
    cout << s.query(range.first - 1, range.second - 1, value) << "\n";
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
  cin >> N;
  arr.resize(N);
  for (int i = 0; i < N; i++) {
    cin >> arr[i];
  }
  cin >> Q;
  queries.resize(Q);
  for (int i = 0; i < Q; i++) {
    cin >> queries[i].first.first >> queries[i].first.second >> queries[i].second;
  }
}
