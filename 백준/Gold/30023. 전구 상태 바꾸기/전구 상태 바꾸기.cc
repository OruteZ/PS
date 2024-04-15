#include<iostream>
#include<queue>

#define LL long long
#define PII std::pair<int, int>
#define DEBUG false
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _thisValueWillNEVERUsed = 0; _thisValueWillNEVERUsed < n; _thisValueWillNEVERUsed++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)
#define INT_MAX 2147483647

using namespace std;

#pragma region Color
enum Color {
    R = 0, G = 1, B = 2
};

enum Color operator++(Color &c) {
    c = static_cast<Color>((c + 1) % 3);
    return c;
}

enum Color operator+(Color &c, int n) {
    return static_cast<Color>(((int)c + n) % 3);
}

int operator-(Color &c1, Color &c2) {
    int ret = (int)c1 - (int)c2;
    if(ret < 0) ret += 3;

    return ret;
}

Color get_color(char c) {
    switch(c) {
        case 'R': return R;
        case 'G': return G;
        case 'B': return B;
    }
}
#pragma endregion

bool unify(vector<Color> burbs, Color target, int& cnt) {
    if(DEBUG)
        cout << "Target: " << target << '\n';

    cnt = 0;
    for(int i = 0; i < burbs.size() - 2; i++) {
        if(DEBUG) {
            for(Color c : burbs) {
                cout << c << ' ';
            } cout << endl;
        }
        if(burbs[i] == target) continue;

        int diff = target - burbs[i];
        burbs[i] = target;
        burbs[i + 1] = burbs[i + 1] + diff;
        burbs[i + 2] = burbs[i + 2] + diff;

        cnt += diff;
    }

    bool ret = burbs[burbs.size() - 2] == target
            && burbs[burbs.size() - 1] == target;
    cnt = ret ? cnt : INT_MAX;

    if(DEBUG) {
        for(Color c : burbs) {
            cout << c << ' ';
        } cout << endl;
        PRINT_LINE;
    }

    return ret;
}

int main() {
    FAST_IO;
    vector<Color> burbs;

    int n; cin >> n;
    string str; cin >> str;

    for(char& c : str) {
        burbs.push_back(get_color(c));
    }

    int red_cnt = 0, green_cnt = 0, blue_cnt = 0;

    bool red = unify(burbs, R, red_cnt);
    bool green = unify(burbs, G, green_cnt);
    bool blue = unify(burbs, B, blue_cnt);

    if(red || green || blue) {
        cout << min(red_cnt, min(green_cnt, blue_cnt));
    } else {
        cout << -1;
    }
}