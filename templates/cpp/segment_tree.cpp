
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