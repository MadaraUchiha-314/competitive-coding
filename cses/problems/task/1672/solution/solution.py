import math

def floyd_warshall(N, dist):
    for i in range(N):
        dist[i][i] = 0
    for k in range(N):
        for i in range(N):
            for j in range(N):
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

if __name__ == "__main__":
    N, M, Q = map(int, input().split())
    dist = [[math.inf for _ in range(N)] for _ in range(N)]
    for _ in range(M):
        src, dest, weight = map(int, input().split())
        src -= 1
        dest -= 1
        dist[src][dest] = min(weight, dist[src][dest])
        dist[dest][src] = min(weight, dist[dest][src])
    floyd_warshall(N, dist)
    for _ in range(Q):
        src, dest = map(int, input().split())
        if dist[src - 1][dest - 1] == math.inf:
            print("-1")
        else:
            print(dist[src][dest])
