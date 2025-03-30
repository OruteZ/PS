#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string S;
    getline(cin, S);
    
    vector<string> tokens;
    string curr = "";
    int n = S.size();
    
    for (int i = 0; i < n; i++){
        char c = S[i];
        // 두 글자짜리 구분자: &&, ||
        if ((c == '&' || c == '|') && i+1 < n && S[i+1] == c) {
            if (!curr.empty()) {
                tokens.push_back(curr);
                curr = "";
            }
            tokens.push_back(string(2, c)); // "&&" 또는 "||"
            i++; // 다음 문자 건너뛰기
        }
        // 한 글자짜리 구분자: <, >, (, )
        else if (c == '<' || c == '>' || c == '(' || c == ')') {
            if (!curr.empty()){
                tokens.push_back(curr);
                curr = "";
            }
            tokens.push_back(string(1, c));
        }
        // 공백 구분자
        else if (c == ' ') {
            if (!curr.empty()){
                tokens.push_back(curr);
                curr = "";
            }
            // 공백 토큰도 일단 추가 (나중에 제거)
            tokens.push_back(" ");
        }
        else {
            curr.push_back(c);
        }
    }
    if(!curr.empty())
        tokens.push_back(curr);
    
    // 출력 시 " " (단일 공백) 토큰은 무시하고, 나머지를 단일 공백으로 연결합니다.
    bool first = true;
    for (const string &tok : tokens) {
        if (tok == " ") continue; // 공백 토큰 건너뛰기
        if (!first) cout << " ";
        cout << tok;
        first = false;
    }
    cout << "\n";
    return 0;
}
