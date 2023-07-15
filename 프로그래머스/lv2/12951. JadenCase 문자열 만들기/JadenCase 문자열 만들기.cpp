#include <string>
#include <vector>

using namespace std;

string solution(string s) {
    bool is_upper = true;
    
    for(int i = 0; i < s.size(); i++) {
        if(is_upper) {
            s[i] = toupper(s[i]);
            is_upper = false;
        }
        else {
            s[i] = tolower(s[i]);
        }
        
        if(s[i] == ' ') is_upper = true;
    }
    
    return s;
}