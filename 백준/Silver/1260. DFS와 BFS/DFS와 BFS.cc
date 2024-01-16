#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
#include<queue>
using namespace std;

bool isConnected[1001][1001];
bool isVisited[1001];
bool isVisitedinB[1001];
int a;

void DFS(int startNum){
    stack<int> container;
    container.push(startNum);

    int num;
    while(!container.empty()){
        num = container.top();
        container.pop();

        if(isVisited[num]) continue;
        isVisited[num] = true;
        cout << num << " ";

        for(int i = a; i > 0; i--){
            if(isConnected[num][i]){
                container.push(i);
            }
        }
    }
    cout << endl;
}

void BFS(int startNum){
    queue<int> container;
    container.push(startNum);

    int num;
    while(!container.empty()){
        num = container.front();
        container.pop();

        if(isVisitedinB[num]) continue;
        isVisitedinB[num] = true;
        cout << num << " ";

        for(int i = 1; i <= a; i++){
            if(isConnected[num][i]){
                container.push(i);
            }
        }
    }
}
int main() {
    int b, startNum, m, n;
    cin >> a;
    cin >> b;
    cin >> startNum;

    for (int i = 0; i < b; i++) {
        cin >> m;
        cin >> n;

        isConnected[m][n] = true;
        isConnected[n][m] = true;
    }

    DFS(startNum);
    BFS(startNum);
}