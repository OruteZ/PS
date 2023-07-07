#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
using namespace std;

typedef long long ll;

//No node
#define NO_NODE 0

class Segment_tree {
public:
    Segment_tree(const std::vector<ll>& arr, ll(*query)(ll, ll), ll (*default_query)(ll)) {
        this->arr.resize(arr.size());
        std::copy(arr.begin(), arr.end(), this->arr.begin());

        this->query = query;
        this->default_query = default_query;

        tree.resize(cal_size_of_tree());
        init();
    }

    ll get_query(const ll &target_start, const ll &target_end,
                 int start = 0, int end = -1, ll node_idx = 1) {
        if(end == -1) end = arr.size() - 1;
        if(end < target_start or start > target_end) return NO_NODE;
        if(target_start <= start and end <= target_end) return tree[node_idx];

        int mid = start + end; mid /= 2;
        long long l_value = get_query(target_start, target_end, start, mid, node_idx * 2);
        long long r_value = get_query(target_start, target_end, mid + 1, end, node_idx * 2 + 1);

        return query(l_value, r_value);
    }

    void change(int index, ll value) {
        arr[index] = value;

        update(index);
    }

private:
    std::vector<ll> arr;
    std::vector<ll> tree;
    ll (*query)(ll, ll);
    ll (*default_query)(ll);

    ll cal_size_of_tree() {
        long long h = ceil(log2(arr.size()));
        long long tree_size = 1 << (h + 1);

        return tree_size + 1;
    }

    ll init(ll node_idx = 1, int start = 0, int end = -1) {
        if(end == -1) end = arr.size() - 1;
        if(start == end) return tree[node_idx] = default_query(arr[start]);

        int mid = start + end; mid /= 2;
        ll l_value = init(node_idx * 2, start, mid);
        ll r_value = init(node_idx * 2 + 1, mid + 1, end);

        return tree[node_idx] = query(l_value, r_value);
    }

    ll update(const int &target_index,
                int start = 0, int end = -1, ll node_idx = 1) {
        if(end == -1) end = arr.size() - 1;
        if(target_index > end or target_index < start) return tree[node_idx];
        if(start == end) {
            return tree[node_idx] = default_query(arr[start]);
        }

        int mid = (start + end) / 2;
        ll l_value = update(target_index, start, mid, node_idx * 2);
        ll r_value = update(target_index, mid + 1, end, node_idx * 2 + 1);

        return tree[node_idx] = query(l_value, r_value);
    }
};

ll detect_even(ll value) {
    return value % 2 == 0 ? 1 : 0;
}

ll detect_odd(ll value) {
    return value % 2 == 1 ? 1 : 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    vector<ll> arr;
    int size;

    cin >> size;
    while(size--) {
        ll number;
        cin >> number; arr.push_back(number);
    }

    Segment_tree even_tree(arr,
                      [](ll v1, ll v2) -> ll {return v1 + v2;},
                      detect_even);
    Segment_tree odd_tree(arr,
                          [](ll v1, ll v2) -> ll {return v1 + v2;},
                          detect_odd);

    int cmd_size;
    cin >> cmd_size;
    while(cmd_size--) {
        int order, i, j;
        ll value;

        if(cin>>order, order==1) {
            cin >> i >> value;

            even_tree.change(i - 1, value);
            odd_tree.change(i - 1, value);
        }
        else if(order == 2) {
            cin >> i >> j;

            cout << even_tree.get_query(i - 1, j - 1) << '\n';
        }
        else {
            cin >> i >> j;

            cout << odd_tree.get_query(i - 1, j - 1) << '\n';
        }
    }

    return 0;
}