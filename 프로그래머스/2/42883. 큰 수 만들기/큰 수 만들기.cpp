#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

string solution(string number, int k) {
    int remove_cnt = 0;
    
    int i = 0;
    while(remove_cnt < k) {
        // cout << "--" << endl;
        if(i == number.size() - 1) {
            // cout << "brk" << endl;
            break;
        }
        
        if(number[i] < number[i + 1]) {
            // cout << "remove pos : " << i << ", num : " << number[i] << endl;
            
            number.erase(i, 1);
            i -= 2;
            if(i < -1) i = -1;
            
            remove_cnt++;
        }
        
        i++;
    }
    
    int rest = k - remove_cnt;
    while(rest--) {
        number.pop_back();
    }
    
    return number;
}