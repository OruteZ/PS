#include <string>
#include <vector>
#include <algorithm>

#define MAX 500

using namespace std;
typedef long long ll;

ll cache[MAX][MAX] = {0,};

void init() {
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < i + 1; j++) {
            cache[i][j] = -1;
        }
    }
}

int solution(vector<vector<int>> triangle) {
    init();
    
    for(int i = triangle.size() - 1; i >= 0; i--) {
        for(int j = 0; j < i + 1; j++) {
            
            if(i == triangle.size() - 1) {
                cache[i][j] = triangle[i][j];
            }
            
            else {
                cache[i][j] = triangle[i][j] + max(cache[i + 1][j], cache[i + 1][j + 1]);
            }
        }
    }
    
    return cache[0][0];
}