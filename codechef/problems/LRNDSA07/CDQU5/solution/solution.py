import sys
sys.setrecursionlimit(10**8)

MOD = 10**9 + 9

def precompute(score, memo): 
    if score in memo:
        return memo[score]
    if score < 2:
        return 0
    if score == 2 or score == 3:
        memo[score] = 1
        return 1
    answer = precompute(score - 2, memo) + precompute(score - 3, memo)
    answer %= MOD
    memo[score] = answer
    return answer

if __name__ == "__main__":
    memo = {
        1: 0
    }
    precompute(10**6, memo)
    precompute(10**6 - 1, memo)
    T = int(input())
    for _ in range(T):
        N = int(input())
        print(memo[N])