#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    vector<ll> A(N);
    for (int i = 0; i < N; i++){
        cin >> A[i];
    }
    
    // 접두사 합 배열: P[0]=0, P[i]=A[0]+...+A[i-1] (1-based 개념)
    vector<ll> P(N+1, 0);
    for (int i = 1; i <= N; i++){
        P[i] = P[i-1] + A[i-1];
    }
    ll T = P[N];
    
    ll count = 0;
    // X는 1부터 N-2까지 (즉, P[1]부터 P[N-2])
    for (int X = 1; X <= N - 2; X++){
        // 조건: P[Y] < T - P[X]  와  P[Y] > (T + P[X]) / 2
        ll U = T - P[X];              // 상한 (exclusive)
        ll L = (T + P[X]) / 2 + 1;      // 하한 (inclusive)
        
        // Y의 인덱스 범위: X+1 <= Y <= N-1 (P 배열에서는 인덱스 X+1부터 N-1)
        auto it_low = lower_bound(P.begin() + X + 1, P.begin() + N, L);
        auto it_up  = lower_bound(P.begin() + X + 1, P.begin() + N, U);
        
        if(it_low < it_up){
            count += (it_up - it_low);
        }
    }
    
    cout << count << "\n";
    return 0;
}
