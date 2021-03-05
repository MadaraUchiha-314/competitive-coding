class Edge:
    def __init__(self, src, dest, weight = 0) -> None:
        self.src = src
        self.dest = dest
        self.weight = weight

class Tree:
    def __init__(self, n, root = 0) -> None:
        self.nodes = n
        self.tree = [[] for _ in range(n)]
        self.root = root
        self.ancestors = [[] for _ in range(n)]
        self.in_time = [-1 for _ in range(n)]
        self.out_time = [-1 for _ in range(n)]
        self.distance_from_root = [0 for _ in range(n)]
    
    def add_directed_edge(self, e: Edge):
        self.tree[e.src].append(e)
    
    def add_undirected_edge(self, e: Edge):
        self.tree[e.src].append(e)
        self.tree[e.dest].append(Edge(e.dest, e.src, e.weight))
    
    def __precompute_ancestors(self, current, visited, stack, current_distance, current_time):
        visited[current] = True
        self.distance_from_root[current] = current_distance
        i = 1
        while i - 1 < len(stack):
            self.ancestors[current].append(stack[i - 1])
            i *= 2
        
        self.in_time[current] = current_time
        
        latest_end_time = current_time
        for edge in self.tree[current]:
            if not visited[edge.dest]:
                latest_end_time = self.__precompute_ancestors(edge.dest, visited, stack + [current], current_distance + edge.weight, latest_end_time + 1)

        self.out_time[current] = latest_end_time + 1
        
        return latest_end_time + 1

    def precompute_ancestors(self):
        visited = [False for _ in range(self.nodes)]
        self.__precompute_ancestors(self.root, visited, [], 0, 0)

    def __is_direct_ancestor(self, a, b):
        if self.in_time[a] <= self.in_time[b] and self.in_time[b] <= self.out_time[a]:
            return True
    
    def lca(self, a, b):
        if self.__is_direct_ancestor(a, b):
            return a
        elif self.__is_direct_ancestor(b, a):
            return b
        else:
            current = a
            i = len(self.ancestors[current]) - 1
            while i >= 0:
                if not self.__is_direct_ancestor(self.ancestors[current][i], b):
                    current = self.ancestors[current][i]
                    i = len(self.ancestors[current]) - 1
                else:
                    i -= 1
            return self.ancestors[current][0]

if __name__ == "__main__":
    T = int(input())
    for _ in range(T):
        N, Q, R = map(int, input().split())
        tree = Tree(N, R - 1)
        for _ in range(N - 1):
            src, dest, weight = map(int, input().split())
            tree.add_undirected_edge(Edge(src - 1, dest - 1, weight))
        tree.precompute_ancestors()
        for _ in range(Q):
            U, V = map(int, input().split())
            lca = tree.lca(U - 1, V - 1)
            print(tree.distance_from_root[U - 1] + tree.distance_from_root[V - 1] - tree.distance_from_root[lca] - tree.distance_from_root[lca])