if __name__ == "__main__":
    T = int(input())
    for _ in range(T):
        N, M = map(int, input().split())
        matrix = []
        dot_star = [0 for _ in range(N)]
        star_dot = [0 for _ in range(N)]
        for i in range(N):
            row = list(input())
            matrix.append(row)
        answer_dot = 0
        answer_star = 0
        for i in range(N):
            for j in range(M):
                if i % 2 == 0:
                    if j % 2 == 0:
                        if matrix[i][j] == '*':
                            answer_dot += 1
                    else:
                        if matrix[i][j] == '.':
                            answer_dot += 1
                else:
                    if j % 2 == 1:
                        if matrix[i][j] == '*':
                            answer_dot += 1
                    else:
                        if matrix[i][j] == '.':
                            answer_dot += 1
                
                if i % 2 == 0:
                    if j % 2 == 0:
                        if matrix[i][j] == '.':
                            answer_star += 1
                    else:
                        if matrix[i][j] == '*':
                            answer_star += 1
                else:
                    if j % 2 == 1:
                        if matrix[i][j] == '.':
                            answer_star += 1
                    else:
                        if matrix[i][j] == '*':
                            answer_star += 1
        print(min(answer_dot, answer_star))

