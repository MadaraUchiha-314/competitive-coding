#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define DEBUG 0

#if DEBUG
  #define debug printf
#else
  #define debug(...) 1 == 1
#endif

int main() {
  int T, N, X, Y;
  int A[1000];
  vector<int> sums(1005);
  scanf("%d", &T);
  while(T--) {
    scanf("%d %d %d", &N, &X, &Y);
    for (int i = 0; i < N; i++) {
      scanf("%d", A + i);
      if (i > 0) {
        sums[i] = sums[i - 1] + A[i];
      } else {
        sums[i] = A[i];
      }
    }
    bool zero_swap = false, one_swap = false;
    int total = 0;
    for (int i = 0; i <  N; i++) {
      total += A[i];
      if (total >= X && total <= Y) {
        zero_swap = true;
        break;
      }
      for (int j = i + 1; j < N; j++) {
        // We swap A[i] and A[j]
        int delta = A[j] - A[i];
        // Now all the elements from i to j have delta added to them.
        int x_pos = upper_bound(sums.begin() + i, sums.begin() + j, X - delta) - sums.begin();
        int y_pos = lower_bound(sums.begin() + i, sums.begin() + j, Y - delta) - sums.begin();
        if (sums[x_pos] == X - delta || sums[y_pos] == Y - delta) {
          one_swap = true;
        } else  if (x_pos != y_pos) {
          one_swap = true;
        }
      }
    }
    if (zero_swap) {
      printf("0\n");
    } else if (one_swap) {
      printf("1\n");
    } else {
      printf("2\n");
    }
  }
}
