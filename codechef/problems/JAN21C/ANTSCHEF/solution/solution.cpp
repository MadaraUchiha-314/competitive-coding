#include <cstdio>
#include <vector>
#include <utility>
#include <cstdint>
using namespace std;

const long long MAX_ANTS = 500000;
vector<pair<long long, long long> > ants_line;

int main() {
  long long T, N, X, M;
  scanf("%lld", &T);
  while(T--) {
    scanf("%lld", &N);
    for (long long i = 0; i < N; i++) {
      scanf("%lld", &M);
      long long negative = 0, positive = 0;
      for (long long j = 0; j < M; j++) {
        scanf("%lld", &X);
        if (X < 0) {
          negative += 1;
        } else {
          positive += 1;
        }
      }
      ants_line.push_back(
        make_pair(
          max(positive, negative),
          min(positive, negative)
        )
      );
    }
    long long current_answer = 0;
    for (auto ant: ants_line) {
      current_answer += ant.second * ant.first;
    }
    ants_line.clear();
    printf("%lld\n", current_answer);
  }
}
