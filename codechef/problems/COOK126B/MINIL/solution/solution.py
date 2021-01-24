if __name__ == "__main__":
    T = int(input())
    for _ in range(T):
        N, M = map(int, input().split())
        matrix = []
        dot_star = [0 for _ in range(N)]
        star_dot = [0 for _ in range(N)]
        for i in range(N):
            row = list(input())
            cost_star_dot = 0
            cost_dot_star = 0
            for j in range(M):
                if j % 2 == 0:
                    if row[j] == '.':
                        cost_star_dot += 1
                    else:
                        cost_dot_star += 1
                else:
                    if row[j] == '.':
                        cost_dot_star += 1
                    else:
                        cost_star_dot += 1
            dot_star.append(cost_dot_star)
            star_dot.append(cost_star_dot)
        print(min(sum(dot_star), sum(star_dot)))
                


