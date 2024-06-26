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

vector<string> dict = {
        "Never gonna give you up",
        "Never gonna let you down",
        "Never gonna run around and desert you",
        "Never gonna make you cry",
        "Never gonna say goodbye",
        "Never gonna tell a lie and hurt you",
        "Never gonna stop",
};

int main() {
    FAST_IO;
    int n; cin >> n;
    cin.get();

    bool answer = true;

    REPEAT(n) {
        string input;
        getline(cin, input, '\n');

//        cout << input << endl;

        if(find(dict.begin(), dict.end(), input) == dict.end()) {
//            cout << input << " is not in dict" << endl;
            answer = false;
            break;
        }
    }

    cout << (answer ? "No" : "Yes");
}