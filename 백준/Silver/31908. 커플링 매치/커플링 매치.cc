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
#define DEBUG true
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)
#define ENDL '\n'
#define INT_INF 2147483647
#define INT_M_INF (-2147483648)

using namespace std;


int main() {
    int size;
    cin >> size;

    map<string, vector<string>> dict;

    string name, ring;
    REPEAT(size) {
        cin >> name >> ring;
        if(ring == "-") continue;

        dict[ring].push_back(name);
    }

    std::cout << std::count_if(dict.begin(),
                               dict.end(),
                               [](auto& v) {return v.second.size() == 2;}
                               ) << ENDL;

    for(const auto& value : dict) if(value.second.size() == 2) {
        std::cout << value.second[0] << ' ' << value.second[1] << ENDL;
    }
}