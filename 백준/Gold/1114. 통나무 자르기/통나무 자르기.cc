#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 통나무를 M길이 이하로 자를 수 있는가?
bool isFeasible(int M, const vector<int>& pos, int L, int C, int &firstCut) {
    int cnt = 0, last = L;

    // base : 마지막 통이 M보다 길면 false
    if(L - pos.back() > M) return false;

    for (int i = pos.size() - 1; i >= 0; i--) {
        if (last - pos[i] > M) {
            // 잘라도 안되면 false
            if (last - pos[i + 1] > M) return false;


            cnt++;
            last = pos[i + 1];
            firstCut = pos[i + 1];
        }
    }
    
    if (last > M) {
        if (pos[0] > M)
            return false;
        else {
            cnt++;
            firstCut = pos[0];
            last = pos[0];
        }
    }

    // 만약 cnt가 남아돌면 첫빠따 자르기
    if (cnt < C) firstCut = pos[0];

    // M 이하로 유지하기 위해 자른 횟수가 C보다 크다면 불가능
    return cnt <= C;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int L, K, C;
    cin >> L >> K >> C;
    vector<int> pos(K);
    for (int i = 0; i < K; i++){
        cin >> pos[i];
    }
    sort(pos.begin(), pos.end());
    
    // Binary search for the minimum M
    // M is the maximum distance between cuts
    int lo = 1, hi = L;
    int bestM = L, bestFirstCut = 0;
    while(lo <= hi){
        int mid = (lo + hi) / 2;
        int firstCut;
        if(isFeasible(mid, pos, L, C, firstCut)){
            bestM = mid;
            bestFirstCut = firstCut;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    
    cout << bestM << " " << bestFirstCut << "\n";
    return 0;
}
