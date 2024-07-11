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
#include <set>

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
//-----------------------------

int N, K;
vector<PII> Contests;
multiset<int> Blocked;
map<PII, bool> Has_Blocked;

//bool is_blockable(int a) {
//    //Contests직선이 a 점 위에서 K회 이상 중첩되었다면 false 반환
//
//}

// 해당 cont를 막습니다
bool block_single(PII& cont) {
    auto it = Blocked.lower_bound(cont.first);
    if(it == Blocked.begin()) return false;

    --it;

    Blocked.erase(it);
    Blocked.insert(cont.second);
    return true;
}

void block() {
    for(auto& cont : Contests) {
        if(block_single(cont)) {
            Has_Blocked[cont] = true;
        }
    }
}

int participate() {
    int last_fin = -1;
    int ret = 0;
    for(auto& cont : Contests) {
        if(last_fin >= cont.first) continue;

        if(block_single(cont)) {
            Has_Blocked[cont] = true;
        } else if(cont.first > last_fin) {
            ret++;
            last_fin = cont.second;

            //if(DEBUG) cout << "part : " << cont.first << ' ' << cont.second << endl;
        }
    }
    return ret;
}

int main() {
    cin >> N >> K;
    REPEAT(N) {
        int s, e;
        cin >> s >> e;

        Contests.emplace_back(s, e);
    }

    sort(Contests.begin(), Contests.end(), [](PII& a, PII& b) {
        if(a.second == b.second) return a.first < b.first;
        else return a.second < b.second;
    });

    REPEAT(K - 1) Blocked.insert(0);

    int answer = participate();

    cout << answer << endl;
}
