#include <cstdio>
#include <vector>
#include <utility>
#include <map>
using namespace std;

#define DEBUG 1

#if DEBUG
  #define debug printf
#else
  #define debug(...) 1 == 1
#endif

const long long MAX_ANTS = 500000;
// The number of positive and negative coordinates for each line.
vector<pair<long long, long long> > ants_line;
// For a given point it has all the lines which have that point.
map<int, pair<vector<int>, vector<int> > > lines_for_point;

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
        // Add that line to the list of lines which have the same point in them.
        if (X > 0) {
          lines_for_point[abs(X)].first.push_back(i);
        } else {
          lines_for_point[abs(X)].second.push_back(i);
        }
      }
      ants_line.push_back(
        make_pair(
          positive,
          negative
        )
      );
    }
    long long answer = 0;
    // Now we go through each point and then see if it appears in multiple lines.
    // If it does, then we need to change the positives and negatives for that particular line.
    debug("Total unique points %lu\n", lines_for_point.size());
    for (auto [point, lines]: lines_for_point) {
      debug("Point is %d\n", point);
      debug("Size of lines for point %d is %lu\n", point, lines.first.size() + lines.second.size());

      if (lines.first.size() + lines.second.size() > 1) {
        // We go to each line and modify the positives and negatives for that line.
        for (auto line: lines.first) {
          debug("Lines are %d\n", line);
          if (ants_line[line].first > 0) {
            ants_line[line].first -= 1;
          }

          ants_line[line].second += 1;
        }
        for (auto line: lines.second) {
          debug("Lines are %d\n", line);
          ants_line[line].first += 1;
          if (ants_line[line].second > 0) {
            ants_line[line].second -= 1;
          }
        }
      }
    }
    for (auto line: ants_line) {
      answer += (long long) line.first * (long long) line.second;
    }
    printf("%lld\n", answer);
    debug("===============\n");
    lines_for_point.clear();
    ants_line.clear();
  }
}
