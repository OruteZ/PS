#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int execute(vector<int> array, const vector<int>& command) {
    int i = command[0], j = command[1], k = command[2];
    
    sort(array.begin() + i - 1, array.begin() + j);
    return *(array.begin() + i + k - 2);
}

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    
    for(auto& command : commands) {
        answer.push_back(execute(array, command));
    }
    
    return answer;
}