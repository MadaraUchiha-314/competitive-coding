class DisjointSet:
    def __init__(self, n):
        self.parent = [i for i in range(n)]
        self.size = [1 for _ in range(n)]

    def root(self, a):
        if self.parent[a] == a:
            return a
        return self.root(self.parent[a])

    def find(self, a, b):
        return self.root(a) == self.root(b)

    def union(self, a, b):
        root_a = self.root(a)
        root_b = self.root(b)
        if self.size[root_a] < self.size[root_b]:
            self.parent[root_a] = self.parent[root_b]
            self.size[root_b] += self.size[root_a]
        else:
            self.parent[root_b] = self.parent[root_a]
            self.size[root_a] += self.size[root_b]

n, m = map(int, input().split())
edges = []
answer = 0
ds = DisjointSet(n)
for _ in range(m):
    src, dest, weight = map(int, input().split())
    edges.append((weight, src - 1, dest - 1))
edges.sort()
for weight, src, dest in edges:
    if ds.root(src) != ds.root(dest):
        ds.union(src, dest)
        answer += weight
print(answer)
