T = int(input())
for _ in range(T):
    lower = False
    upper = False
    digit = False
    special = False
    sp = ['@', '#', '%', '&', '?']
    length = False
    password = list(input())
    for i in range(len(password)):
        c = password[i]
        if c.isupper() and i != 0 and i != len(password) - 1:
            upper = True
        if c.islower():
            lower = True
        if c.isdigit() and i != 0 and i != len(password) - 1:
            digit = True
        if c in sp and i != 0 and i != len(password) - 1:
            special = True
        if len(password) >= 10:
            length = True
    if lower and upper and digit and special and length:
        print("YES")
    else:
        print("NO")