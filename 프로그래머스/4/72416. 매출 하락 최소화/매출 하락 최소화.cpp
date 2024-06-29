#include <string>
#include <vector>
#include <climits>
#include <algorithm>
#include <iostream>
#include <cmath>

#define DEBUG true

using namespace std;

vector<vector<int>> graph;
vector<pair<int, int>> dp_table; // <true, false>

void build_graph(vector<vector<int>>& links, int n) {        
    
    graph.resize(n + 1);
    for(auto& link : links) {
        graph[link[0] - 1].push_back(link[1] - 1);
    }
    
    dp_table.resize(n + 1);
    for(auto& dp : dp_table) {
        dp.first = -1;
        dp.second = -1;
    }
}

int recursion(int num, bool do_part, vector<int>& sales);

int dp_formula_T(int num, vector<int>& sales) {
    int ret = sales[num];
    for(int child : graph[num]) {
        ret += min(recursion(child, true, sales), recursion(child, false, sales));
    }
    
    return ret;
}

int dp_formula_F(int num, vector<int>& sales) {
    int ret = 0;
    for(int child : graph[num]) {
        ret += min(recursion(child, true, sales), recursion(child, false, sales));
    }
    
    // case : 전부 참여 안했을 떄
    int no_one = 0;
    for(int child : graph[num]) {
        no_one += recursion(child, false, sales);
    }
    
    // 참여 비용이 가장 싼 한명은 해야지
    if(ret == no_one && !graph[num].empty()) {
        int some_one_value = INT_MAX;
            
        for(int child : graph[num]) {
            int part_cost = recursion(child, true, sales) - recursion(child, false, sales);
            some_one_value = min(some_one_value, part_cost);
        }
        
        ret += some_one_value;
    }
    
    return ret;
}


int recursion(int num, bool do_part, vector<int>& sales) {
    int& result = do_part ? dp_table[num].first : dp_table[num].second;
    if(result != -1) return result;
    
    result = do_part ? dp_formula_T(num, sales) : dp_formula_F(num, sales);
    
    // if(DEBUG) cout << num + 1 << ' ' << (do_part ? 't' : 'f') << " : " << result << endl;
    
    return result;
}

int solution(vector<int> sales, vector<vector<int>> links) {
    int answer = 0;
    int n = sales.size();
    
    build_graph(links, n);
    answer = min(recursion(0, false, sales), recursion(0, true, sales));
    
    return answer;
}