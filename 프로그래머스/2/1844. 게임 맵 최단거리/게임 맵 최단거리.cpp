#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<iostream>
using namespace std;

int N, M;

pair<int, int> Delta[4] = {
    {0, 1},
    {1, 0},
    {-1, 0},
    {0, -1}
};

pair<int, int> add(pair<int, int>& a, pair<int, int>& b) {
    return make_pair(a.first + b.first, a.second + b.second);
}

bool is_out_of_map(int i, int j) {
    if(i >= N or i < 0) return true;
    if(j >= M or j < 0) return true;
    return false;
}

bool is_out_of_map(pair<int, int>& pos) {
    return is_out_of_map(pos.first, pos.second);
}

int bfs(vector<vector<int>>& maps) {
    vector<vector<int>> dist(N);
    for(vector<int>& line : dist) line.resize(M);
    
    pair<int, int> dest = {N-1, M-1};
    pair<int, int> start = {0, 0};
    
    queue<pair<int, int>> q;
    q.emplace(start);
    dist[0][0] = 1;
    
    while(not q.empty()) {
        pair<int, int> cur = q.front(); 
        q.pop();
        
        if(cur == dest) break;
        
        for(int k = 0; k < 4; k++) {
            pair<int, int> next = add(cur, Delta[k]);
            if(is_out_of_map(next)) continue;
            if(dist[next.first][next.second] > 0) continue;
            if(maps[next.first][next.second] == 0) continue;
            
            dist[next.first][next.second] = dist[cur.first][cur.second] + 1;
            q.push(next);
        }
    }
    
    return dist[N-1][M-1] == 0 ? -1 : dist[N-1][M-1];
}

int solution(vector<vector<int>> maps)
{
    N = maps.size();
    M = maps[0].size();
    
    int answer = bfs(maps);
    
    
    return answer;
}