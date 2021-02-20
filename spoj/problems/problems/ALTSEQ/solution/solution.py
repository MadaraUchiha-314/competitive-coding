def is_different_sign(a, b):
    if a * b > 0:
        return False
    return True

def is_increasing(a, b):
    return abs(a) > abs(b)

def longest_alternate_sequence(A):
    N = len(A)
    dp = [1 for _ in range(N)] # dp[i] stores the longest alternating sequence ending at i
    for i in range(N):
        for j in range(i):
            if is_different_sign(A[j], A[i]) and is_increasing(A[i], A[j]):
                dp[i] = max(dp[i], 1 + dp[j])
    return max(dp)

if __name__ == "__main__":
    N = int(input())
    A = list(map(int, input().split()))
    print(longest_alternate_sequence(A))
