#include <iostream>
#include<queue>
#include<cstring>
using namespace std;

long long int dp[100][(1<<10)-1][10];

long long int TSP(int idx, int visit, int now){

    visit |= (1 << now);

    if(idx == 0 && now == 0) return 0;

    if(visit == (1<<10)-1 && idx == 0) return 1;
    else if(visit != (1<<10)-1 && idx == 0) return 0;



    if(dp[idx][visit][now] >= 0) return dp[idx][visit][now];

    long long int result;
    if(now == 9){
        result = TSP(idx-1, visit, now-1);
    } else if (now == 0){
        result = TSP(idx-1, visit, now+1);
    } else{
        result = TSP(idx-1, visit, now-1)+TSP(idx-1, visit, now+1);
    }
    result = result % 1000000000;

    dp[idx][visit][now] = result;

    return result;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    memset(dp, -1, sizeof(dp));

    int n; cin >> n;
    /*
    for(int i = 1; i <= n; i++){
        cout << uptable[i] << " ";
    } cout << endl;
    for(int i = 1; i <= n; i++){
        cout << reversetable[i] << " ";
    } cout << endl;
    */
    long long int answer = 0;
    for(int i = 0; i < 10; i++){
        answer += TSP(n-1, 0, i);
    }
    cout << answer % 1000000000 << endl;
}