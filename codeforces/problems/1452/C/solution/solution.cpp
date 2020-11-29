#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
  int t;
  cin>>t;

  while (t--) {
    string s;
    cin>>s;
    int sq = 0, ro = 0;
    int ans = 0;
    for (char c: s) {
      if (c == '[') sq++;
      else if (c == ']' && sq > 0) ++ans,--sq;
      else if (c == '(') ro++;
      else if (c == ')' && ro > 0) ++ans,--ro;
    }
    cout<<ans<<endl;
  }
}
