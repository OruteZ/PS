#include<bits/stdc++.h>

using namespace std;

#define MAX_SIZE 1'000'000

int N;
vector<map<int, int>> Numbers;

void set_prime_factors(int value, map<int, int>& result) {
    while(value % 2 == 0) {
        result[2]++;
        value /= 2;
    }

    for(int i = 3; i * i <= value; i++) {
        while(value % i == 0) {
            result[i]++;
            value /= i;
        }
    }

    if(value > 2) {
        result[value]++;
    }
}

map<int, int> get_max_GCD() {
    map<int, int> result;

    for(map<int, int>& numb : Numbers) {
        for(auto [factor, cnt] : numb) {
            result[factor] += cnt;
        }
    }

    // 두 번째 루프: N으로 나눈 후, cnt가 0인 요소를 삭제한다.
    for (auto it = result.begin(); it != result.end(); ) {
        it->second /= N;

        if (it->second == 0) {
            it = result.erase(it); // 현재 요소를 삭제하고, 다음 요소로 이동
        } else {
            ++it; // 삭제하지 않은 경우 다음 요소로 이동
        }
    }

    return result;
}

int cal_cnt(const map<int, int>& target) {
    int answer = 0;

    for(map<int, int>& Number : Numbers) {
        for(auto& [factor, target_cnt] : target) {
            int cur_cnt = Number[factor];
            
            if(cur_cnt < target_cnt) answer += target_cnt - cur_cnt; 
        }
    }

    return answer;
}

int map2int(map<int, int>& m) {
    int ret = 1; 
    for(auto& [factor, cnt] : m) {
        for(int i = 0; i < cnt; i++) ret *= factor;
    }

    return ret;
}

int main() {
    cin >> N;

    Numbers.resize(N);
    for(map<int, int>& m : Numbers) {
        int numb; cin >> numb;

        set_prime_factors(numb, m);
    }

    map<int, int> GCD = get_max_GCD();
    int answer = cal_cnt(GCD);

    cout << map2int(GCD) << ' ' << answer << endl;

    return 0;
}