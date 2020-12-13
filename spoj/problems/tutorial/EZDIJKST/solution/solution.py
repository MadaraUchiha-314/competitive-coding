import math
import heapq

def dijkstra(g, src, dest):
    answer = [math.inf for _ in range(len(g))]
    answer[src] = 0
    pq = [(0, src)]
    while len(pq) > 0:
        _, current = heapq.heappop(pq)
        for child, weight in g[current]:
            if answer[current] + weight < answer[child]:
                answer[child] = answer[current] + weight
                heapq.heappush(pq, (answer[current] + weight, child))
    return answer[dest]

t = int(input())
for _ in range(t):
    v, k = map(int, input().split())
    g = [[] for _ in range(v + 1)]
    for _ in range(k):
        src, dest, weight = map(int, input().split())
        g[src].append((dest, weight))
    a, b = map(int, input().split())
    answer = dijkstra(g, a, b)
    if answer == math.inf:
        print("NO")
    else:
        print(answer)
