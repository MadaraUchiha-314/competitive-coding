#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

bool is_increasing(int a, int b) {
    return abs(a) > abs(b);
}

bool is_alternate(long long a, long long b) {
    return a * b < 0;
}

int main() {
    int N;
    int A[5000], dp[5000];
    scanf("%d", &N);
    for (int i = 0; i <  N; i++) {
        scanf("%d", A + i);
        dp[i] = 1;
    }
    for (int i = 0; i <  N; i++) {
        for (int j = 0; j < i; j++) {
            if (is_increasing(A[i], A[j]) && is_alternate(A[i], A[j])) {
                dp[i] = max(dp[i], 1 + dp[j]);
            }
        }
    }
    printf("%d\n", *max_element(dp, dp + N));
}