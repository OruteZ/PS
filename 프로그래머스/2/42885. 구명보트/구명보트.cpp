#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int Answer;
int Capacity;
int Limit;

int get_available() {
    return Limit - Capacity;
}

void board(int num) {
    if(get_available() >= num) {
        Capacity += num;
        return;
    }
    
    //else : new boat
    Answer++;
    Capacity = num;
}

int solution(vector<int> people, int limit) {
    Limit = limit;
    Capacity = 0;
    Answer = 1;
    
    sort(people.begin(), people.end());
    
    int l_idx = 0, r_idx = people.size() - 1;
    while(l_idx <= r_idx) {
        int double_weight = people[l_idx] + people[r_idx];
        int single_weight = people[r_idx];
        
        if(double_weight <= get_available()) {
            l_idx++;
            r_idx--;
            
            board(double_weight);
        }
        
        else {
            r_idx--;
            board(single_weight);
        }
    }
    
    return Answer;
}