import string

alphabets = list(string.ascii_lowercase) + list(string.ascii_uppercase)

def count_hash(s, l, index, memo):
    if (s, l, index) in memo:
        return memo[(s, l, index)]
    if s == 0 and l == 0:
        return 1
    answer = 0
    for i in range(index + 1, len(alphabets)):
        if s - i - 1 >= 0 and l - 1 >= 0:
            answer += count_hash(s - i - 1, l - 1, i, memo)
    memo[(s, l, index)] = answer
    return answer

if __name__ == "__main__":
    T = int(input())
    memo = {}
    for i in range(T):
        L, S = map(int, input().split())
        answer = 0
        if L > len(alphabets) or S > sum([i + 1 for i in range(len(alphabets))]):
            answer = 0
        else:
            answer = count_hash(S, L, -1, memo)
        print("Case {0}: {1}".format(i + 1, answer))
