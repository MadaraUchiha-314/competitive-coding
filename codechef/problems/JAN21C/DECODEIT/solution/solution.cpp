#include <cstdio>
using namespace std;
int main() {
  int T;
  int N;
  char S[100000];
  char lower_case_letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'};
  scanf("%d", &T);
  while(T--) {
    scanf("%d", &N);
    scanf("%s", S);
    for (int i = 0; i < N; i += 4) {
      int decoded_char = ((S[i] - '0') * 1 << 3) + ((S[i +  1] - '0') * 1 << 2) + ((S[i + 2]  - '0') * 1 << 1) + ((S[i + 3]  - '0') * 1 << 0);
      printf("%c", lower_case_letters[decoded_char]);
    }
    printf("\n");
  }
}
