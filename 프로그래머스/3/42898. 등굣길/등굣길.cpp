#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>

#define MOD 1'000'000'007

using namespace std;

vector<vector<int>> Map;
int M, N;

int get_kind(int i, int j) {
    if(i < 0) return 0;
    if(j < 0) return 0;
    if(Map[i][j] < 0) return 0;
    
    int& ret = Map[i][j];
    if(ret > 0) return ret;
    
    ret = get_kind(i - 1, j) + get_kind(i, j - 1);
    if(ret >= MOD) ret %= MOD;
    
    return ret;
}


int solution(int m, int n, vector<vector<int>> puddles) {
    M = m; N = n;
    Map.assign(N, vector<int>(M));
    
    for(auto& p : puddles) {
        Map[p[1] - 1][p[0] - 1] = INT_MIN;
    }
    Map[0][0] = 1;
    
    return get_kind(n - 1, m - 1);
}