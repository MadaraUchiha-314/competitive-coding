#include <cstdio>
#include <vector>
#include <limits>
#include <map>
using namespace std;

void input();

int N, M;
const int MAX_NODES = 200000;
int A[MAX_NODES];
vector<int> g[MAX_NODES];
bool visited[MAX_NODES];
int costs[MAX_NODES];

int dfs(int current) {
    if (!visited[current]) {
        visited[current] = true;
        int max_price = A[current];
        for (auto child: g[current]) {
            max_price = max(dfs(child), max_price);
        }
        costs[current] = max_price; 
    }
    return costs[current];
}

void solve() {
    int max_profit = numeric_limits<int>::min();
    for (int i = 0; i <  N; i++ ) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    for (int i = 0; i < N; i++) {
        if (g[i].size() > 0) {
            for (auto child: g[i]) {
                max_profit = max(max_profit, costs[child] - A[i]);
            }
        }
    }
    printf("%d\n", max_profit);
}


int main() {
    input();
    solve();
}

void input() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", A + i);
    }
    int src, dest;
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &src, &dest);
        g[src - 1].push_back(dest - 1);
    }
}