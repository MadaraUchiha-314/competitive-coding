#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <limits>
#include <map>
#include <tuple>
using namespace std;

const int INFINITY = 1 << 20;

map<tuple<int, int, int>, int> memo;
int min_answer = INFINITY;

int boxes(int *H, int k1, int k2, int i, int current_answer) {
  if (k1 <= 0 && k2 <= 0) {
    min_answer = min(min_answer, current_answer);
    return 0;
  }
  if (i < 0) {
    return INFINITY;
  }
  if (current_answer > min_answer) {
    return INFINITY;
  }
  if (memo.find(make_tuple(max(k1, -1), max(k2, -1), i)) != memo.end()) {
    return memo[make_tuple(max(k1, -1), max(k2, -1), i)];
  }
  int answer1 = INFINITY, answer2 = INFINITY;
  if (k1 > 0) {
    int min_k = min(k1 - H[i], k2);
    int max_k = max(k1 - H[i], k2);
    answer1 = boxes(H, min_k, max_k, i - 1, current_answer + 1) + 1;
  }
  if (k2 > 0) {
    int min_k = min(k2 - H[i], k1);
    int max_k = max(k2 - H[i], k1);
    answer2 = boxes(H, min_k, max_k, i - 1, current_answer + 1) + 1;
  }
  int answer = min(
    answer1,
    answer2
  );
  memo[make_tuple(max(k1, -1), max(k2, -1), i)] = answer;
  return answer;
}
int main() {
  int T;
  int N, K;
  int H[4000];
  scanf("%d", &T);
  while(T--) {
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; i++) {
      scanf("%d", H + i);
    }
    sort(H, H + N);
    int answer = boxes(H, K, K, N - 1, 0);
    printf("%d\n", min_answer > N ? -1 : min_answer);
    memo.clear();
    min_answer = INFINITY;
  }
}
