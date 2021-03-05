T = int(input())
for _ in range(T):
    N = list(input())
    answer = 10**9
    for i in range(len(N)):
        answer = min(answer, int(''.join(N[:i] + N[i + 1:])))
    print(answer)