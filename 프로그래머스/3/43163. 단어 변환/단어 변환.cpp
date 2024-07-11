#include <string>
#include <vector>
#include <queue>
using namespace std;

int Size = 0;

bool is_changeable(string& begin, string& target) {
    int diff_cnt = 0;
    for(int i = 0; i < begin.size(); i++) {
        if(begin[i] != target[i]) diff_cnt++;
    }
    
    return diff_cnt <= 1;
}

int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    Size = words.size();
    
    queue<string> container;
    container.push(begin);
    
    vector<bool> visited;
    visited.assign(Size, false);

    
    while(not container.empty()) {
        int container_cnt = container.size();
        // bfs 개수 세서 바꾸기
        while(container_cnt--) {
            string cur = container.front();
            container.pop();
            
            
            // 
            if(cur == target) return answer;

            for(int i = 0; i < Size; i++) {
                string word = words[i];
                if(visited[i]) continue;
                if(not is_changeable(cur, word)) continue;
                
                visited[i] = true;
                container.push(word);
            }
        }
        
        answer++;
    }
    
    return 0;
}