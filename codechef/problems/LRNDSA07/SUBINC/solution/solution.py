if __name__ == "__main__":
    T = int(input())
    for  _ in range(T):
        N = int(input())
        A = list(map(int, input().split()))
        current = A[0]
        answer = 0
        current_length = 1
        for i in range(1, N):
            if A[i] >= current:
                current_length += 1
            else:
                answer += (current_length * (current_length + 1)) / 2
                current_length = 1
            current = A[i]
        answer += (current_length * (current_length + 1)) / 2
        print(int(answer))