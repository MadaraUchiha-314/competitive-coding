#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define DEBUG 1

#if DEBUG
  #define debug printf
#else
  #define debug(...) 1 == 1
#endif

int main() {
  int T, N, X, Y;
  int A[1000];
  vector<int> cum_sum;
  scanf("%d", &T);
  while(T--) {
    debug("Test case %d\n", T);
    cum_sum.clear();
    scanf("%d %d %d", &N, &X, &Y);
    cum_sum.push_back(0);
    for (int i = 0; i < N; i++) {
      scanf("%d", A + i);
      cum_sum.push_back(cum_sum[i] + A[i]);
    }
    int lower_x = 0, lower_y = 0;
    for (int i = 0; i < cum_sum.size(); i++) {
      if (cum_sum[i] <= X) {
        lower_x = max(lower_x, i);
      }
      if (cum_sum[i] <= Y) {
        lower_y = max(lower_y, i);
      }
    }
    /**
     * Example array [7, 8, 5, 3, 2, 1]
     * Cumulative sum array: [0, 7, 15, 20, 23, 25, 26]
     * Case - 1:
     * X = 17, Y = 19
     * lower_x == lower_y == 2
     */
    /**
     * lower_x and lower_y need to be exactly the same for us to be swapping.
     * If not there is some cumulative sum which is in between.
     */
    debug("Lower x = %d Lower Y = %d and sums are %d %d\n", lower_x, lower_y, cum_sum[lower_x], cum_sum[lower_y]);
    if (lower_x != lower_y) {
      printf("0\n");
    } else if (cum_sum[lower_x] == X || cum_sum[lower_y] == Y) {
      printf("0\n");
    } else if (lower_x == cum_sum.size() - 1) {
      printf("-1\n");
    }
    else {
      /**
       * There are 2 cases where we will require a swap of exactly 1.
       * Case-1, we swap one of the elements from the left of lower_x with an appropriate element.
       * Case-2 we swap one of the elements from the right of lower_x with an appropriate element.
       */
      lower_x -= 1; // Convert it to the index for the array A. There was an extra element added to cum_sum.
      bool found = false;
      for (int i = 0; i <= lower_x; i++) {
        for (int j = lower_x + 1; j < N; j++) {
          debug("Comparing %d and %d\n", A[i], A[j]);
          if (
            ((A[j] - A[i]) >= (X - cum_sum[lower_x + 1])) && ((A[j] - A[i]) <= (Y - cum_sum[lower_x + 1]))
          ) {
            debug("Can swap %d with %d\n", A[i], A[j]);
            found = true;
            break;
          }
        }
        if (found) {
          break;
        }
      }
      if (found) {
        printf("1\n");
        continue;
      }
      for (int i = lower_x + 2; i < N; i++) {
        if (
          (A[lower_x + 1] - A[i]) >= (cum_sum[lower_x + 2] - Y) && (A[lower_x + 1] - A[i] <= (cum_sum[lower_x + 2] - X))
        ) {
          debug("Can swap %d with %d\n", A[lower_x + 1], A[i]);
          found = true;
          break;
        }
      }
      if (found) {
        printf("1\n");
        continue;
      }
      printf("2\n");
    }
  }
}
