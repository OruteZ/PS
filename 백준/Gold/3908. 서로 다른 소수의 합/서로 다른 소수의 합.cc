#include<bits/stdc++.h>

using namespace std;

vector<bool> is_prime;
vector<map<int, int>> sum_factors;
    // sum_factors[i][j] = k : i수를 j개의 소수의 합으로 나타내는 방법의 수가 k개 존재한다.

void build_table(int n, int k) {
    is_prime.resize(n + 1, true);
    sum_factors.resize(n + 1);

    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    // dp 시작 O(N)
    for (int i = 2; i <= n; i++) if(is_prime[i]) {
        // 이전에 존재하는 모든 소수 순회, 이때 더하기가 중복되지 않도록 역순으로 해줌줌
        for(int j = n; j >= 0; j--) {
            int target = i + j;

            if(target > n) continue;

            // target의 경우의 수에 1를 더해줌, key값이 없다면 value를 1로 초기화
            for(auto& p : sum_factors[j]) {
                sum_factors[target][p.first + 1] += p.second;
            }
        }

        // 자기자신으로 구성이 가능하기 때문에 1추가
        sum_factors[i][1] = 1;
    }
}

int main() {
    int n, k;
    
    int t_case; cin >> t_case;


    // 최대 정수개수 1120에 대한 모든 테이블 그냥 미리 작성
    build_table(1120, 14);

    while(t_case--) {
        cin >> n >> k;

        cout << sum_factors[n][k] << '\n';
    }

}