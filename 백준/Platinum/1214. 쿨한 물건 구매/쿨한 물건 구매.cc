#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<stack>
#include<deque>

#define INT_INF 2147483647
#define INT_NINF -2147483648
#define FASTIO std::ios_base::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
#define LL long long
#define PII std::pair<int, int>
#define ENDL '\n'
#define DEBUG true

LL solve(int p, int q, int d) {
   if(d % q == 0) return d;
   if(d % p == 0) return d;

   int p_full_cnt = d / p + 1;
   LL cur_max = p * p_full_cnt;
   LL ret = p * p_full_cnt;

   for(int i = p_full_cnt - 1; i >= 0; i--) {
      //find the remaining distance
      int remaining = d - i * p;
      if(remaining % q == 0) {
         return d;
      }
      int q_full_cnt = remaining / q + 1;

      LL cur_answer = q * q_full_cnt + i * p;
      if(cur_answer == cur_max) break;
      ret = std::min(ret, cur_answer);
   }

   return ret;
}

int main() {
   FASTIO;

   int p, q, d;

   std::cin >> d >> p >> q;
   if(p < q) {
      //swap
      int temp = p;
      p = q;
      q = temp;
   }

   LL answer = solve(p, q, d);
   std::cout << answer << ENDL;   

   return 0;
}