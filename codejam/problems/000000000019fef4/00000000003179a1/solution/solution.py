# Problem Name/URL: 

import bisect
import heapq

TOTAL = 10 ** 4

if __name__ == "__main__":
    T = int(input())
    for t in range(T):
        U = int(input())
        digit_bounds = {}
        all_chars = set()
        for i in range(TOTAL):
            M, R = input().split()
            M = list(map(int, list(M)))
            all_chars |= set(list(R))
            if len(R) == len(M):
                if R[0] in digit_bounds:
                    digit_bounds[R[0]] = min(digit_bounds[R[0]], M[0])
                else:
                    digit_bounds[R[0]] = M[0]
        mapping = []
        for key in digit_bounds:
            mapping.append((digit_bounds[key], key))
        mapping.sort()
        print("Case #{0}: ".format(t + 1), end="")
        for char in all_chars:
            if char not in digit_bounds:
                print(char, end="")
                break
        for value, key in mapping:
            print(key, end="")
        print()




