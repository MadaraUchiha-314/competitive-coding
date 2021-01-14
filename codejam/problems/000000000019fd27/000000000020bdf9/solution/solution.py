t = int(input())
for tc in range(t):
    n = int(input())
    activities = []
    for i in range(n):
        start, end = map(int, input().split())
        activities.append((start, end, i))
    activities.sort()
    people = ["C", "J"]
    tasks = []
    answer = []
    for i in range(len(people)):
        tasks.append(activities[i])
        answer.append((activities[i][2], people[i]))
    for i in range(len(people), n):
        start, end, index = activities[i]
        for j in range(len(people)):
            if start >= tasks[j][1]:
                tasks[j] = activities[i]
                answer.append((index, people[j]))
                break;
    answer.sort()
    if len(answer) != n:
        print("Case #{0}: {1}".format(tc + 1, "IMPOSSIBLE"))
    else:
        print("Case #{0}: {1}".format(tc + 1, "".join([ans[1] for ans in answer])))
