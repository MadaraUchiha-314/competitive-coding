import string

def dfs(g, current, visited):
    if visited[current]:
        return set()
    visited[current] = True
    reachable = set([current])
    for child in g[current]:
        reachable |= dfs(g, child, visited)
    return reachable
if __name__ == "__main__":
    P = int(input())
    for _ in range(P):
        S = list(input())
        T = list(input()) 
        M = int(input())
        g = { c: [] for c in list(string.ascii_lowercase) }
        gc = { c: [] for c in list(string.ascii_lowercase) }
        for _ in range(M):
            mappings = input()
            src = mappings[0]
            dest = mappings[-1]
            g[src].append(dest)
        if len(S) != len(T):
            print("NO")
            continue
        for c in list(string.ascii_lowercase):
            gc[c] = list(dfs(g, c, { c: False for c in list(string.ascii_lowercase) }))
        can_transform = True
        for s, t in zip(S, T):
            if s != t and (t not in gc[s]):
                can_transform = False
        if can_transform:
            print("YES")
        else:
            print("NO")
        

