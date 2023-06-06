#include <iostream>
#include <vector>
#include <cmath>
typedef long long ll;
using namespace std;

int cal_tree_size(int vector_size) {
    int h = ceil(log2(vector_size));
    return (1 << (h + 1));
}

void input_vector(vector<int> &origin_vector, int vector_size) {
    for(auto &i : origin_vector) cin >> i;
}

ll seg_init(const vector<int> &origin, vector<ll> &tree, int node, int left, int right) {
    if(left >= right) return 0;

    if(right - left == 1) {
        tree[node] = origin[left];
        return tree[node];
    }

    int mid = (left + right) / 2;

    ll left_value = seg_init(origin, tree, node * 2, left, mid);
    ll right_value = seg_init(origin, tree, node * 2 + 1, mid, right);

    tree[node] = left_value + right_value;
    return tree[node];
}

void seg_update(const vector<int> &origin, vector<ll> &tree, int node, int left, int right, int idx, int diff) {
    if(idx < left or right <= idx) return;

    tree[node] += diff;
    if(left + 1 == right) return;

    int mid = (left + right) / 2;
    seg_update(origin, tree, node * 2, left, mid, idx, diff);
    seg_update(origin, tree, node * 2 + 1, mid, right, idx, diff);
}

ll seg_sum(const vector<int> &origin, vector<ll> &tree, int node, int left, int right, int start, int end) {
    if(right <= start or left >= end) return 0;
    if(start <= left and right <= end) return tree[node];

    int mid = (left + right) / 2;
    ll left_value = seg_sum(origin, tree, node * 2, left, mid, start, end);
    ll right_value = seg_sum(origin, tree, node * 2 + 1, mid, right, start, end);

    return left_value + right_value;
}

void solve() {
    int n;
    int m;
    int tree_size;
    cin >> n >> m;
    n++;

    tree_size = cal_tree_size(n);

    vector<int> origin_vector(n);
    for(auto &i : origin_vector) i = 0;
    vector<ll> seg_tree(tree_size);
    seg_init(origin_vector, seg_tree, 1, 1, n + 1);

    int order, start, end, point, value;
    for(int i = 0; i < m; i++){
        cin >> order;
        if(order == 0){
            cin >> start >> end;
            if(start > end) {
                swap(start, end);
            }

            cout <<
            seg_sum(origin_vector, seg_tree, 1, 1, n + 1, start, end + 1)
            << '\n';
        }
        else {
            cin >> point >> value;
            int diff = value - origin_vector[point];
            origin_vector[point] = value;
            seg_update(origin_vector, seg_tree, 1, 1, n + 1, point, diff);
        }
    }

}

//-------------------------------------------- const code ------------------------------------------
//int main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr); cout.tie(nullptr);
//
//    solve();
//
//    return 0;
//}
