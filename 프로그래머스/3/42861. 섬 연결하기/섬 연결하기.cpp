#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

map<int, int> Parent;

int get_parent(int num) {
    if(Parent.find(num) == Parent.end()) {
        Parent[num] = num;
    }
    
    int& p = Parent[num];
    if(p != num) {
        p = get_parent(p);
    }
    
    return p;
}

void connect(int a, int b) {
    int a_par = get_parent(a);
    int b_par = get_parent(b);
    
    if(a_par < b_par) Parent[b_par] = a_par;
    else Parent[a_par] = b_par;
}

// returns cost
int MST_Kruskal(vector<vector<int>>& costs) {
    sort(costs.begin(), costs.end(), 
         
         [](vector<int>& left, vector<int>& right) {return left[2] < right[2];}
         
        );
    
    int result = 0;
    
    for(auto& edge : costs) {
        int u = edge[0];
        int v = edge[1];
        int dist = edge[2];
        
        if(get_parent(u) == get_parent(v)) continue;
        connect(u, v);
        result += dist;
    }
    
    return result;
}

int solution(int n, vector<vector<int>> costs) {
    return MST_Kruskal(costs);
}