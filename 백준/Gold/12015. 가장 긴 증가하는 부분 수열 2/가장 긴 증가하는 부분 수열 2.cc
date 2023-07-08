#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
using namespace std;

typedef long long ll;

void set_lis(vector<int> &lis, int v) {
    if(lis.back() < v) {
        lis.push_back(v); return;
    }

//    int start = 0;
//    int end = lis.size() - 1;
//    while(true) {
//        if(start == end) {
//            lis[start] = v;
//            break;
//        }
//
//        int mid = start + end / 2;
//
//        if(lis[mid] < v) start = mid + 1;
//        else end = mid;
//    }
    auto iter = lower_bound(lis.begin(), lis.end(), v);
    (*iter) = min(*iter, v);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<int> A(N);
    for(int &i : A) cin >> i;

    vector<int> lis_vector = {INT32_MAX};
    for(int i : A) {
        set_lis(lis_vector, i);
    }

//    for(int i : lis_vector) cout << i << " ";
//    cout << endl;

    cout << lis_vector.size() << endl;

    return 0;
}