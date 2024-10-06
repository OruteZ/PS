#include<bits/stdc++.h>

using namespace std;

int N;
vector<int> A;

bool is_full_zero() {
    for(int x : A) {
        if(x != 0) return false;
    }
    return true;
}

int solution() {
   int ret = 0;

   while(not is_full_zero()) {
        for(int i = 0; i < N; i++) {
            if(A[i] % 2 == 1) {
                A[i]--;
                ret++;
            }    
        }

        if(is_full_zero()) break;
        
        for(int& i : A) {
            i /= 2;
        }
        ret++;
   } 

   return ret;
}

int main() {
    cin >> N;
    A.resize(N);
    for(int& x : A) cin >> x;

    cout << solution() << endl;
}