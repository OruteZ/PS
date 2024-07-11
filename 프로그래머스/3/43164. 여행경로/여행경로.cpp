#include <string>
#include <algorithm>
#include <stack>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

// 공항 : <목적지, 티켓 번호>
map<string, vector<pair<string, int>>> graph;

// <n, b> : n번 티켓 썼는가? true : false (b)
map<int, bool> visited;

// 티켓 전체 개수
int T_length;

void build_graph(vector<vector<string>>& tickets) {
    int idx = 0;
    for(auto& ticket : tickets) {
        graph[ticket[0]].emplace_back(ticket[1], idx++);
    }
    
    for(auto& [key, val] : graph) {
        sort(val.begin(), val.end());
    }
}

// start 정점, edge_num 번 티켓을 써서, answer, stk
bool try_dfs(string start, int edge_num, vector<string>& answer, int stk = 0) {
    if(visited[edge_num]) return false;
    
    cout << "DFS : " << start << ' ' << stk << endl;
    
    //start
    visited[edge_num] = true;
    answer.push_back(start);
    
    
    //check fin
    if(T_length == stk) return true;
    
        for(auto& next : graph[start]) {
            int next_edge = next.second;
            string next_str = next.first;
            
            bool result = try_dfs(next_str, next_edge, answer, stk + 1);
            if(result == true) return true;
        }
    
    
    //end
    visited[edge_num] = false;
    answer.pop_back();
    
    return false;
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    
    T_length = tickets.size();
    
    build_graph(tickets);
    try_dfs("ICN", -1, answer);
    
    
    return answer;
}