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

int count_more_than_k(const std::vector<int>& vec, int k) {
    return vec.end() - std::upper_bound(vec.begin(), vec.end(), k);
}

LL cal_tree_size(int arr_size) {
    long long h = ceil(log2(arr_size));
    long long tree_size = 1 << (h + 1);

    return tree_size + 1;
}

std::vector<std::vector<int>> merge_sort_tree;


void merge(const std::vector<int> &left_child, const std::vector<int> &right_child, std::vector<int> &result) {
    int left_pointer = 0;
    int right_pointer = 0;

    result.resize(left_child.size() + right_child.size());
    int result_idx = 0;

    while(left_pointer < left_child.size() and right_pointer < right_child.size()) {
        int l_value = left_child[left_pointer];
        int r_value = right_child[right_pointer];

        if(l_value < r_value) {
            result[result_idx++] = l_value;
            left_pointer++;
            continue;
        }

        else {
            result[result_idx++] = r_value;
            right_pointer++;
            continue;
        }
    }

    while(left_pointer < left_child.size()) {
        result[result_idx++] = left_child[left_pointer++];
    }

    while(right_pointer < right_child.size()) {
        result[result_idx++] = right_child[right_pointer++];
    }
}
void build(int tree_idx, int arr_begin, int arr_end, const std::vector<int> &arr) {
    if(arr_begin + 1 == arr_end) {
        merge_sort_tree[tree_idx].push_back(arr[arr_begin]);
        return;
    }

    int mid = (arr_begin + arr_end) / 2;
    build(tree_idx * 2, arr_begin, mid, arr);
    build(tree_idx * 2 + 1, mid, arr_end, arr);

    merge(merge_sort_tree[tree_idx * 2], merge_sort_tree[tree_idx * 2 + 1], merge_sort_tree[tree_idx]);
}
void init(const std::vector<int> &arr) {
    merge_sort_tree.resize(cal_tree_size(arr.size()));

    build(1, 0, arr.size(), arr);
}

int query(int target_begin, int target_end, int cur_begin, int cur_end, int tree_idx, int k) {
    if(cur_end <= target_begin or target_end <= cur_begin) return 0;
    if(target_begin <= cur_begin and cur_end <= target_end) return count_more_than_k(merge_sort_tree[tree_idx], k);

    int cur_mid = (cur_begin + cur_end) / 2;
    int l = query(target_begin, target_end, cur_begin, cur_mid, tree_idx * 2, k);
    int r = query(target_begin, target_end, cur_mid, cur_end, tree_idx * 2 + 1, k);

    return l + r;
}

int main() {
    FAST_IO;
    int n; std::cin >> n;

    std::vector<int> arr(n);
    for(int &i : arr) std::cin >> i;

    init(arr);

    int m; std::cin >> m;

    int i, j, k;

    REPEAT(m) {
        std::cin >> i >> j >> k;

        std::cout << query(i - 1, j, 0, n, 1, k) << '\n';
    }
}