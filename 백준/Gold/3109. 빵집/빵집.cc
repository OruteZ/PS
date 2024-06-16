#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>
#include<vector>
#include<unordered_set>
#include<list>

#define LL long long
#define PII std::pair<int, int>
#define DEBUG true
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)
#define ENDL '\n'
#define INT_INF 2147483647
#define INT_M_INF (-2147483648)

class map {
private:
    int width;
    int height;

    std::vector<std::vector<bool>> m;
    bool available(int i, int j) {
        if(i >= height) return false;
        if(j >= width ) return false;
        if(i < 0) return false;
        if(j < 0) return false;

        return m[i][j];
    }

public:
    map(int w, int h) : width(w), height(h) {
        m.resize(sizeof(std::vector<bool>) * h);
        for(int i = 0; i < h; i++) {
            m[i].resize(sizeof(bool) * w);
        }
    };

    void get_input() {
        std::string line;
        for(int i = 0; i < height; i++) {
            std::cin >> line;
            for(int j = 0; j < width; j++) {
                if(line[j] == '.') m[i][j] = true;
                else m[i][j] = false;
            }
        }
    }

    bool try_connect(int i, int j = 0) {
        if(not available(i, j)) return false;
        m[i][j] = false;

        if(j == width - 1) return true;

        for(int di = -1; di <= 1; di++) {
            int next_i = i + di;
            int next_j = j + 1;

            if(try_connect(next_i, next_j)) return true;

        }

        return false;
    }
};

int main() {
    FAST_IO;

    int w, h;
    std::cin >> h >> w;

    map m(w, h);
    m.get_input();

    int answer = 0;
    for(int i = 0; i < h; i++) {
        if(m.try_connect(i)) answer++;
    }
    std::cout << answer;
}