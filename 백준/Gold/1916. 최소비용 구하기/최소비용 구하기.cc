#include<iostream>
#include<queue>
#include<unordered_map>
#include<vector>
using namespace std;

int INF = 99999999;

// <비용, 목적지> [출발지]
vector<pair<int, int>> table[1001];

//최소 값 저장 배열 dist
int dist[1001];

void dijk(int start){
    priority_queue<pair<int,int>> container;

    container.push({-dist[start], start});

    while(!container.empty()){
        int curNode = container.top().second;
        int curValue = -container.top().first;
        container.pop();

        if(curValue > dist[curNode]) continue;

        for(int i = 0; i < table[curNode].size(); i++){
            int nextNode = table[curNode][i].second;
            int nextValue = table[curNode][i].first;

            if(dist[nextNode] > nextValue + curValue){
                dist[nextNode] = nextValue + curValue;
                container.push({-dist[nextNode], nextNode});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n,m; cin >> n; cin >> m;

    while(m--){
        int a,b,c;
        cin >> a >> b >> c;

        table[a].emplace_back(c,b);
    }
    int start, end; cin >> start >> end;


    for(int i = 1; i <= n; i++){
        dist[i] = INF;
    }
    dist[start] = 0;

    dijk(start);

    cout << dist[end] << endl;


    return 0;
}