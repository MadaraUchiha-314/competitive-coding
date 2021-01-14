t = int(input())
for i in range(t):
    s = list(map(int, list(input())))
    stack = []
    op = 0
    for c in s:
        if c == op:
            stack.append(str(c))
        elif c > op:
            while op != c:
                stack.append('(')
                op += 1
            stack.append(str(c))
        else:
            while op != c:
                stack.append(')')
                op -= 1
            stack.append(str(c))
    while op != 0:
        stack.append(')')
        op -=  1
    print('Case #{0}: {1}'.format(str(i + 1), ''.join(stack)))
