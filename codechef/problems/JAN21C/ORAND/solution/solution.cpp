#include <cstdio>
#include <queue>
#include <map>
using namespace std;

// Variables for the problem
int A[1000000], B[1000000];
map<int, bool> visited;
int explored = 0;
int N, M;

void create_graph() {
  queue<int> q;
  q.push(0);
  while(q.size() != 0) {
    int current = q.front();
    q.pop();
    if (!visited[current]) {
      explored += 1;
      visited[current] = true;
      for (int i = 0; i < N; i++) {
        if (!visited[current | A[i]]) {
          q.push(current | A[i]);
        }
      }
      for (int i = 0; i < M; i++) {
        if (!visited[current & B[i]]) {
          q.push(current & B[i]);
        }
      }
    }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d", &N);
    scanf("%d", &M);
    for (int i = 0; i < N; i++) {
      scanf("%d", A + i);
    }
    for (int i = 0; i < M; i++) {
      scanf("%d", B + i);
    }
    create_graph();
    printf("%d\n", explored);
    explored = 0;
    visited.clear();
  }
}
