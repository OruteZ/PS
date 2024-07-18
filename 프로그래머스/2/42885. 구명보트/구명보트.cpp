#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<int> people, int limit) {
    int answer = 0;
    
    sort(people.begin(), people.end());
    
    int l_idx = 0, r_idx = people.size() - 1;
    while(l_idx <= r_idx) {
        int double_weight = people[l_idx] + people[r_idx];
        int single_weight = people[r_idx];
        
        if(double_weight <= limit) {
            l_idx++;
            r_idx--;
            
            answer++;
        }
        
        else {
            r_idx--;
            answer++;
        }
    }
    
    return answer;
}