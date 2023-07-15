#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int str_to_int(string num) {
    int answer = 0;
    for(int i = 0; i < num.size(); i++) {
        answer += i - '0';
        answer *= 10;
    }
    
    return answer / 10;
}

string solution(string s) {
    vector<int> nums;
    
    int cur_idx = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == ' ') {
            nums.push_back(stoi(s.substr(cur_idx, i - cur_idx)));
            cur_idx = i + 1;
        }
    }
    nums.push_back(stoi(s.substr(cur_idx, s.size() - cur_idx)));
    
    for(int& i : nums) cout << i << " ";
    cout << endl;
    
    string minimum = to_string(*min_element(nums.begin(), nums.end()));
    string maximum = to_string(*max_element(nums.begin(), nums.end()));
    
    string answer = minimum + " " + maximum;
    
    return answer;
}