#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>
#include<vector>
#include<set>

#define LL long long
#define PII std::pair<int, int>
#define DEBUG false
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)

#define MAX 100'000

int array[MAX];
std::vector<std::vector<int>> merge_tree;


LL cal_size(int n) {
    long long h = ceil(log2(n));
    long long tree_size = 1 << (h + 1);

    return tree_size + 1;
}

void merge(int left_child, int right_child, int cur_node) {
    std::vector<int> &left_vec = merge_tree[left_child];
    std::vector<int> &right_vec = merge_tree[right_child];
    std::vector<int> &result = merge_tree[cur_node];

    result.reserve(left_vec.size() + right_vec.size());

    int l_ptr = 0, r_ptr = 0;
    while(l_ptr < left_vec.size() and r_ptr < right_vec.size()) {
        if(left_vec[l_ptr] <= right_vec[r_ptr]) {
            result.push_back(left_vec[l_ptr++]);
            continue;
        }
        else {
            result.push_back(right_vec[r_ptr++]);
            continue;
        }
    }

    while(l_ptr < left_vec.size()) {
        result.push_back(left_vec[l_ptr++]);
    }

    while(r_ptr < right_vec.size()) {
        result.push_back(right_vec[r_ptr++]);
    }
}

void recursion_init(int begin, int end, int node) {
    int length = end - begin;
    if(length == 1) {
        merge_tree[node].push_back(array[begin]);
        return;
    }

    int mid = (begin + end) / 2;
    recursion_init(begin, mid, node * 2);
    recursion_init(mid, end, node * 2 + 1);

    merge(node * 2, node * 2 + 1, node);
}

void init_tree(int arr_size) {
    LL tree_size = cal_size(arr_size);
    merge_tree.resize(tree_size);

    recursion_init(0, arr_size, 1);
}

int count_more_than_k(int k, const std::vector<int> &vec) {
    auto iter = std::upper_bound(vec.begin(), vec.end(), k);
    int length = vec.end() - iter;
    return length;
}

int query(int begin, int end, int target_begin, int target_end, int k, int node) {
    if(target_end <= begin or end <= target_begin) return 0;
    if(target_begin <= begin and end <= target_end) return count_more_than_k(k, merge_tree[node]);

    int mid = (begin + end) / 2;
    int l_value = query(begin, mid, target_begin, target_end, k, node * 2);
    int r_value = query(mid, end, target_begin, target_end, k, node * 2 + 1);

    return l_value + r_value;
}


void print_tree() {
    for(int idx = 1; idx < merge_tree.size(); idx++) {
        std::vector<int> &vec = merge_tree[idx];
        for(int &i : vec) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    FAST_IO;

    int n; std::cin >> n;
    for(int i = 0; i < n; i++) {
        std::cin >> array[i];
    }
    init_tree(n);

    int m; std::cin >> m;

    int i, j, k;
    int a, b, c;
    int last_answer = 0;

    REPEAT(m) {
        std::cin >> a >> b >> c;
        i = last_answer ^ a;
        j = last_answer ^ b;
        k = last_answer ^ c;

        i--; //0_base기 때문에 인덱스를 1 빼고 봐야함, 하지만 함수의 범위가 [begin, end)기 때문에 j는 그대로

        last_answer = query(0, n, i, j, k, 1);
        std::cout << last_answer << '\n';
    }

    if(DEBUG) print_tree();
}