T = int(input())
for _ in range(T):
    L, R = map(int, input().split())
    print(1 + R + R - (L + L) )