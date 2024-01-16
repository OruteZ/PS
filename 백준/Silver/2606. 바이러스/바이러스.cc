#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
//-----------------------------------로파이 재즈
#include<stack>
#include<queue>
#include<algorithm>
int board[101][101];
bool visited[101];
int num;
int DFS(int n){

    stack<int> container;
    container.push(n);
    visited[n] = true;
    int cnt = 0;
    while(!container.empty()){
        int k = container.top();
        container.pop();

        for(int i = 1; i <= num; i++){
            if(board[k][i] == 1 && !visited[i]){
                container.push(i);
                visited[i]= true;
                cnt++;
            }
        }
    }
    return cnt;
}
int main(){

    cin >> num;

    int T;
    cin>> T;

    int a,b;
    while(T--){
        cin >> a >> b;
        board[a][b] = 1;
        board[b][a] = 1;
    }
    cout << DFS(1) << endl;
};