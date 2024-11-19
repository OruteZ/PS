    #include <bits/stdc++.h>
    using namespace std;

    //#define DEBUG

    typedef long long int ll;

    struct Material {
        int corruption_speed;
        int expiration_date;
        int can_exception;

        ll corruption;
    };

    // day_cnt가 지난 뒤 재료들을 먹을 수 있나? 
    bool canEat(vector<Material>& materials, ll day_cnt, int max_exception, ll safety_cnt) {
        // 각 재료의 부패 정도를 큰 순으로 저장
        priority_queue<ll> pq;

        ll total_corruption = 0;
        for (int i = 0; i < materials.size(); i++) {
            materials[i].corruption = (ll)materials[i].corruption_speed * max((ll)1, day_cnt - materials[i].expiration_date);

            total_corruption += materials[i].corruption;
            if(materials[i].can_exception) pq.push(materials[i].corruption);
        }

        // safety_cnt 만큼 pq에서 값을 꺼내서 total_corruption에서 빼기
        for (int i = 0; i < max_exception; i++) {
            if (pq.empty()) break;
            total_corruption -= pq.top();
            pq.pop();
        }

        return total_corruption <= safety_cnt;
    }

    int main() {
        int material_cnt, safety_cnt, max_exception;

        cin >> material_cnt >> safety_cnt >> max_exception;

        vector<Material> materials(material_cnt);
        for (int i = 0; i < material_cnt; i++) {
            cin >> materials[i].corruption_speed >> materials[i].expiration_date >> materials[i].can_exception;
            materials[i].corruption = 0;
        }

        // 이걸로 하면 됨
        // for(int i = 0; i < 1e9; i++) {
        //     if(not canEat(materials, i, max_exception, safety_cnt)) {
        //         cout << i - 1 << endl;
        //         break;
        //     }
        // }

        // 선형탐색에서 이분탐색으로 변환
        ll left = 0, right = 2e9;
        ll result = 0;

        while (left <= right) {
            //cout << left << " " << right << endl;

            ll mid = (left + right) / 2;

            if (canEat(materials, mid, max_exception, safety_cnt)) {
                result = max(result, mid);
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        cout << result << endl;

        return 0;
    }