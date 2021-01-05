#include <cstdio>
#include <algorithm>
using namespace std;
int main() {
  int T;
  int N, K, D;
  int A[100];
  scanf("%d", &T);
  while(T--) {
    int sum = 0;
    scanf("%d %d %d", &N, &K, &D);
    for (int i = 0; i < N; i++) {
      scanf("%d", A + i);
      sum += A[i];
    }
    printf("%d\n", min(D, sum / K));
  }
}
