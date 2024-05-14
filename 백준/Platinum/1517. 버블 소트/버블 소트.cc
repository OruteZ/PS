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

LL ret;
std::vector<int> temp;

void merge(std::vector<int>& arr, int l, int r, int size) {
   int mid = (l + r) / 2;
   int i = l, j = mid + 1;
   int k = l;
   
   int swp_cnt = 0;

   while(i <= mid && j <= r) {
      if(arr[i] <= arr[j]) {
         temp[k++] = arr[i++];
         ret += swp_cnt;
      } else {
         temp[k++] = arr[j++];
         swp_cnt++;
      }
   }

   while(i <= mid) {
      temp[k++] = arr[i++];
      ret += swp_cnt;
   }

   while(j <= r) {
      temp[k++] = arr[j++];
      swp_cnt++;
   }

   for(int i = l; i <= r; i++) {
      arr[i] = temp[i];
   }
}

void merge_sort(std::vector<int>& arr, int l = 0, int r = -1) {
   int n = arr.size();
   if(r == -1) r = n - 1;

   // recursion
   if(l < r) {
      int mid = (l + r) / 2;
      merge_sort(arr, l, mid);
      merge_sort(arr, mid + 1, r);
      merge(arr, l, r, n);
   }
}

void solve(std::vector<int>& arr) {
   merge_sort(arr); 

   // std::cout << "Sorted array: ";
   // for(int i = 0; i < arr.size(); i++) {
   //    std::cout << arr[i] << " ";
   // }

   std::cout << ret << ENDL;
}

int main(void) {
   int n;
   std::cin >> n;

   std::vector<int> arr(n);
   temp.resize(n);

   for(int i = 0; i < n; i++) {
      std::cin >> arr[i];
   }

   solve(arr);

   return 0;
}