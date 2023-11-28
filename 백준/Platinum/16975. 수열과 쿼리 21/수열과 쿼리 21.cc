#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>
#include<vector>

#define LL long long
#define DEBUG true
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)

LL cal_tree_size(int arr_size) {
    long long h = ceil(log2(arr_size));
    long long tree_size = 1 << (h + 1);

    return tree_size + 1;
}

std::vector<LL> seg_tree;
std::vector<LL> lazy;
void init_tree(const std::vector<LL>& arr);
LL init(LL node, LL begin_idx, LL end_idx, const std::vector<LL>& arr);
LL get_value(LL target, LL begin, LL end, LL node);

void update_lazy(LL node, LL begin, LL end) {
    if(lazy[node] == 0) return;

    LL length = end - begin;
    seg_tree[node] += length * lazy[node];

    if(length == 1) {
        lazy[node] = 0;
        return;
    }

    lazy[node * 2] += lazy[node];
    lazy[node * 2 + 1] += lazy[node];
    lazy[node] = 0;
}

LL update(LL target_begin, LL target_end, LL begin, LL end, LL node, LL value) {
    if(begin >= target_end or end <= target_begin) return 0;

    if(target_begin <= begin and end <= target_end) {
        lazy[node] += value;
        update_lazy(node, begin, end);
        return seg_tree[node];
    }

    LL mid = (begin + end) / 2;
    LL l = update(target_begin, target_end, begin, mid, node * 2, value);
    LL r = update(target_begin, target_end, mid, end, node * 2 + 1, value);
    return seg_tree[node] = l + r;
}

void init_tree(const std::vector<LL>& arr) {
    LL size = arr.size();

    LL tree_size = cal_tree_size(size);
    seg_tree.resize(tree_size);
    lazy.resize(tree_size);

    init(1, 0, arr.size(), arr);
}

LL init(long long int node, long long int begin, long long int end, const std::vector<long long int> &arr) {
    int size = end - begin;
    if(size == 1) {
        seg_tree[node] = arr[begin];
        return seg_tree[node];
    }

    int mid = (begin + end) / 2;
    LL l_value = init(node * 2, begin, mid, arr);
    LL r_value = init(node * 2 + 1, mid, end, arr);

    return l_value + r_value;
}

LL get_value(long long int target, long long int begin, long long int end, long long int node) {
    if(target < begin or target >= end) return INT64_MAX;

    //if current node has lazy value, update lazy
    update_lazy(node, begin, end);
    if(target == begin and end - begin == 1) return seg_tree[node];

    LL mid = begin + end;
    mid /= 2;

    LL l_value = get_value(target, begin, mid, node * 2);
    LL r_value = get_value(target, mid, end, node * 2 + 1);

    return std::min(l_value, r_value);
}



int main() {
    FAST_IO;
    int n; std::cin >> n;

    std::vector<LL> array(n);
    for(LL &i : array) std::cin >> i;

    init_tree(array);

    int m; std::cin >> m;

    int order, i, j, x;
    REPEAT(m) {
        std::cin >> order;
        if(order == 1) {
            std::cin >> i >> j >> x;
            i--;
            j--;

            update(i, j + 1, 0, n, 1, x);
        }

        if(order == 2) {
            std::cin >> x;
            x--;

            std::cout << get_value(x, 0, n, 1) << '\n';
        }
    }
}