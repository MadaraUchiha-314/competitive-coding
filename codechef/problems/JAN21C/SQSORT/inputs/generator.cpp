//generates all test files from 0.in to 7.in
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <codecvt>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif

#if __cplusplus >= 201402L
#include <shared_mutex>
#endif

#if __cplusplus >= 201703L
#include <any>
#include <charconv>
// #include <execution>
#include <filesystem>
#include <optional>
#include <string_view>
#include <variant>
#endif

#if __cplusplus > 201703L
#include <bit>
#include <compare>
#include <concepts>
#if __cpp_impl_coroutine
# include <coroutine>
#endif
#include <latch>
#include <numbers>
#include <ranges>
#include <span>
#include <stop_token>
#include <semaphore>
#include <syncstream>
#include <version>
#endif
using namespace std;
typedef long long int uli;
const int mx = 1024;
const int mxw = 50;
struct testCase{
  int B;
  vector<vector<int> > A;
  vector<int>C, D, W;
};

vector<testCase>all;

//integer to string
string itos(int v){
  if(v == 0) return "0";
  string ans = "";
  for(; v != 0; v/=10) ans = string(1, '0' + (v % 10)) + ans;
  return ans;
}

//print all test cases
void printAll(){
  int tc = 0;
  for(auto tst : all){
    string fname = itos(tc) + ".in";
    auto fl = freopen(fname.c_str(),"w",stdout);
    int n = tst.A.size();
    int b = tst.B;

    printf("%d %d\n", n, b);

    for(int i = 0; i < n; i++){
      if(i!=0)printf(" ");
      printf("%d", tst.C[i]);
    }
    puts("");

    for(int i = 0; i < n; i++){
      if(i!=0)printf(" ");
      printf("%d", tst.D[i]);
    }
    puts("");

    for(int i = 0; i < b; i++){
      if(i!=0)printf(" ");
      printf("%d", tst.W[i]);
    }
    puts("");

    for(int i = 0; i < n; i++){
      int m = tst.A[i].size();
      printf("%d",m);
      for(int j = 0; j < m; j++){
        printf(" %d", tst.A[i][j] + 1);
      }
      puts("");
    }
    fclose(fl);
    tc++;
  }
}
int main(){
  srand(time(NULL)); //the seed is different in the official test files
  for(int n : {16, 32, 64, 128}){
    for(int s = 0; s < 2; s++){
      vector<int> p (mx, 0);
      iota(p.begin(), p.end(), 0);
      random_shuffle(p.begin(), p.end());
      testCase t;
      t.A.resize(n);
      t.B = mx;
      t.C.resize(mx);
      t.D.resize(mx);
      t.W.resize(mx);
      for(int i=0;i<mx;i++){
        t.C[i] = rand() % mxw + 1;
        t.D[i] = rand() % mxw + 1;
        t.W[i] = rand() % mxw + 1;
      }
      random_shuffle(p.begin(),p.end());
      for(int x : p){
        int i = rand() % n;
        //first generation scheme: all elements to the first sequence
        if(s == 0) i = 0;
        t.A[i].push_back(x);
      }
      all.push_back(t);
    }
  }
  printAll();
  return 0;
}
