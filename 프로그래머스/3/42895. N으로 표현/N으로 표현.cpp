#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

vector<unordered_set<int>> Dp(9); // dp[i]는 N을 i번 사용해서 나타낼 수 있는 모든 수들의 집합

int get_only_N(int N, int size) {
    int ret = 0;
    while(size--) {
        ret = ret * 10 + N;
    }
    
    return ret;
}

int solution(int N, int number) {
    if (N == number) return 1;
    
    
    // N, NN, NNN . . . 삽입
    int num = 0;
    for (int i = 1; i < 9; i++) {
        Dp[i].insert(get_only_N(N, i));
        
        //방금 넣음
        if (Dp[i].find(number) != Dp[i].end()) {
            return i;
        }
    }

    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < i; j++) {
            
            for (int a : Dp[j]) {
                for (int b : Dp[i - j]) {
                    Dp[i].insert(a + b);
                    Dp[i].insert(a - b);
                    Dp[i].insert(a * b);
                    if (b != 0) Dp[i].insert(a / b);
                }
            }
        }
        
        if (Dp[i].find(number) != Dp[i].end()) {
            return i;
        }
    }
    
    return -1;
}