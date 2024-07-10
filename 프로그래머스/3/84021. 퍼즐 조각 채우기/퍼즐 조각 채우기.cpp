#include <string>
#include <vector>
#include <map>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

struct pos {
    int x;
    int y;
    
    bool operator==(const pos& other) const {
        return other.x == x && other.y == y;
    }
    
    bool operator!=(const pos& other) const {
        return ! (*this == other);
    }
    
    pos operator+(const pos& other) const {
        return {
            other.x + x,
            other.y + y
        };
    }
    
    pos operator-(const pos& other) const {
        return {
            x - other.x,
            y - other.y
        };
    }
    
    vector<pos> get_delta() {
        vector<pos> ret = {
            {x + 1, y},
            {x - 1, y},
            {x, y + 1},
            {x, y - 1}
        };
        
        return ret;
    }
    
    bool operator<(const pos& other) const {
        if(x < other.x) return true;
        if(x > other.x) return false;
        
        return y < other.y;
    }
};

vector<vector<pos>> blanks;
vector<vector<pos>> shapes;
int Size;

bool out_of_map(const pos& p) {
    if(p.x >= Size or p.x < 0) return true;
    if(p.y >= Size or p.y < 0) return true;
    
    return false;
}

void bfs(vector<vector<pos>>& target, 
         vector<vector<int>>& board, 
         map<pos, bool>& visited,
         pos start, int filled_n) {
    
    queue<pos> container;
    vector<pos> result;
    
    container.push(start);
    visited[start] = true;
    
    while(!container.empty()) {
        auto cur = container.front(); container.pop();
        
        result.push_back(cur);
        
        for(auto& next : cur.get_delta()) {
            if(out_of_map(next)) continue;
            if(board[next.x][next.y] == filled_n) continue;
            if(visited[next]) continue;
            
            visited[next] = true;
            container.push(next);
        }
    }
    
    target.push_back(result);
}


vector<pos> re_position(vector<pos>& pos_list) {
    int min_x = 100;
    int min_y = 100;
    //find minimum
    for(auto& p : pos_list) {
        min_x = min(p.x , min_x);
        min_y = min(p.y, min_y);
    }
    
    pos min_pos = {min_x, min_y};
    for(auto& p : pos_list) {
        p = p - min_pos;
    }
    
    return pos_list;
}

void build_shape(vector<vector<pos>>& target, vector<vector<int>>& board, int filled_n) {
    map<pos, bool> visited;
    
    for(int i = 0; i < Size; i++) {
        for(int j = 0; j < Size; j++) {
            if(board[i][j] == filled_n) continue;
            if(visited[{i, j}]) continue;
            
            bfs(target, board, visited, {i, j}, filled_n);
        }
    }
}

int compare(vector<pos> a, vector<pos> b) {
    if(a.size() != b.size()) return 0;
    
    int result = 0;
    a = re_position(a);
    b = re_position(b);
    
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    
    return a == b ? a.size() : 0;
}

vector<vector<int>> rotate(vector<vector<int>> original) {
    vector<vector<int>> result(Size);
    for(auto& v : result) v.resize(Size);
    
    for(int i = 0; i < Size; i++) {
        for(int j = 0; j < Size; j++) {
            result[Size - j - 1][i] = original[i][j];
        }
    }
    
    return result;
}

void fill(vector<pos> pos_list, vector<vector<int>>& board) {
    for(auto& p : pos_list) {
        board[p.x][p.y] = 1 - board[p.x][p.y];
    }
}

template<typename T>
void rm_erase(vector<T>& list, T target) {
    list.erase(remove(list.begin(), list.end(), target), list.end());
}

int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
    int answer = 0;
    Size = game_board.size();
    
    
    for(int rot = 0; rot < 4; rot++) {
        blanks.clear(); shapes.clear();
        
        build_shape(blanks, game_board, 1);
        build_shape(shapes, table, 0);
        
        for(int i = 0; i < shapes.size(); i++) {
            auto& shp = shapes[i];
            
            for(auto& blnk : blanks) {
                int value = compare(shp, blnk);
                if(value == 0) continue;
                
                answer += value;
                fill(blnk, game_board);
                fill(shp, table);

                rm_erase<vector<pos>>(blanks, blnk);
                rm_erase<vector<pos>>(shapes, shp);
                i--;
                break;
            }
        }
        
        
        table = rotate(table);
    }
    
    return answer;
}