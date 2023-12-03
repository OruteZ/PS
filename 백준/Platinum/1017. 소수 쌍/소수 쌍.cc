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
#define DEBUG true
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)
#define FAST_IO std::ios_base::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr)

#define MAX 2000

class prime_checker {
private:
    std::vector<bool> is_prime_vec;
    int size;
public:
    prime_checker(int length) {
        size = length;
        is_prime_vec.resize(size + 1);
        for(int i = 0; i <= size; i++) {
            is_prime_vec[i] = true;
        }

        is_prime_vec[0] = is_prime_vec[1] = false;
        for(int i = 2; i <= size; i++) {
            if(not is_prime_vec[i]) continue;

            for(int j = 2; j * i <= size; j++) {
                is_prime_vec[i * j] = false;
            }
        }
    }
    bool is_prime(int num) {
        if(num > size) return false;
        return is_prime_vec[num];
    }
};

std::vector<int> adj[MAX + 1];

std::vector<int> link(MAX + 1);

bool visited[MAX + 1];

int first;

void clear_link() {
    for(int &i : link) i = -1;
}

void clear_visited() {
    for(int i = 0; i <= MAX; i++) visited[i] = false;
}

bool try_match(int num) {
    if(visited[num]) return false;
    visited[num] = true;

    for(int target : adj[num]) {
        int from = link[target];
        if(from == first) continue;

        if(from == -1) {
            link[target] = num;
            link[num] = target;
            return true;
        }

        if(try_match(from)) {
            link[target] = num;
            link[num] = target;
            return true;
        }
    }

    return false;
}

bool try_bipartite_match(const std::vector<int>& left) {
    for(int i = 1; i < left.size(); i++) {
        clear_visited();

        if(not try_match(left[i])) return false;
    }

    return true;
}

int main() {
    prime_checker pc(MAX);

    FAST_IO;
    int n; std::cin >> n;

    std::vector<int> list(n);
    for(int i = 0; i < n; i++) {
        std::cin >> list[i];
    }

    std::vector<int> even, odd;
    for(int num : list) {
        if(num % 2 == 0) {
            even.push_back(num);
        }
        else odd.push_back(num);
    }

    if(even.size() != odd.size()) {
        std::cout << -1;
        exit(0);
    }

    for(int e : even) for(int o : odd) {
        if(pc.is_prime(e + o)) {
            adj[o].push_back(e);
            adj[e].push_back(o);
        }
    }

    first = list[0];
    bool is_even = first % 2 == 0;

    std::priority_queue<int, std::vector<int>, std::greater<>> pq;
    for(int next : adj[first]) {
        clear_link();

        link[next] = first;
        link[first] = next;

        if(try_bipartite_match(is_even ? even : odd)) {
            pq.push(next);
        }
    }

    if(pq.empty()) std::cout << -1;
    else while(not pq.empty()){
        int top = pq.top();
        pq.pop();

        std::cout << top << ' ';
    }
}