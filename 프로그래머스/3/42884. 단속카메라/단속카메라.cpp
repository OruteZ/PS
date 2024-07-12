#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> routes) {
    sort(routes.begin(), routes.end(), [](vector<int>& left, vector<int>& right) {
        return left[1] < right[1];
    });
    
    int answer = 0;
    int last_cam_pos = -300001;
    
    for(auto& r : routes) {
        if(r[0] <= last_cam_pos) continue;
        
        last_cam_pos = r[1];
        answer++;
    }
    
    return answer;
}