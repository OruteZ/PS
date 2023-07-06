#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
using namespace std;

typedef long long ll;

int N, M, K;

vector<ll> arr;
vector<ll> seg_tree;

ll cal_size_of_tree(int size) {
    int h = ceil(log2(size));
    ll tree_size = 1 << (h + 1);

    return tree_size + 1;
}

void start() {
    //arr 입력 후 tree 초기화
    for(int i = 0; i < N; i++) {
        ll num; cin >> num;
        arr.push_back(num);
    }
    int size = arr.size();
    seg_tree.assign(cal_size_of_tree(size), 0);
}

ll init(ll node, int start, int end) {
    if(start == end) return seg_tree[node] = arr[end];

    int mid = (start + end) / 2;
    ll left_value = init(node * 2, start, mid);
    ll right_value = init(node * 2 + 1, mid + 1, end);

    return seg_tree[node] = left_value + right_value;
}

ll get_sum(ll node, int start, int end, const int &target_start, const int &target_end) {
    if(start > target_end or end < target_start) return 0;
    if(target_start <= start and end <= target_end) return seg_tree[node];

    int mid = (start + end) / 2;
    ll left_value = get_sum(node * 2, start, mid, target_start, target_end);
    ll right_value = get_sum(node * 2 + 1, mid + 1, end, target_start, target_end);

    return left_value + right_value;
}

void update(ll node, int start, int end, const int& target_index, const ll& diff) {
    if(target_index < start or target_index > end) return;

    seg_tree[node] += diff;

    if(start == end) return;

    int mid = start + end; mid /= 2;
    update(node * 2, start, mid, target_index, diff);
    update(node * 2 + 1, mid + 1, end, target_index, diff);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> N >> M >> K;
    int cnt = M + K;

    start();

    init(1, 0, arr.size() - 1);

    int order;
    while(cnt--) {
        ll a, b;

        cin >> order >> a >> b;
        if(order == 1) {
            a--;
            ll diff = b - arr[a];

            update(1, 0, N - 1, a, diff);
            arr[a] = b;
        } else {
            cout << get_sum(1, 0, N - 1, a - 1, b - 1) << '\n';
        }
    }

    return 0;
}

