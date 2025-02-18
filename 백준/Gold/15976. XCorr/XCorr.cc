#include<bits/stdc++.h>

typedef long long ll;
using namespace std;

void getInput(map<int, int>& target) {
    int cnt = 0; cin >> cnt;

    for (int i = 0; i < cnt; i++) {
        int a, b; cin >> a >> b;
        target[a] = b;
    }
}

void buildPresum(vector<pair<int, ll>>& presum_map, map<int, int>& original) {
    int sum = 0;
    for (auto it = original.begin(); it != original.end(); it++) {
        sum += it->second;
        presum_map.emplace_back(it->first, sum);
    }
}

int getPresum(vector<pair<int, ll>>& presum_info, int start, int end) {
    // a <= t <= b인 t들의 합을 구하는 함수
    start = max(-1, start);
    end = max(-1, end);

    int sum = 0;

    auto comp1 = [](const pair<int, ll>& a, int b) { return a.first < b; };
    auto comp2 = [](int a, const pair<int, ll>& b) { return a < b.first; };

    auto right = upper_bound(presum_info.begin(), presum_info.end(), end, comp2) - 1;
    auto left = lower_bound(presum_info.begin(), presum_info.end(), start, comp1) - 1;

    return right->second - left->second;
}

int main() {
    map<int, int> x;
    map<int, int> y;
    vector<pair<int, ll>> presum = {{-100, 0}};

    getInput(x);
    getInput(y);
    buildPresum(presum, y);

    int a, b; cin >> a >> b;


    ll answer = 0;
    for(auto [k, v] : x) {
        answer += (ll)v * getPresum(presum, a + k, b + k);

        ///cout << getPresum(presum, a + k, b + k) << endl;;
    }

    //cout << endl;
    cout << answer << endl;

}