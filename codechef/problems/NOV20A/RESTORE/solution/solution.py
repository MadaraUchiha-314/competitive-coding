if __name__ == "__main__":
    T = int(input())
    for _ in range(T):
        N = int(input())
        B = list(map(int, input().split()))
        A = [0 for _ in range(N)]
        current = 10**6
        for i in range(N):
            if A[i] == 0:
                A[i] = current
                if B[i] - 1 != i:
                    if A[B[i] - 1] == 0:
                        A[B[i] - 1] = 2 * current
                    else:
                        A[i] = A[B[i] - 1]
                current += 1
        print(" ".join(map(str, A)))
