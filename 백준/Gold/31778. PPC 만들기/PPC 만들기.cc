#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    string S;
    cin >> N >> K >> S;
    S = " " + S;  // 1-indexed 편의를 위해

    int Ptot = 0;
    for(int i = 1; i <= N; i++)
        if(S[i] == 'P') 
            Ptot++;

    vector<int> c_pos, p_pos;
    for(int i = 1; i <= Ptot; i++){
        if(S[i] == 'C')
            c_pos.push_back(i);
    }
    for(int i = Ptot+1; i <= N; i++){
        if(S[i] == 'P')
            p_pos.push_back(i);
    }

    int M0 = (int)c_pos.size();     
    int Kp = min(K, M0);               

    vector<int> ys;
    for(int t = 0; t < Kp; t++){
        ys.push_back(p_pos[M0 - 1 - t]);
    }
    
    for(int i = 0; i < Kp; i++){
        int x = c_pos[i];
        int y = ys[i];
        swap(S[x], S[y]);
    }

    ll ans = 0;
    ll cntP = 0;
    for(int i = 1; i <= N; i++){
        if(S[i] == 'P'){
            cntP++;
        } else { // 'C'
            ans += cntP * (cntP - 1) / 2;
        }
    }

    cout << ans << "\n";
    return 0;
}
