#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>
#include<vector>
#include<unordered_set>
#include<list>
#include<map>

#define LL long long
#define PII std::pair<int, int>
#define DEBUG false
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)
#define ENDL '\n'
#define INT_INF 2147483647
#define INT_M_INF (-2147483648)

using namespace std;

class cmd_dict {
private:
    map<int, pair<int, int>> dict;

    void init() {
        for(int i = 0; i < 8; i++) {
            for(int j = i + 1; j < 8; j++) {
                dict[pow(2, i) + pow(2, j)] = make_pair(i, j);
            }
        }
    }
public:
    cmd_dict() {
        init();
    }

    bool try_get_cmd(int value, pair<int, int>& result) {
        if(dict.find(value) == dict.end()) {
            return false;
        }

        result = dict.operator[](value);
        return true;
    }
};

int main() {
    int n, target;
    std::cin >> n;

    vector<int> positions(8);
    for(int i = 0; i < 8; i++) positions[i] = i;
    vector<int> command_list(n);
    for(int& i : command_list) cin >> i;

    std::cin >> target;

    cmd_dict dic = cmd_dict();

    PII result;
    for(int& cmd : command_list) {
        if(not dic.try_get_cmd(cmd, result)) continue;

        if(DEBUG) std::cout << "cmd : " << result.first << ' ' << result.second << ENDL;

        swap(positions[result.first], positions[result.second]);
    }

    std::cout << positions[target];
}
