T = int(input())
for _ in range(T):
    N = int(input())
    spam = {}
    non_spam = {}
    for _ in range(N):
        word, is_spam = input().split()
        if is_spam == "0":
            if word in non_spam:
                non_spam[word] += 1
            else:
                non_spam[word] = 1
        else:
            if word in spam:
                spam[word] += 1
            else:
                spam[word] = 1
    answer = 0
    for word in spam:
        if word in non_spam:
            if spam[word] >= non_spam[word]:
                answer += spam[word]
        else:
            answer += spam[word]
    for word in non_spam:
        if word in spam:
            if non_spam[word] > spam[word]:
                answer += non_spam[word]
        else:
            answer += non_spam[word]
    print(answer)
