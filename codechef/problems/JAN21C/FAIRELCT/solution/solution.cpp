#include <cstdio>
#include <algorithm>
using namespace std;
int main() {
  int T;
  int N, M;
  int A[1000], B[1000];
  scanf("%d", &T);
  while(T--) {
    int sum_a = 0, sum_b = 0;
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
      scanf("%d", A + i);
      sum_a += A[i];
    }
    for (int i = 0; i < M; i++) {
      scanf("%d", B + i);
      sum_b += B[i];
    }
    sort(A, A + N);
    sort(B, B + M);
    int i = 0, j = M - 1;
    int swaps = 0;
    while((sum_a <= sum_b) && (i < N) && (j >= 0)) {
      if (A[i] < B[j]) {
        sum_a += B[j] - A[i];
        sum_b += A[i] - B[j];
        swaps++;
      }
      i++; j--;
    }
    if (sum_a > sum_b) {
      printf("%d\n", swaps);
    } else {
      printf("-1\n");
    }
  }
}
