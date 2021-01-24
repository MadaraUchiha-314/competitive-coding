max_n = 10**6 + 1

primes = []
composites = [True for i in range(max_n)]
answers = [0 for _ in range(max_n)]
def sieve():
    for i in range(2, max_n):
        if composites[i]:
            primes.append(i)
            j = i
            while j + i < max_n:
                composites[j + i] = False
                j += i

def precompute():
    answer = 0
    primes_index = 0
    for i in range(1, max_n):
        if primes_index < len(primes) and primes[primes_index] == i:
            if primes_index > 1 and (primes[primes_index] - primes[primes_index - 1] == 2):
                answer += 1
            primes_index += 1
        answers[i] = answer   

if __name__ == "__main__":
    sieve()
    precompute()
    T = int(input())
    for _ in range(T):
        N = int(input())
        print(answers[N])