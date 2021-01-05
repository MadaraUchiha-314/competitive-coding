#include <cstdio>
#include <cstdlib>
#include <utility>
using namespace std;
int main() {
  int T;
  int N, K, X, Y;
  scanf("%d", &T);
  while(T--) {
    scanf("%d %d %d %d", &N, &K, &X, &Y);
    pair<int, int> point = make_pair(X, Y);
    pair<int, int> reflections[4];
    bool hit_corner = false;
    for (int i = 0; i < 4; i++) {
      if (Y <= X) {
        if (i == 0) {
          point.second = point.second + abs(N - point.first);
          point.first = N;
        } else if (i == 1) {
          point.first = point.first - abs(N - point.second);
          point.second = N;
        } else if (i == 2) {
          point.second = N - abs(point.first);
          point.first = 0;
        } else {
          point.first = 0 + abs(point.second);
          point.second = 0;
        }
      } else {
        if (i == 0) {
          point.first = point.first + abs(N - point.second);
          point.second = N;
        } else if (i == 1) {
          point.second = N - abs(N - point.first);
          point.first = N;
        } else if (i == 2) {
          point.first = N - abs(point.second);
          point.second = 0;
        } else {
          point.second = 0 + abs(point.first);
          point.first = 0;
        }
      }
      if (hit_corner) {
        reflections[i] = reflections[i - 1];
      } else {
        reflections[i] = point;
      }
      if (point.first == 0 && point.second == 0) {
        hit_corner = true;
      } else if (point.first == 0 && point.second == N) {
        hit_corner = true;
      } else if (point.first == N && point.second == N) {
        hit_corner = true;
      } else if (point.first == N && point.second == 0) {
        hit_corner = true;
      }
    }
    printf("%d %d\n", reflections[(K - 1) % 4].first,  reflections[(K - 1) % 4].second);
  }
}
