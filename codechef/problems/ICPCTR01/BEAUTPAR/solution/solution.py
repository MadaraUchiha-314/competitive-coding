T = int(input())
for _ in range(T):
    N, K = map(int,input().split())
    A = list(map(int, input().split()))
    total = 0
    prefix_sum = []
    positive_sum_count = 0
    positive_sum_indices = []
    for i in range(N):
        total += A[i]
        prefix_sum.append(total)
        if total > 0:
            positive_sum_count += 1
    
    
        